#include <set>
#include <map>

class person {
private:
  unsigned id;
  std::map<unsigned, double> preferences;

public:
 person(const unsigned & iid = 0) : id(iid) {};
 person(const person & other) : id(other.id), preferences(other.preferences) {};
  double get_preference(const unsigned & oid);
  void set_preference(const unsigned & oid, const double & val);
  unsigned get_id();
  unsigned get_highest(const std::set<unsigned> & tried);
};
