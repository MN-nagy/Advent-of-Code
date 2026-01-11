#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REAL "day15.txt"
#define TEST "test.txt"
#define sz(x) ((int)x.size())

vector<string> grid;
string moves = "";
int startR, startC;

void solve() {

  string s;
  int r = 0;
  while (getline(cin, s)) {
    if (s.empty())
      break;
    for (int c = 0; c < sz(s); c++) {
      if (s[c] == '@') {
        startC = c;
        startR = r;
      }
    }
    r++;
    grid.push_back(s);
  }

  string c;
  while (cin >> c) {
    moves += c;
  }
}

int main() {
  freopen(TEST, "r", stdin);

  solve();
  return 0;
}
