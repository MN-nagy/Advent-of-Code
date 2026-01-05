#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

#define REAL "day14.txt"
#define TEST "test.txt"
int const W = 101, H = 103;

void solve() {
  int px, py, vx, vy;
  int pxf = 0, pyf = 0;
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  int mX = W / 2, mY = H / 2;

  while (scanf("p=%d,%d v=%d,%d\n", &px, &py, &vx, &vy) == 4) {
    pxf = ((px + vx * 100) % W + W) % W;
    pyf = ((py + vy * 100) % H + H) % H;

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

  ll ans = (ll)q1 * q2 * q3 * q4;
  cout << ans << '\n';
}

int main() {

  freopen(REAL, "r", stdin);

  solve();
  return 0;
}
