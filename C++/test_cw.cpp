#include <iostream>
#include <cctype>

int main(int argc, char **argv) {
  uint64_t ui64 = 1;
  unsigned long tl = 1;

  for (int i = 0; i < 64; ++i) {
    std::cout << "uint_64 " << (ui64 <<=1) << '\n';
    std::cout << "long    " << (tl <<= 1) << '\n';
  }
}
