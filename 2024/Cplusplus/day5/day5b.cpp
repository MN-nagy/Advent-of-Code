#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define REAL "day5.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

bool rules[100][100];
int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Text file -_- \n";
    return 1;
  }

  vector<vector<int>> update;

  string line;
  while (getline(file, line) && !line.empty()) {
    stringstream ss(line);
    int x, y;
    char d;
    ss >> x >> d >> y;
    rules[x][y] = true;
  }

  while (getline(file, line)) {
    stringstream ss(line);
    vector<int> row;
    int val;

    while (ss >> val) {
      row.push_back(val);
      if (ss.peek() == ',')
        ss.ignore();
    }

    update.push_back(row);
  }

  long long total = 0;

  for (auto &r : update) {
    bool valid = true;

    for (int i = 0; i < sz(r); ++i) {
      for (int j = i + 1; j < sz(r); ++j) {
        if (rules[r[j]][r[i]]) {
          valid = false;
          break;
        }
      }
      if (!valid)
        break;
    }

    if (!valid) {
      sort(r.begin(), r.end(), [&](int a, int b) { return rules[a][b]; });

      total += r[r.size() / 2];
    }
  }

  cout << total << '\n';

  return 0;
}
