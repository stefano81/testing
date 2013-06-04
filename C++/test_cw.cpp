#include <iostream>
#include <cctype>

int main(int argc, char **argv) {
  uint64_t ui64 = 1;
  unsigned long tl = 1;

  std::cout << "sizeof(int):      " << sizeof(int) << '\n';
  std::cout << "sizeof(long):     " << sizeof(long) << '\n';
  std::cout << "sizeof(uint64_t): " << sizeof(uint64_t) << '\n';

  for (int i = 0; i < 64; ++i) {
    std::cout << "uint_64 " << (ui64 <<=1) << '\n';
    std::cout << "long    " << (tl <<= 1) << '\n';
  }
}
