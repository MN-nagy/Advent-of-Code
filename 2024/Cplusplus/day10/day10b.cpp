#include <fstream>
#include <iostream>
#include <queue>
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

// updated to solve the problem as well but DFS is cleaner
// int bfs(int r, int c) {
//   queue<ii> q;
//   int count = 0;
//   int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
//
//   q.push({r, c});
//
//   while (!q.empty()) {
//     ii cur = q.front();
//     q.pop();
//
//     int y = cur.first;
//     int x = cur.second;
//
//     for (int d = 0; d < 4; ++d) {
//       int nr = y + dr[d];
//       int nc = x + dc[d];
//
//       if (nr < 0 || nr >= R || nc < 0 || nc >= C)
//         continue;
//
//       if (map[nr][nc] == map[y][x] + 1) {
//         if (map[nr][nc] == 9)
//           count++;
//
//         q.push({nr, nc});
//       }
//     }
//   }
//
//   return count;
// }

// two function dps
// void dfsRec(ii s, int &count) {
//
//   int r = s.first;
//   int c = s.second;
//   int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
//   for (int d = 0; d < 4; d++) {
//     int nr = r + dr[d];
//     int nc = c + dc[d];
//
//     if (nr < 0 || nr >= R || nc < 0 || nc >= C)
//       continue;
//
//     if (map[nr][nc] == map[r][c] + 1) {
//       if (map[nr][nc] == 9)
//         count++;
//       dfsRec({nr, nc}, count);
//     }
//   }
// }
//
// int dfs(int r, int c) {
//   int count = 0;
//   dfsRec({r, c}, count);
//
//   return count;
// }

int dfs(int r, int c) {
  if (map[r][c] == 9)
    return 1;

  int t_depth = 0;
  int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};

  for (int d = 0; d < 4; ++d) {
    int nr = r + dr[d];
    int nc = c + dc[d];

    if (nr >= 0 && nr < R && nc >= 0 && nc < C)
      if (map[nr][nc] == map[r][c] + 1)
        t_depth += dfs(nr, nc);
  }

  return t_depth;
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
    total += dfs(p.first, p.second);
  }

  cout << total << '\n';

  return 0;
}
