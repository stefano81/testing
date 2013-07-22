#include <iostream>

int main(int argc, char *argv[]) {
  char *p = "test";
  char *q = "test";

  if (p == q)
    std::cout << "one!" <<std::endl;
  else
    std::cout << "two!" <<std::endl;
}
