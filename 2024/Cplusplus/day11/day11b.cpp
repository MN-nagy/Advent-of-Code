// use freq map as using a linked-list will cause your pc to expload before you
// get any anwers -_-

#include <fstream>
#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

#define REAL "day11.txt"
#define TEST "test.txt"
#define sz(x) ((int)x.size())

int const G = 75;

ll digits(ll n) {
  int d = 1;
  while (n >= 10) {
    n /= 10;
    d++;
  }
  return d;
}

map<ll, ll> stones;
int main() {
  ifstream F(REAL);

  if (!F) {
    cerr << "Input!!!!\n";
    return 1;
  }

  ll t;
  while (F >> t) {
    stones[t]++;
  }

  int f = 0;
  while (f < G) {
    map<ll, ll> nc;
    for (auto &p : stones) {
      ll d = digits(p.first);
      switch (p.first) {
      case 0:
        nc[1] += p.second;
        continue;
      default:
        if (d % 2 == 0) {
          ll div = 1;
          for (int k = 0; k < d / 2; k++)
            div *= 10;
          ll l = p.first / div;
          ll r = p.first % div;
          nc[l] += p.second;
          nc[r] += p.second;
          continue;
        }

        nc[p.first * 2024] += p.second;
      }
    }
    stones = nc;
    f++;
  }

  ll count = 0;
  for (auto &p : stones) {
    count += p.second;
  }

  cout << count << '\n';

  return 0;
}
