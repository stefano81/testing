#include <iostream>

int main(int argc, char *argv[]) {
  int vi[10];
  short vs[10];

  std::cout << "sizeof(int): " << sizeof(int) << std::endl;
  std::cout << "sizeof(short): " << sizeof(short) << std::endl;

  std::cout << &vi[0] << " " << &vi[1] << std::endl;
  std::cout << &vs[0] << " " << &vs[1] << std::endl;

  return 0;
}
