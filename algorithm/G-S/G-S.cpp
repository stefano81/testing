#include <vector>
#include <map>
#include <random>
#include <memory>
#include "person.h"
#include <iostream>
#include <functional>

std::vector<person> generate(const unsigned & n) {
  std::vector<person> people;
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  auto rand = std::bind(distribution, generator);

  for (int i = 0; i < n; ++i) {
    person p(i);

    for (int j = 0; j < n; ++j) {
        p.set_preference(j, rand());
    }
    people.push_back(p);
  }

  return people;
}

int main(int argc, char *argv[]) {
  unsigned n = atoi(argv[1]);

  auto men = generate(n);
  auto women = generate(n);

  std::map<unsigned, std::set<unsigned>> tried;
  std::map<unsigned, person> couple;

  while (0 != men.size()) {
    std::cout << men.size() << std::endl;

    auto m = men.back();
    auto tried_m = tried[m.get_id()];

    if (n < tried_m.size()) {
      int wid = m.get_highest(tried[m.get_id()]);
      std::cout << "Trying " << m.get_id() << " with " << wid << std::endl;

      auto is_engaged = couple.find(wid);
    }
  }
}
