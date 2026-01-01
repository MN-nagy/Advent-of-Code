#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define REAL "day2.txt"
#define TEST "test.txt"

int isvalid(const vector<int> &r) {
  int dec = 0;
  int inc = 0;

  for (size_t i = 1; i < r.size(); i++) {
    long long cur = r[i] - r[i - 1];

    if (abs(cur) < 1 || 3 < abs(cur))
      return 0;

    if (cur > 0)
      inc = 1;
    if (cur < 0)
      dec = 1;

    if (dec && inc)
      return 0;
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
    }
  }

  cout << r_total << '\n';

  return 0;
}
