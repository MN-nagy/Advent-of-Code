#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define REAL "day8.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

const int MAX_N = 150;
int antinodes[MAX_N][MAX_N];
int R, C;
int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input File Error\n";
    return 1;
  }

  unordered_map<char, vector<pair<int, int>>> poses;
  string line;
  int r = 0;
  while (getline(file, line)) {
    C = sz(line);
    stringstream ss(line);
    for (int c = 0; c < sz(line); c++) {
      char a = line[c];
      if (a != '.')
        poses[a].push_back({r, c});
    }
    r++;
  }
  R = r;

  for (auto &pair : poses) {
    for (int i = 0; i < sz(pair.second); i++) {
      auto an1 = pair.second[i];
      for (int j = i + 1; j < sz(pair.second); j++) {
        auto an2 = pair.second[j];
        int dr = an2.first - an1.first;
        int dc = an2.second - an1.second;

        // antinode 1
        int nr1 = an1.first - dr;
        int nc1 = an1.second - dc;

        if (nr1 >= 0 && nr1 < R && nc1 >= 0 && nc1 < C) {
          antinodes[nr1][nc1] = true;
        }

        // antinode 2
        int nr2 = an2.first + dr;
        int nc2 = an2.second + dc;

        if (nr2 >= 0 && nr2 < R && nc2 >= 0 && nc2 < C) {
          antinodes[nr2][nc2] = true;
        }
      }
    }
  }

  int count = 0;
  for (auto &r : antinodes) {
    for (auto &c : r) {
      if (c == true)
        count++;
    }
  }

  cout << count << '\n';

  return 0;
}
