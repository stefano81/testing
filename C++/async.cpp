#include <future>
#include <iostream>
#include <vector>

int main() {    
  std::vector<std::future<void>> fs;
  for (int i = 0; i < 100; ++i) {
    fs.push_back(std::async([](int m) { std::cout << (m + 1) << std::endl;}, i));
  }
  std::cout << "In main" << std::endl;
  for (auto f = begin(fs); end(fs) != f; ++f)
    f->get();
    //std::cout << f->get() << std::endl;
}
