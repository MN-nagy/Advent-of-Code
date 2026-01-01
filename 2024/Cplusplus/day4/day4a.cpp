#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define REAL "day4.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Error in Text file\n";
    return 1;
  }

  vector<vector<char>> grid;
  string line;
  while (getline(file, line)) {
    vector<char> row;
    for (auto &c : line) {
      row.push_back(c);
    }

    grid.push_back(row);
  }

  long long total = 0;

  const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int r = 0; r < sz(grid); ++r) {
    for (int c = 0; c < sz(grid[r]); ++c) {

      if (grid[r][c] == 'X') {
        for (int d = 0; d < 8; d++) {
          bool match = true;

          for (int k = 1; k < 4; k++) {
            int nr = r + dr[d] * k;
            int nc = c + dc[d] * k;

            if (nr < 0 || nr >= sz(grid) || nc < 0 || nc >= sz(grid[r]) ||
                grid[nr][nc] != "XMAS"[k]) {
              match = false;
              break;
            }
          }
          if (match)
            total++;
        }
      }
    }
  }

  cout << total << '\n';

  return 0;
}
