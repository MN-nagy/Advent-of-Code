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
  for (int r = 1; r < sz(grid) - 1; ++r) {
    for (int c = 1; c < sz(grid[r]) - 1; ++c) {

      if (grid[r][c] == 'A') {
        char TL = grid[r - 1][c - 1];
        char BR = grid[r + 1][c + 1];
        char TR = grid[r - 1][c + 1];
        char BL = grid[r + 1][c - 1];

        bool d1 = ((TL == 'M' && BR == 'S') || (TL == 'S' && BR == 'M'));
        bool d2 = ((TR == 'M' && BL == 'S') || (TR == 'S' && BL == 'M'));

        if (d1 && d2) {
          total++;
        }
      }
    }
  }

  cout << total << '\n';

  return 0;
}
