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

ll bfs(int r, int c) {
  ll perimeter = 0;
  ll area = 0;

  int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};

  queue<ii> q;
  visited[r][c] = true;
  q.push({r, c});

  while (!q.empty()) {
    ii curr = q.front();
    q.pop();
    area++;

    int r = curr.first;
    int c = curr.second;

    for (int d = 0; d < 4; d++) {
      int nr = r + dr[d];
      int nc = c + dc[d];

      if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
        if (grid[nr][nc] != grid[r][c]) {
          perimeter++;
        } else {
          if (!visited[nr][nc]) {
            visited[nr][nc] = true;
            q.push({nr, nc});
          }
        }
      } else {
        perimeter++;
      }
    }
  }

  return area * perimeter;
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
