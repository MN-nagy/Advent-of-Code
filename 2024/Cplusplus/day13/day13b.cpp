#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

#define REAL "day13.txt"
#define TEST "test.txt"
#define sz(x) ((int)x.size())

ll const V = 10000000000000;

void solvep2() {
  ll ax, ay, bx, by, px, py;
  ll t_tokens = 0;

  while (scanf("Button A: X+%lld, Y+%lld\n", &ax, &ay) == 2) {
    scanf("Button B: X+%lld, Y+%lld\n", &bx, &by);
    scanf("Prize: X=%lld, Y=%lld\n", &px, &py);

    px += V;
    py += V;

    ll det = ax * by - ay * bx;
    ll na = px * by - py * bx;
    ll nb = py * ax - px * ay;

    if (det == 0)
      continue;
    if (na % det != 0 || nb % det != 0)
      continue;

    ll a = na / det;
    ll b = nb / det;

    if (a < 0 || b < 0)
      continue;

    t_tokens += (a * 3 + b * 1);
  }

  cout << t_tokens << "\n";
}

int main() {
  freopen(REAL, "r", stdin);

  solvep2();

  return 0;
}
