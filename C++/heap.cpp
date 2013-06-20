/*
 * g++ -std=c++11 heap.cpp -o heap
 * ./heap N
 * > + v   // add v
 * > -     // remove root
 * > @     // peek root
 * > #     // size of the heap
 * > !     // quit
 */

#include <iostream>
#include <cmath>
#include <string>

class heap {
private:
  long long * key;
  unsigned long length;

  int leftChild(const int &i) const {
    return 2 * i;
  }

  int rightChild(const int &i) const {
    return 2 * i + 1;
  }

  int parent(const int &i) const {
    return std::floor(i / 2);
  }

  void swap(const int &i, const int &j) {
    auto t = key[i];
    key[i] = key[j];
    key[j] = t;
  }

  void heapify_up(const int &i) {
    if (0 != 1) {
      int j = parent(i);
      if (key[i] < key[j]) {
	swap(i, j);
	heapify_up(j);
      }
    }
  }

  void heapify_down(const int &i) {
    if (leftChild(i) >= length)
      return;

    int j = -1;
    if (leftChild(i) < length - 1)
      j =  key[leftChild(i)] < key[rightChild(i)] ? leftChild(i) : rightChild(i);
    else if (leftChild(i) == length - 1)
      j = leftChild(i);
    
    if (key[i] > key[j]) {
      swap(i, j);
      heapify_down(j);
    }
  }
  
public:
  heap(const int & N) : length{0} {
    key = new long long[N];

    for (int i = 0; i < N; ++i) key[i] = -1;
  }
  ~heap() {
    delete key;
  }

  void add(const unsigned long & v) {
    key[length] = v;
    heapify_up(length);
    ++length;
  }

  unsigned long peek() {
    return key[0];
  }

  unsigned long del() {
    auto v = key[0];

    key[0] = key[--length];
    key[length] = -1;

    heapify_down(0);

    return v;
  }

  unsigned long size() const {
    return length;
  }
};

int main(int argc, char *argv[]) {
  if (2 != argc)
    return 1;

  heap myheap{stol(argv[1])};

  unsigned char command;
  unsigned long v;
  do {
    std::cout << ">";
    std::cin >> command;

    switch(command) {
    case '+':
      std::cin >> v;
      myheap.add(v);
      break;
    case '-':
      std::cout << myheap.del() << std::endl;
      break;
    case '#':
      std::cout << myheap.size() << std::endl;
      break;
    case '@':
      std::cout << myheap.peek() << std::endl;
      break;
    case '!':
      std::cout << "Goodbye" << std::endl;
      break;
    default:
      std::cout << "Unknown command" << std::endl;
      break;
    }

  } while ('!' != command);

  return 0;
}
