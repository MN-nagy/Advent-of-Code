#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REAL "day6.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input File problem\n";
    return 1;
  }

  vector<string> grid;
  string line;
  while (getline(file, line)) {
    grid.push_back(line);
  }

  int r = 0, c = 0;
  for (int i = 0; i < sz(grid); ++i) {
    for (int j = 0; j < sz(grid[0]); ++j) {
      if (grid[i][j] == '^') {
        r = i;
        c = j;
        goto found;
      }
    }
  }

found:;

  int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1}, dir = 0;
  vector<vector<bool>> visited(sz(grid), vector<bool>(sz(grid[0]), false));

  long count = 0;
  while (true) {
    if (visited[r][c] == false) {
      visited[r][c] = true;
      count++;
    }

    int nr = r + dr[dir];
    int nc = c + dc[dir];

    if (nr < 0 || nr >= sz(grid) || nc < 0 || nc >= sz(grid[0])) {
      break;
    }

    if (grid[nr][nc] == '#') {
      dir = (dir + 1) % 4;
      continue;
    }

    r = nr;
    c = nc;
  }

  cout << count << '\n';

  return 0;
}
