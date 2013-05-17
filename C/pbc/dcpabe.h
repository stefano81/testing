#include <pbc.h>

#include <stdio.h>
#include <string.h>

#include "dcp-abe.h"

GP * global_setup(char *path_to_param);
struct authority * authority_setup(GP * gp, char * attributes[], int n);
struct personal_key * generate_key(GP * gp, struct authority * authority, char *userid, char *attribute);
node_t * compute_tree(char *policy);
struct access * compute_access_structure(GP *gp, char *policy);
struct ct * encrypt(GP * gp, struct authority ** authorities, int n, element_t * M, struct access * arho);
element_t * decrypt(GP * gp, struct ct * ct, struct personal_key **keys, int n, char *userid);
