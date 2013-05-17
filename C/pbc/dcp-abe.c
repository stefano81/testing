#include <pbc.h>

#include <stdio.h>
#include <string.h>

#include "dcp-abe.h"

GP * global_setup(char * path_to_param) {
  char param[1024];
  FILE * file = fopen(path_to_param, "r");
  size_t count = fread(param, 1, 1024, file);
  if (!count) pbc_die("input error");
  printf("count: %d\n", (int)count);
  GP *gp = malloc(sizeof(GP));

  pairing_init_set_buf(gp->pairing, param, count);
  element_init_G1(gp->g1, gp->pairing);
  element_random(gp->g1);

  return gp;
}

struct authority * authority_setup(GP * gp, char * attributes[], int n) {
  struct authority * authority = malloc(sizeof(struct authority));

  authority->n = n;
  authority->attributes = malloc(sizeof(char *) * n);
  authority->pkeys = malloc(sizeof(struct authority_pk *) * n);
  authority->skeys = malloc(sizeof(struct authority_sk *) * n);

  int i;
  element_t eg1g1;
  element_init_GT(eg1g1, gp->pairing);

  for (i = 0; i < n; i++) {
    // copy the attribute name
    authority->attributes[i] = strdup(attributes[i]);

    // init the sk
    struct authority_sk * sk = malloc(sizeof(struct authority_sk));
    element_init_Zr(sk->ai, gp->pairing);
    element_random(sk->ai);
    element_init_Zr(sk->yi, gp->pairing);
    element_random(sk->yi);

    authority->skeys[i] = sk;
    
    // init the pk
    struct authority_pk * pk = malloc(sizeof(struct authority_pk));
    element_init_G1(pk->eg1g1_ai, gp->pairing);
    
    pairing_apply(eg1g1, gp->g1, gp->g1, gp->pairing);
    element_pow_zn(pk->eg1g1_ai, eg1g1, sk->ai);

    element_init_G1(pk->g1_yi, gp->pairing);
    element_pow_zn(pk->g1_yi, gp->g1, sk->yi);

    authority->pkeys[i] = pk;
  }

  return authority;
}

struct personal_key * generate_key(GP * gp, struct authority * authority, char *userid, char *attribute) {
  struct personal_key * per_key = malloc(sizeof(struct personal_key));

  per_key->userid = strdup(userid);
  per_key->attribute = strdup(attribute);

  element_t hgid;
  element_t g1ai;
  element_t hgidyi;

  element_init_G1(hgid, gp->pairing);
  element_init_G1(g1ai, gp->pairing);
  element_init_G1(hgidyi, gp->pairing);
  element_init_G1(per_key->key, gp->pairing);

  element_from_hash(hgid, userid, strlen(userid));

  int i = 0;
  for (i = 0; i < authority->n; i++) {
    if (!strcmp(attribute, authority->attributes[i]))
      break;
  }

  element_pow_zn(g1ai, gp->g1, authority->skeys[i]->ai);
  element_pow_zn(hgidyi, hgid, authority->skeys[i]->yi);

  element_mul(per_key->key, g1ai, hgidyi);

  return per_key;
}

node_t * compute_tree(char *policy) {
  node_t * node = malloc(sizeof(node_t));

  return NULL;
}

struct access * compute_access_structure(GP *gp, char *policy) {
  struct access * access_structure = malloc(sizeof(struct access));
  access_structure->policy = strdup(policy);
  
  access_structure->root = NULL;//compute_tree(policy);

  // test with the matrix for: and a or d and b c
  access_structure->nrow = 4;
  access_structure->ncolumn = 3;
  access_structure->matrix = malloc(sizeof(element_t *) * 4);
  int i;
  for (i = 0; i < 4; i++) {
    access_structure->matrix[i] = malloc(sizeof(element_t) * 3);
  }

  element_init_Zr(access_structure->matrix[0][0], gp->pairing);
  element_set1(access_structure->matrix[0][0]);
  element_init_Zr(access_structure->matrix[0][1], gp->pairing);
  element_set1(access_structure->matrix[0][1]);
  element_init_Zr(access_structure->matrix[0][2], gp->pairing);
  element_set0(access_structure->matrix[0][2]);

  element_init_Zr(access_structure->matrix[1][0], gp->pairing);
  element_set0(access_structure->matrix[1][0]);
  element_init_Zr(access_structure->matrix[1][1], gp->pairing);
  element_set1(access_structure->matrix[1][1]);
  element_neg(access_structure->matrix[1][1], access_structure->matrix[1][1]);
  element_init_Zr(access_structure->matrix[1][2], gp->pairing);
  element_set1(access_structure->matrix[1][2]);

  element_init_Zr(access_structure->matrix[2][0], gp->pairing);
  element_set0(access_structure->matrix[2][0]);
  element_init_Zr(access_structure->matrix[2][1], gp->pairing);
  element_set0(access_structure->matrix[2][1]);
  element_init_Zr(access_structure->matrix[2][2], gp->pairing);
  element_set1(access_structure->matrix[2][2]);
  element_neg(access_structure->matrix[2][2], access_structure->matrix[2][2]);

  element_init_Zr(access_structure->matrix[3][0], gp->pairing);
  element_set0(access_structure->matrix[3][0]);
  element_init_Zr(access_structure->matrix[3][1], gp->pairing);
  element_set1(access_structure->matrix[3][1]);
  element_neg(access_structure->matrix[3][1], access_structure->matrix[3][1]);
  element_init_Zr(access_structure->matrix[3][2], gp->pairing);
  element_set0(access_structure->matrix[3][2]);

  // and a or d and b c
  access_structure->rho = malloc(sizeof(char **) * 4);
  access_structure->rho[0] = strdup("a");
  access_structure->rho[1] = strdup("b");
  access_structure->rho[2] = strdup("c");
  access_structure->rho[3] = strdup("d");

  return access_structure;
}

void dot_product(element_t *dst, element_t *v1, element_t *v2, int size) {
  int i;
  element_t t;
  element_init_same_as(t, *dst);

  element_set0(*dst);

  for (i = 0; i < size; i++) {
    element_mul(t, v1[i], v2[i]);
    element_add(*dst, *dst, t);
  }
}

struct authority_sk * select_key(struct authority ** authorities, int index, struct access *arho) {
  char * name = arho->rho[index];

  int m = sizeof(authorities)/sizeof(struct authority *);
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < authorities[i]->n; j++) {
      if (0 == strcmp(name, authorities[i]->attributes[j])) {
	return authorities[i]->skeys[j];
      }
    }
  }
}

struct ct * encrypt(GP * gp, struct authority ** authorities, element_t * M, struct access * arho) {
  element_t s;
  element_t *v;
  element_t *w;

  element_init_GT((*M), gp->pairing);
  element_random((*M));

  element_init_Zr(s, gp->pairing);
  element_random(s);

  v = malloc(sizeof(element_t) * arho->ncolumn);
  
  element_init_Zr(v[0], gp->pairing);
  element_set(v[0], s);

  int i;
  for (i = 1; i < arho->ncolumn; i++) {
    element_init_Zr(v[i], gp->pairing);
    element_random(v[i]);
  }

  w = malloc(sizeof(element_t) * arho->ncolumn);
  element_init_Zr(w[0], gp->pairing);
  element_set0(w[0]);
  for (i = 1; i < arho->ncolumn; i++) {
    element_init_Zr(w[i], gp->pairing);
    element_random(w[i]);
  }

  struct ct * ct = malloc(sizeof(struct ct));
  
  ct->access_structure = arho;

  element_t g1g1, g1g1s;
  element_init_GT(g1g1, gp->pairing);
  element_init_GT(g1g1s, gp->pairing);

  pairing_apply(g1g1, gp->g1, gp->g1, gp->pairing);

  element_pow_zn(g1g1s, g1g1, s);

  element_init_GT(ct->c0, gp->pairing);
  element_mul(ct->c0, *M, g1g1s); // C_0 = Me(g_1, g_1)^s

  ct->c1 = malloc(sizeof(element_t) * arho->nrow);
  ct->c2 = malloc(sizeof(element_t) * arho->nrow);
  ct->c3 = malloc(sizeof(element_t) * arho->nrow);

  element_t lambdax, wx, rx;
  element_t c1x1, c1x2;
  element_t c1exp;
  element_t c3x1, c3x2;
  element_t c3exp;

  element_init_Zr(lambdax, gp->pairing);
  element_init_Zr(wx, gp->pairing);
  element_init_Zr(rx, gp->pairing);
  element_init_Zr(c1exp, gp->pairing);
  element_init_Zr(c3exp, gp->pairing);
  element_init_GT(c1x1, gp->pairing);
  element_init_GT(c1x2, gp->pairing);
  element_init_G1(c3x1, gp->pairing);
  element_init_G1(c3x2, gp->pairing);

  struct authority_sk *keyx;

  for (i = 0; i < arho->nrow; i++) {
    element_init_GT(ct->c1[i], gp->pairing);

    dot_product(&lambdax, arho->matrix[i], v, arho->ncolumn);
    element_pow_zn(c1x1, g1g1, lambdax);

    element_pow_zn(c1x2, g1g1, wx);

    element_random(rx);

    keyx = select_key(authorities, i, arho);

    element_mul(c1exp, keyx->ai, rx);
    element_pow_zn(c1x1, g1g1, c1exp);

    element_mul(ct->c1[i], c1x1, c1x2); // C_{1,x} = e(g_1, g_1)^{\lambda_x} e(g_1, g_1)^{alpha_{\rho(x)}r_x}

    element_init_G1(ct->c2[i], gp->pairing);

    element_pow_zn(ct->c2[i], gp->g1, rx); // C_{2,x} = g_1^{r_x}

    element_init_G1(ct->c3[i], gp->pairing);

    dot_product(&wx, arho->matrix[i], w, arho->ncolumn);

    element_mul(c3exp, keyx->yi, rx);
    printf("1\n");
    element_pow_zn(c3x1, gp->g1, c3exp);
    printf("2\n");
    element_pow_zn(c3x2, gp->g1, wx);

    element_mul(ct->c3[i], c3x1, c3x2); // C_{3,x} = g_1^{y_{\rho(x)}r_x} g_1^{w_x}
  }

  element_clear(rx);
  element_clear(s);
  element_clear(lambdax);

  element_clear(g1g1);
  element_clear(c1exp);
  element_clear(c1x1);
  element_clear(c1x2);

  for (i = 0; i < arho->ncolumn; i++) {
    element_clear(v[i]);
    element_clear(w[i]);
  }

  element_clear(wx);
  element_clear(c3exp);
  element_clear(c3x1);
  element_clear(c3x2);

  return ct;
}

int * get_indexes(struct personal_key **keys, int n, struct access * as) {
  // TODO
  int * indexes = malloc(sizeof(int) * 2);

  indexes[0] = 0;
  indexes[1] = 3;

  return indexes;
}

struct personal_key * get_key(struct personal_key **pkeys, int n, char *attribute) {
  int i;
  for (i = 0; i < n; i++)
    if (0 == strcmp(pkeys[i]->attribute, attribute))
      return pkeys[i];

  return NULL;
}

element_t * decrypt(GP * gp, struct ct * ct, struct personal_key **keys, int n, char *userid) {
  element_t *M = malloc(sizeof(element_t));

  element_init_GT(*M, gp->pairing);

  int *indexes = get_indexes(keys, n, ct->access_structure);

  element_t hgid;
  element_init_G1(hgid, gp->pairing);
  element_from_hash(hgid, userid, strlen(userid));

  element_t t1, t2, t3, t4;
  element_t pt;
  element_init_GT(t1, gp->pairing);
  element_init_GT(t2, gp->pairing);
  element_init_GT(t3, gp->pairing);
  element_init_GT(t4, gp->pairing);
  element_init_GT(pt, gp->pairing);

  int m = sizeof(indexes)/sizeof(int);

  int x = indexes[0];

  pairing_apply(t1, hgid, ct->c3[x], gp->pairing);
  pairing_apply(t2, get_key(keys, n, ct->access_structure->rho[x])->key, ct->c2[x], gp->pairing);
  element_mul(t3, ct->c1[x], t1);
  element_invert(t2, t2);
  element_mul(pt, t3, t2);
  
  int i;
  for (i = 1; i < m; i++) {
    x = indexes[i];
    pairing_apply(t1, hgid, ct->c3[x], gp->pairing);
    pairing_apply(t2, get_key(keys, n, ct->access_structure->rho[x])->key, ct->c2[x], gp->pairing);
    element_mul(t3, ct->c1[x], t1);
    element_invert(t2, t2);
    element_mul(t4, t3, t2);
    
    element_mul(pt, pt, t4);
  }
  element_invert(pt, pt);

  element_mul(*M, ct->c0, pt);

  return M;
}
