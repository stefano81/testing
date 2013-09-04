#include <stdio.h>

int main(int argc, char* argv[]) {

  for (int i = 0; i < 32; ++i)
    printf("%d %lu\n", i, (1ul << i));

  return 0;
}
