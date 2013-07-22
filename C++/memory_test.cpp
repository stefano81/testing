#include <iostream>

int main(int argc, char *argv[]) {
  const unsigned int size = 1024 * 1024 * 1024;
  for (unsigned int i = 0; true; ++i) {
    try {
      new char[size];
    } catch (std::bad_alloc) {
      std::cout << "done at " << (i * size) << std::endl;
    }
  }
}
