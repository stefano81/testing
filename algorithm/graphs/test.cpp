#include "node.h"
#include <vector>
#include <set>
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
  auto n1 = std::shared_ptr<node>(new node(1));
  auto n2 = std::shared_ptr<node>(new node(2));

  //auto n1 = std::unique_ptr<node>(1);
  //auto n2 = std::unique_ptr<node>(2);

  std::vector<std::shared_ptr<node>> nodes;
  nodes.push_back(n1);
  nodes.push_back(n2);

  n1->visit = true;

  for (auto i = begin(nodes); end(nodes) != i; ++i) {
    std::cout << (*i)->id << ' ' << (*i)->visit << std::endl;
  }
  
}
