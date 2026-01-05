#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

#define REAL "day14.txt"
#define TEST "test.txt"
int const W = 101, H = 103;

void solve() {
  int px, py, vx, vy;
  int pxf = 0, pyf = 0;
  int mX = W / 2, mY = H / 2;
  int window = W * H;
  int bt = 0;
  vector<vector<int>> robs;

  while (scanf("p=%d,%d v=%d,%d\n", &px, &py, &vx, &vy) == 4) {
    robs.push_back({px, py, vx, vy});
  }

  ll lsf = INT_MAX;
  for (int i = 0; i < window; i++) {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (auto &v : robs) {
      pxf = ((v[0] + v[2] * i) % W + W) % W;
      pyf = ((v[1] + v[3] * i) % H + H) % H;

      if (pxf != mX && pyf != mY) {
        if (pxf < mX) {
          if (pyf < mY)
            q1++;
          else
            q2++;
        } else {
          if (pyf < mY)
            q3++;
          else
            q4++;
        }
      }
    }
    ll a = (ll)q1 * q2 * q3 * q4;
    if (a < lsf) {
      lsf = a;
      bt = i;
    }
  }

  cout << bt << '\n';
}

int main() {

  freopen(REAL, "r", stdin);

  solve();
  return 0;
}
