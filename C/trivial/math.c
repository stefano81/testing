#include <math.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  for (int i = 0; i < 100; ++i) {
    printf("%d %f\n", i, pow(-1.0, i + 2.0));
  }
}
