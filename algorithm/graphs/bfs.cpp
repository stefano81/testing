#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <functional>
#include <set>
#include <iostream>

struct node {
  unsigned id;
  bool visited;
  std::set<unsigned> adj;
};

std::vector<node> generate(unsigned n, unsigned m) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned> distribution(0, n);
  auto rand = std::bind(distribution, generator);
  std::vector<node> graph;

  for (unsigned i = 0; i < n; ++i) {
    graph.push_back({i, false, {}});
  }

  for (unsigned i = 0; i < m; ++i) {
    
  }

}

int main(int argc, char* argv[]) {
  if (3 != argc) return 1;
  unsigned n = std::stoul(argv[1]),
    m = std::stoul(argv[2]);

  std::vector<node> graph = generate(n, m);

  bft(graph, 0);

  return 0;
}
