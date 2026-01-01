#include <algorithm>
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

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int total = 0;
  for (auto i{0u}; i < left.size(); i++) {
    total += std::abs(left[i] - right[i]);
  }

  cout << total << endl;
  return 0;
}
