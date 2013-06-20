#include <iostream>

int main(int argc, char *argv[]) {
  int i = 1;

  while (0 < i) ++i;

  std::cout << "i is negative!" << std::endl;

  int v[2] = {0, 1};
  i = 1;
  v[i] = i++;
}
