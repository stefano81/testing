#include "dcpabe.h"

void test1Authority(GP *gp) {
  char *attributes[] = {"a", "b", "c", "d"};
  struct authority * authority1 = authority_setup(gp, attributes, 4);
  
  printf("authority 1 created\n");

  struct personal_key * ku_a = generate_key(gp, authority1, "user", "a");

  printf("key ku_a generated\n");

  struct personal_key * ku_d = generate_key(gp, authority1, "user", "d");

  printf("key ku_d generated\n");

  struct access * arho = compute_access_structure(gp, "and a or d and b c");

  /*  // test span
  int i,j;
  element_t * v1 = arho->matrix[0];
  element_t * v2 = arho->matrix[3];
  element_t * span = malloc(sizeof(element_t) * arho->ncolumn);

  printf("print A\n");
  for (i = 0; i < arho->nrow; i++) {
    printf("%s", arho->rho[i]);
    for (j = 0; j < arho->ncolumn; j++) {
      element_printf(" %B", arho->matrix[i][j]);
    }
    printf("\n");
  }


  for (i = 0; i < arho->ncolumn; i++) {
    element_init_same_as(span[i], v1[i]);
    element_printf(" %B %B\n", v1[i], v2[i]);
    element_add(span[i], v1[i], v2[i]);
  }

  for (i = 0; i < arho->ncolumn; i++) {
    element_printf(" %B", span[i]);
  }
  printf("\n");
  */
  //  return 1;

  printf("computed access structure\n");

  element_t message;
  struct ct * ciphertext = encrypt(gp, &authority1, 1, &message, arho);

  element_printf("%B\n", message);

  printf("ciphertext created\n");

  struct personal_key ** ikeys = malloc(sizeof(struct personal_key *) * 2);
  ikeys[0] = ku_a;
  ikeys[1] = ku_d;
  //  struct personal_key ** okeys = find_keys(arho, ikeys);

  element_t * decrypted = decrypt(gp, ciphertext, ikeys, 2, "user");
  element_printf("%B\n", *decrypted);

  printf("message %c= decrypted\n", 0 == element_cmp(message, *decrypted) ? '=': '!');
}

void test2Authorities(GP *gp) {
  char *attributes1[] = {"a", "b"};
  struct authority * authority1 = authority_setup(gp, attributes1, 2);
  printf("authority 1 created\n");

  char *attributes2[] = {"c", "d"};  
  struct authority * authority2 = authority_setup(gp, attributes2, 2);
  printf("authority 2 created\n");

  struct personal_key * ku_a = generate_key(gp, authority1, "user", "a");

  printf("key ku_a generated\n");

  struct personal_key * ku_d = generate_key(gp, authority2, "user", "d");

  printf("key ku_d generated\n");

  struct access * arho = compute_access_structure(gp, "and a or d and b c");

  struct authority * authorities[] = {authority1, authority2};

  element_t message;
  struct ct * ciphertext = encrypt(gp, authorities, 2, &message, arho);

  printf("ciphertext created\n");

  struct personal_key ** ikeys = malloc(sizeof(struct personal_key *) * 2);
  ikeys[0] = ku_a;
  ikeys[1] = ku_d;

  element_t * decrypted = decrypt(gp, ciphertext, ikeys, 2, "user");

  printf("message %c= decrypted\n", 0 == element_cmp(message, *decrypted) ? '=': '!');

}

int main(int argc, char** argv) {
  printf("Let's try this out!\n");

  GP *gp = global_setup("/Users/stefano/Projects/PBC/pbc-0.5.12/param/a.param");

  printf("parameters generated\n");

  printf("%d\n", argc);

  if (1 == argc)
    test1Authority(gp);
  else
    test2Authorities(gp);

  /*  element_t mdecrypted;
  element_init_same_as(mdecrypted, *decrypted);
  element_neg(mdecrypted, *decrypted);
  printf("message %c= decrypted\n", 0 == element_cmp(message, mdecrypted) ? '=': '!');
  */

  return 0;
}

