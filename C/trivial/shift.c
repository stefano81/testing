#include <stdio.h>

int main(int argc, char *argv[]) {
  unsigned long m = 1;
  unsigned long b = 0;

  for (int i = 0; i < 100; ++i) {
    printf("%d %d %d\n", m, m <<= 1, m);

    printf("%d %d %d\n", b, b |= m, m);
  }
}
