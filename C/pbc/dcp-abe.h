#ifndef _DCP_ABE_H
#define _DCP_ABE_H

#include <pbc.h>

struct GP {
  pairing_t pairing;
  element_t g1;
};

typedef struct GP GP;

struct authority_pk {
  element_t eg1g1_ai;
  element_t g1_yi;
};

struct authority_sk {
  element_t ai;
  element_t yi;
};

struct authority {
  char ** attributes;
  int n;
  struct authority_pk ** pkeys;
  struct authority_sk ** skeys;
};

struct personal_key {
  char * attribute;
  char * userid;
  element_t key;
};

struct node_t {
  char * name;
  char * label;
  struct node_t *left;
  struct node_t *right;
};

typedef struct node_t node_t;

struct access {
  int ncolumn, nrow;
  char * policy;
  element_t ** matrix;
  node_t * root;
  char ** rho;  
};

struct ct {
  struct access * access_structure;
  element_t c0;
  element_t * c1;
  element_t * c2;
  element_t * c3;
};

#endif
