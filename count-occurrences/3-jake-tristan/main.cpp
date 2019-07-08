#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdlib>

typedef std::pair<uint32_t, uint32_t> Pair;

bool comp(const Pair& elem1, const Pair& elem2) {
  if (elem1.second == elem2.second) {
    return elem1.first < elem2.first;
  } else {
    return elem1.second < elem2.second;
  }
}

int main() {
  std::ifstream in("numbers");
  uint32_t counts[50000] = {};
  std::string l;
  while (in) {
    std::getline(in, l);
    int x = atoi(l.c_str());
    counts[x - 1]++;
  }

  std::vector<Pair> v;
  for (uint i = 0; i < 50000; i++) {
    if (counts[i] > 0) {
      v.push_back(Pair(i + 1, counts[i]));
    }
  }

  std::sort(v.begin(), v.end(), comp);
  std::ofstream f("test");
  for (const Pair& elem : v) {
    f << elem.second << " " << elem.first << "\n";
  }
}
