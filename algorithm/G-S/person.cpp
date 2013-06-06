#include "person.h"
#include <functional>
#include <utility>

double person::get_preference(const unsigned & oid) {
  return preferences[oid];
}

void person::set_preference(const unsigned & oid, const double & val) {
  preferences[oid] = val;
}

unsigned person::get_id() {
  return id;
}

unsigned person::get_highest(const std::set<unsigned> & tried) {
  unsigned max_id{0};
  double max_val{0.0};

  for (auto i = begin(preferences); i != end(preferences); ++i) {
    if (end(tried) != tried.find(i))
      if (max_val < it->second) {
	max_id = it->first;
	max_val = it->second;
      }
  }
}
