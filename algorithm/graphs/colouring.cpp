#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <functional>
#include <set>
#include <iostream>
#include <memory>

struct node {
  unsigned id;
  bool visited;
  std::set<unsigned> adj;
};

std::vector<std::shared_ptr<node>> generate(unsigned n, unsigned m) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<unsigned> distribution(0, n-1);
  auto rand = std::bind(distribution, generator);
  std::vector<std::shared_ptr<node>> graph;

  for (unsigned i = 0; i < n; ++i) {
    graph.push_back(std::shared_ptr<node>(new node{i, false, {}}));
  }

  for (unsigned i = 0; i < n; ++i) {
    int r;
    do {
      r = rand();
    } while (end(graph[i]->adj) != graph[i]->adj.find(r));

    graph[i]->adj.insert(r);
    graph[r]->adj.insert(i);
  }

  for (unsigned i = 2 * n; i < m; i +=2) {
    int r1, r2;
    do {
      r1 = rand();
    } while (n - 1 <= graph[r1]->adj.size());
    do {
      r2 = rand();
    } while (end(graph[r1]->adj) != graph[r1]->adj.find(r2));

    graph[r1]->adj.insert(r2);
    graph[r2]->adj.insert(r1);
  }
    
  return graph;
}	        
	    

void bft(std::vector<std::shared_ptr<node>>& graph, unsigned root) {
    std::vector<std::vector<unsigned>> L;

    for (auto i = begin(graph); end(graph) != i; ++i) {
      (*i)->visited = false;
    }
    graph[root]->visited = true;

    L.push_back(std::vector<unsigned>{root});

    int i = 0;
    std::cerr << "digraph tree {" << std::endl;
    while (! L[i].empty()) {
      L.push_back(std::vector<unsigned>{});

      for (auto k = begin(L[i]); end(L[i]) != k; ++k) {
	std::cerr << *k;
	for (auto j = begin(graph[*k]->adj); end(graph[*k]->adj) != j; ++j) {
	  if (!(graph[*j]->visited)) {
	    graph[*j]->visited = true;
	    L[i+1].push_back(*j);
	    std::cerr << "-> " << *j;
	  }
	}
	std::cerr << std::endl;
      }
      ++i;
    }
    std::cerr << "}" << std::endl;
}

int main(int argc, char* argv[]) {
  if (3 != argc) return 1;
  unsigned n = std::stoul(argv[1]),
    m = std::stoul(argv[2]);

  auto graph = generate(n, m);

  std::cout << "graph test {" << std::endl;
  for (auto i = begin(graph); end(graph) != i; ++i) {
    std::cout << (*i)->id;

    for (auto j = begin((*i)->adj); end((*i)->adj) != j; ++j) {
      std::cout << " -> " << *j ;
    }
    std::cout << std::endl;
  }
  std::cout << "}" << std::endl;

  bft(graph, 0);

  return 0;
}
