#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

#define REAL "day10.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

const int MAX_N = 60;
int map[MAX_N][MAX_N];
int R = MAX_N, C = MAX_N;

int bfs(int r, int c) {
  bool visited[MAX_N][MAX_N];
  memset(visited, 0, sizeof(visited));
  queue<ii> q;
  set<ii> seen;
  int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};

  visited[r][c] = true;
  q.push({r, c});

  while (!q.empty()) {
    ii cur = q.front();
    q.pop();

    int y = cur.first;
    int x = cur.second;

    for (int d = 0; d < 4; ++d) {
      int nr = y + dr[d];
      int nc = x + dc[d];

      if (nr < 0 || nr >= R || nc < 0 || nc >= C)
        continue;

      if (map[nr][nc] == map[y][x] + 1) {
        if (map[nr][nc] == 9)
          seen.insert({nr, nc});

        if (!visited[nr][nc]) {
          q.push({nr, nc});
          visited[nr][nc] = true;
        }
      }
    }
  }

  return seen.size();
}

int main() {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input file !!\n";
    return 1;
  }

  string line;
  vector<ii> zeros;
  int r = 0;
  while (getline(file, line)) {
    C = sz(line);
    for (int c = 0; c < sz(line); ++c) {
      map[r][c] = line[c] - '0';
      if (line[c] - '0' == 0) {
        zeros.push_back({r, c});
      }
    }
    ++r;
  }
  R = r;

  long long total = 0;
  for (auto &p : zeros) {
    total += bfs(p.first, p.second);
  }

  cout << total << '\n';

  return 0;
}
