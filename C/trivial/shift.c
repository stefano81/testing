#include <stdio.h>

int main(int argc, char *argv[]) {
  unsigned long m = 1, b = m, c = 0;

  printf("%d\n", sizeof(unsigned long));

  for (int i = 0; i < (sizeof(unsigned long) * 8); ++i) {
    printf("%lu:\n", i);
    printf("m: %lu\n", m);
    printf("m<<i: %lu\n", m<<i);
    printf("b: %lu\n", b <<= 1);
    printf("c: %lu\n", c);
    printf("c: %lu\n", c |= (m<<i));
  }
}
