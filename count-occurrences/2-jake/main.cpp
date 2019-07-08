#include <functional>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

typedef unsigned int uint;
typedef std::unordered_map<uint, uint> Map;
typedef Map::value_type Pair;
typedef std::function<bool(Pair, Pair)> Comparator;

bool comp(const Pair& elem1, const Pair& elem2) {
  if (elem1.second == elem2.second) {
    return elem1.first < elem2.first;
  } else {
    return elem1.second < elem2.second;
  }
}

int main() {
  Map raw;
  uint x;
  std::ifstream in("numbers");
  while (in >> x, in.good()) {
    raw[x]++;
  }
  in.close();

  std::set<Pair, Comparator> sorted(raw.cbegin(), raw.cend(), comp);
  std::ofstream out("test");
  for (const Pair& elem : sorted) {
    out << elem.second << " " << elem.first << std::endl;
  }
}

