#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define REAL "day2.txt"
#define TEST "test.txt"

// skip_idx wraps
int isvalid(const vector<int> &r, size_t skip_idx = -1) {
  int dec = 0, inc = 0;
  int prev = -1;

  for (size_t i = 0; i < r.size(); i++) {
    if (i == skip_idx)
      continue;

    if (prev != -1) {
      long long cur = r[i] - r[prev];

      if (abs(cur) < 1 || 3 < abs(cur))
        return 0;
      if (cur > 0)
        inc = 1;
      if (cur < 0)
        dec = 1;
      if (dec && inc)
        return 0;
    }

    prev = i;
  }

  return 1;
}

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Error in Text file\n";
    return 1;
  }

  vector<vector<int>> reps;

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    int level;
    vector<int> report;
    while (ss >> level) {
      report.push_back(level);
    }

    reps.push_back(report);
  }

  int r_total = 0;
  for (const auto &rep : reps) {
    if (isvalid(rep)) {
      r_total += 1;
    } else {
      for (auto i{0u}; i < rep.size(); i++) {

        if (isvalid(rep, i)) {
          r_total += 1;
          break;
        }
      }
    }
  }

  cout << r_total << '\n';

  return 0;
}
