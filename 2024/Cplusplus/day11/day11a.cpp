#include <fstream>
#include <iostream>
#include <list>

using namespace std;

typedef list<int>::iterator li;

#define REAL "day11.txt"
#define TEST "test.txt"
#define sz(x) ((int)x.size())

int const G = 25;

int digits(long long n) {
  int d = 1;
  while (n >= 10) {
    n /= 10;
    d++;
  }
  return d;
}

list<long long> stones;
int main() {
  ifstream F(REAL);

  if (!F) {
    cerr << "Input!!!!\n";
    return 1;
  }

  long long t;
  while (F >> t) {
    stones.push_back(t);
  }

  int f = 0;
  while (f < G) {
    for (auto it = stones.begin(); it != stones.end();) {
      int d = digits(*it);
      switch (*it) {
      case 0:
        *it = 1;
        it++;
        continue;
      default:
        if (d % 2 == 0) {
          long long div = 1;
          for (int k = 0; k < d / 2; k++)
            div *= 10;
          string s = to_string(*it);
          long long l = *it / div;
          long long r = *it % div;
          stones.insert(it, l);
          stones.insert(it, r);
          it = stones.erase(it);
          continue;
        }

        *it *= 2024;
        it++;
      }
    }
    f++;
  }
  long long count = 0;
  for (auto it = stones.begin(); it != stones.end(); ++it) {
    count++;
  }

  cout << count << '\n';

  return 0;
}
