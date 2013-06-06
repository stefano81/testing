#include <vector>
#include <map>
#include <random>
#include <memory>
#include "person.h"
#include <iostream>
#include <functional>
#include <set>
#include <chrono>

std::vector<person> generate(const unsigned & n) {
  std::vector<person> people;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
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

  std::map<unsigned, std::set<unsigned>> tried;
  std::map<unsigned, person> couple;

  auto men = generate(n);
  auto women = generate(n);

  while (0 != men.size()) {
    auto m = men.front();
    men.erase(begin(men));

    auto& tried_m = tried[m.get_id()];

    if (n > tried_m.size()) {
      int wid = m.get_highest(tried[m.get_id()]);
      tried_m.insert(wid);

      auto is_engaged = couple.find(wid);

      if (end(couple) == is_engaged) {
	couple[wid] = m;
      } else {
	if (women[wid].prefers(m, is_engaged->second)) {
	  men.push_back(is_engaged->second);
	  couple[wid] = m;
	} else {
	  men.push_back(m);
	}
      }
    }
  }

  for (auto i = begin(couple); end(couple) != i; ++i) {
    std::cout << "(" << i->first << ", " << i->second.get_id() << ")" << std::endl;
  }

  return 0;
}
