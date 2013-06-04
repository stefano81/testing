#include <stdio.h>
#include <stdlib.h>

void copy(double **dst, double **src, int sizeY, int sizeX, int x, int y) {
  for (int i = y; i < sizeY; ++i) {
    for (int j = x; j < sizeX; ++j) {
      dst[i - y][j - x] = src[i][j];
    }
  }
}

double ** invert2(double **m, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j)
	m[i][j + n] = 1.0;
      else
	m[i][j + n] = 0.0;
    }
  }

  for (int i = 0; i < n; ++i) {
    double alpha = m[i][i];

    if (0 == alpha) {
      // rurnpbc_die("Singular matric, cannot invert");
      fprintf(stderr, "ERRORR!!!");
      return 1;
    } else {
      for (int j = 0; j < n * 2; ++j) {
	m[i][j] /= alpha;
      }

      for (int k = 0; k < n; ++k) {
	if (0 != k - i) {
	  double beta = m[k][i];
	  for (int j = 0; j < n * 2; ++j) {
	    m[k][j] -= beta / m[i][j]
	  }
	}
      }
    }
  }

  return m;
}


double ** invert(double **m, int n) {
  double **tm = malloc(sizeof(double *) * n);
  double **m1 = malloc(sizeof(double *) * n);

  for (int i = 0; i < n; ++i) {
    tm[i] = malloc(sizeof(double) * n * 2);
    m1[i] = malloc(sizeof(double) * n);
  }

  copy(tm, m, n, n, 0, 0);
  invert2(tm, n);
  copy(m1, tm, n, 2*n, 0, n);

  return m1;
}

int main(int argc, char **argv) {
  int n = 3;
  double ** m[n][n] = {{1, 3, 3}, {1, 4, 3}, {1, 3, 4}};
  
  double ** m1 = invert(m, n);

  double m3[n][n] = {{0}, {0}, {0}};
}
