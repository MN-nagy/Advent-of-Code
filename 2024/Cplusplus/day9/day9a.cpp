#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define REAL "day9.txt"
#define TEST "test.txt"

#define sz(x) ((int)x.size())

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Input File Error!\n";
    return 1;
  }

  string line;
  file >> line;

  vector<int> disk;
  int c = 0;
  for (size_t i = 0; i < line.length(); ++i) {
    if (i % 2 == 0) {
      for (int j = 0; j < line[i] - '0'; ++j) {
        disk.push_back(c);
      }
      c++;
    } else {
      for (int j = 0; j < line[i] - '0'; ++j) {
        disk.push_back(-1);
      }
    }
  }

  int s = 0;
  int e = sz(disk) - 1;

  while (true) {
    while (disk[s] != -1)
      ++s;
    while (disk[e] == -1)
      --e;

    if (s >= e)
      break;

    swap(disk[s], disk[e]);
  }

  long long cheksum = 0;
  for (int i = 0; i < sz(disk); ++i) {
    if (disk[i] == -1)
      break;
    cheksum += (long long)i * disk[i];
  }

  cout << cheksum << '\n';

  return 0;
}
