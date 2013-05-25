#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **m, int N) {
  printf(">>\n");
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf(" %d", m[i][j]);
    }
    printf("\n");
  }
  printf("<<\n");
}

int main(int argc, char **argv) {

  int n = 3;
  int **m = malloc(sizeof(int *) * n);

  m[0] = malloc(sizeof(int) * n);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;

  m[1] = malloc(sizeof(int) * n);
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  m[2] = malloc(sizeof(int) * n);
  m[2][0] = 7;
  m[2][1] = 8;
  m[2][2] = 9;

  int **mr = malloc(sizeof(int *) * n);

  mr[0] = malloc(sizeof(int) * n);
  mr[0][0] = 1;
  mr[0][1] = 4;
  mr[0][2] = 7;

  mr[1] = malloc(sizeof(int) * n);
  mr[1][0] = 2;
  mr[1][1] = 5;
  mr[1][2] = 8;

  mr[2] = malloc(sizeof(int) * n);
  mr[2][0] = 3;
  mr[2][1] = 6;
  mr[2][2] = 9;


  print_matrix(m, n);

  for (int i = 0; i < (n - 1); ++i) {
    for (int j = i + 1; j < n; ++j) {
      int t = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = t;
    }
  }

  print_matrix(m, n);
  print_matrix(mr, n);

  
}
