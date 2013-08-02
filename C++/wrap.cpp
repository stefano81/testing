#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <future>

using namespace std;

template<class T> class wrapper {
private:
  mutable T t;
  mutable mutex m;
public:
  wrapper( T t_ = T{}) : t{t_}{}
  template<typename F> auto operator()(F f) -> decltype(f(t)) {
    lock_guard<mutex> _{m};
    return f(t);
  }
};

int main (int argc, char *argv[]) {
  wrapper<string> s{"start\n"};
  vector<future<void>> v;

  for (int i = 0; i < 5; ++i) {
    cerr << "starting ";
    cerr << i;
    cerr << "\n";

    v.push_back(async([&,i] {
	  s([=](string& s) {
	      s += to_string(i) + "" + to_string(i);
	      s += "\n";
	    });
	  s([](string& s){
	      cout << s;
	    });
	}));
  }

  for (auto& f : v)
    f.wait();
}
