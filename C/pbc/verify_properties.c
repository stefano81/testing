#include <stdio.h>
#include <pbc/pcb.h>

int main(int argc, char **argv) {
  pairing_t pairing;

  char param[1024];
  pairing_t * pairing = malloc(sizeof(pairing_t));

  FILE * file = fopen(params_path, "r");
  size_t read = fread(param, 1, 1024, file);
  fclose(file);

  if (!read) pbc_die("Error reading the parameter file");

  pairing_init_set_buf(*pairing, param, read);

}
