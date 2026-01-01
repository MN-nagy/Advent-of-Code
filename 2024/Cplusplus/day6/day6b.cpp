#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#define REAL "day6.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input!!!!!!!\n";
    return 1;
  }

  vector<string> grid;

  string line;
  while (getline(file, line)) {
    grid.push_back(line);
  }

  int r = 0;
  int c = 0;
  for (auto i = 0; i < sz(grid); ++i) {
    for (auto j = 0; j < sz(grid[0]); ++j) {
      if (grid[i][j] == '^') {
        r = i;
        c = j;
        goto found;
      }
    }
  }

found:;

  int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1}, dir = 0;

  unordered_set<int> visited;
  while (true) {
    visited.insert(r * 1000 + c);

    if (r + dr[dir] < 0 || r + dr[dir] >= sz(grid) || c + dc[dir] < 0 ||
        c + dc[dir] >= sz(grid[0])) {
      break;
    }

    if (grid[r + dr[dir]][c + dc[dir]] == '#') {
      dir = (dir + 1) % 4;
      continue;
    }

    r += dr[dir];
    c += dc[dir];
  }

  cout << visited.size() << '\n';

  return 0;
}
