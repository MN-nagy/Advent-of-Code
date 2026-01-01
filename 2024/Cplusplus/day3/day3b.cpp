#include <charconv>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

#define REAL "day3.txt"
#define TEST "test.txt"

int main(void) {
  ifstream file(REAL);

  if (!file) {
    cerr << "Error in Text file\n";
    return 1;
  }

  regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");

  bool enabled = true;
  long long total = 0;
  string line;
  while (getline(file, line)) {
    auto begin = sregex_iterator(line.begin(), line.end(), pattern);
    auto end = sregex_iterator();

    for (auto i = begin; i != end; ++i) {
      smatch match = *i;
      string str = match.str();

      if (str == "do()") {
        enabled = true;
      } else if (str == "don't()") {
        enabled = false;
      } else {
        if (enabled) {

          long long x, y;
          from_chars(&*match[1].first, &*match[1].second, x);
          from_chars(&*match[2].first, &*match[2].second, y);

          total += x * y;
        }
      }
    }
  }

  cout << total << '\n';

  return 0;
}
