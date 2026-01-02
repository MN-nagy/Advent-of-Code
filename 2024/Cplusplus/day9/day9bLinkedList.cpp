// same solution but with a doubly linked-list to avoid the O(N) insert
// ~O(N)

#include <cstddef>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define REAL "day9.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())
#define FGI vector<list<pair<int, int>>::iterator>

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input File Error!\n";
    return 1;
  }

  string line;
  file >> line;

  list<pair<int, int>> disk;
  FGI files;
  int c = 0;
  for (size_t i = 0; i < line.length(); ++i) {
    int l = line[i] - '0';
    if (i % 2 == 0) {
      disk.push_back({c, l});
      files.push_back(prev(disk.end()));
      c++;
    } else {
      disk.push_back({-1, l});
    }
  }

  // gap cache
  FGI gs(10, disk.begin());
  for (int cr = c - 1; cr >= 0; --cr) {
    auto f = files[cr];
    int len = f->second;
    auto gap = gs[len];

    while (gap != disk.end() && gap != f) {
      if (gap->first == -1 && gap->second >= f->second) {
        gs[len] = gap;

        int def = gap->second - f->second;

        f->first = -1;
        gap->first = cr;
        gap->second = f->second;

        if (def > 0) {
          disk.insert(next(gap), {-1, def});
        }

        break;
      }

      gap++;
    }

    // if no gaps found
    if (gap == f) {
      // mark the current size to skip;
      gs[len] = disk.end();
    }
  }

  long long total = 0;
  int idx = 0;
  for (auto const &v : disk) {
    idx += v.second;
    if (v.first != -1) {
      for (int i = idx - 1; i >= idx - v.second; --i) {
        total += (long long)i * v.first;
      }
    }
  }

  cout << total << '\n';

  return 0;
}
