#include <set>

class node {
 public:
 node(const unsigned &i, const bool& v = false, const int & c = 1) : id{i}, visit{v}, cost{c} {/*adj = {};*/};

  //  std::set<node> adj;
  bool visit;
  int cost;
  unsigned id;
};
