#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define REAL "day1.txt"
#define TEST "test.txt"

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Error in Text file\n";
    return 1;
  }

  vector<int> left;
  vector<int> right;

  int left_val;
  int right_val;
  while (file >> left_val >> right_val) {
    left.push_back(left_val);
    right.push_back(right_val);
  }

  // no id is > 100,000
  int r[100000] = {0};

  for (auto &x : right) {
    r[x]++;
  }

  long long total = 0;
  for (auto &i : left) {
    total += i * r[i];
  }

  cout << total << '\n';

  return 0;
}
