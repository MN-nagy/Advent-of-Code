#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define REAL "day7.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

bool check(int idx, long long c_val, vector<long long> &nums) {
  long long target = nums[0];

  if (idx == sz(nums))
    return c_val == target;

  if (c_val > target)
    return false;

  bool add = check(idx + 1, c_val + nums[idx], nums);
  bool mult = check(idx + 1, c_val * nums[idx], nums);

  if (add || mult)
    return true;
  return false;
}

int main(void) {
  ifstream file(REAL);
  if (!file) {
    cerr << "Input Error\n";
    return 1;
  }

  vector<vector<long long>> eqs;

  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    vector<long long> eq;
    long long n;
    while (ss >> n) {
      eq.push_back(n);
      if (ss.peek() == ':')
        ss.ignore();
    }

    eqs.push_back(eq);
  }

  long long t_cal = 0;
  for (auto &e : eqs) {
    if (check(2, e[1], e)) {
      t_cal += e[0];
    }
  }

  cout << t_cal << '\n';

  return 0;
}
