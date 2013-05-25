#include <iostream>
#include <vector>
#include <string>

using std::string;

struct Pair {
  string name;
  double val;
};

std::vector<Pair> pairs;

double& value(const string& s) {
  for (int i = 0; i < pairs.size(); ++i)
    if (s == pairs[i].name)
      return pairs[i].val;

  Pair p = {s};
  pairs.push_back(p);

  return pairs[pairs.size() - 1].val;
}



int main(int argc, char *argv[]) {
  string s;

  while (std::cin >> s)
    ++value(s);

  for (auto p = pairs.begin(); p != pairs.end(); ++p)
    std::cout << p->name << "," << p->val << "\n";
}
