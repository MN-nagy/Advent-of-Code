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
        int current_r = an1.first;
        int current_c = an1.second;
        while (current_r >= 0 && current_r < R && current_c >= 0 &&
               current_c < C) {
          antinodes[current_r][current_c] = true;
          current_r -= dr;
          current_c -= dc;
        }

        // antinode 2
        int current_r2 = an2.first;
        int current_c2 = an2.second;

        while (current_r2 >= 0 && current_r2 < R && current_c2 >= 0 &&
               current_c2 < C) {
          antinodes[current_r2][current_c2] = true;
          current_r2 += dr;
          current_c2 += dc;
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
