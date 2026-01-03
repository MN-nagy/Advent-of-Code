#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

#define REAL "day12.txt"
#define TEST "test.txt"
#define sz(x) ((int)x.size())

const int MAX_N = 140;
char grid[MAX_N][MAX_N];
int R = MAX_N, C = MAX_N;
bool visited[MAX_N][MAX_N];
int const dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
int const drc[] = {-1, -1, 1, 1}, dcc[] = {-1, 1, 1, -1};

bool valid(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }

ll bfs(int r, int c) {
  ll corners = 0;
  ll area = 0;

  queue<ii> q;
  visited[r][c] = true;
  q.push({r, c});

  while (!q.empty()) {
    ii curr = q.front();
    q.pop();
    area++;

    int r = curr.first;
    int c = curr.second;
    char p = grid[r][c];

    for (int i = 0; i < 4; ++i) {
      int cr = drc[i];
      int cc = dcc[i];

      bool ver = valid(r + cr, c) && grid[r + cr][c] == p;
      bool hor = valid(r, c + cc) && grid[r][c + cc] == p;
      bool diag = valid(r + cr, c + cc) && grid[r + cr][c + cc] == p;

      if (!ver && !hor)
        ++corners;
      if (ver && hor && !diag)
        ++corners;
    }

    for (int d = 0; d < 4; d++) {
      int nr = r + dr[d];
      int nc = c + dc[d];

      if (valid(nr, nc)) {
        if (grid[nr][nc] != grid[r][c]) {
        } else {
          if (!visited[nr][nc]) {
            visited[nr][nc] = true;
            q.push({nr, nc});
          }
        }
      }
    }
  }

  return area * corners;
}

int main() {
  ifstream F(REAL);
  if (!F) {
    cerr << "Input !!\n";
    return 1;
  }

  string line;
  int r = 0;
  while (getline(F, line)) {
    C = sz(line);
    for (int c = 0; c < sz(line); ++c) {
      grid[r][c] = line[c];
    }
    ++r;
  }
  R = r;

  ll total = 0;
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      if (!visited[r][c]) {
        total += bfs(r, c);
      }
    }
  }

  cout << total << "\n";

  return 0;
}
