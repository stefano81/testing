#include "person.h"
#include <functional>
#include <utility>

bool person::prefers(const person & m, const person & m1) {
  return get_preference(m.get_id()) > get_preference(m1.get_id());
}

double person::get_preference(const unsigned & oid) {
  return preferences[oid];
}

void person::set_preference(const unsigned & oid, const double & val) {
  preferences[oid] = val;
}

unsigned person::get_id() const {
  return id;
}

unsigned person::get_highest(const std::set<unsigned> & tried) {
  unsigned max_id{0};
  double max_val{0.0};

  for (auto i = begin(preferences); i != end(preferences); ++i) {
    if (end(tried) == tried.find(i->first)) {
      // not tried yet
      if (max_val < i->second) {
	max_id = i->first;
	max_val = i->second;
      }
    }
  }

  return max_id;
}
