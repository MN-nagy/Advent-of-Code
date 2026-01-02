#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define REAL "day9.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input File Error!\n";
    return 1;
  }

  string line;
  file >> line;

  vector<pair<int, int>> disk;
  int c = 0;
  for (size_t i = 0; i < line.length(); ++i) {
    if (i % 2 == 0) {
      disk.push_back({c, line[i] - '0'});
      c++;
    } else {
      disk.push_back({-1, line[i] - '0'});
    }
  }

  for (int cr = c; cr >= 0; --cr) {
    int fi = -1;
    for (int i = sz(disk) - 1; i >= 0; --i) {
      if (disk[i].first == cr) {
        fi = i;
        break;
      }
    }

    for (int j = 0; j < fi; ++j) {
      if (disk[j].first == -1 && disk[j].second >= disk[fi].second) {
        int def = disk[j].second - disk[fi].second;
        if (!def) {
          swap(disk[j].first, disk[fi].first);
          break;
        }

        disk[fi].first = -1;
        disk[j] = {cr, disk[fi].second};
        disk.insert(disk.begin() + j + 1, {-1, def});

        break;
      }
    }
  }

  long long total = 0;
  int idx = 0;
  for (auto const &v : disk) {
    idx += v.second;
    if (v.first == -1) {
      continue;
    }

    for (int i = idx - 1; i >= idx - v.second; --i) {
      total += (long long)i * v.first;
    }
  }

  cout << total << '\n';

  return 0;
}
