#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define INPUT "input.txt"
#define TEST_INPUT "testinput.txt"

struct Matrix {
  vector<vector<int>> buttons;
  vector<int> target;
};

vector<string> parseFile(const string &filename);
vector<Matrix> parseMatrix(const vector<string> &content);
int solve(const vector<int> &target, const vector<vector<int>> &buttons);

int main(void) {
  vector<string> content = parseFile(INPUT);
  vector<Matrix> init_matrix = parseMatrix(content);

  int total_min = 0;

  for (auto m : init_matrix) {
    total_min += solve(m.target, m.buttons);
  }

  cout << total_min << endl;

  return 0;
}

vector<string> parseFile(const string &filename) {
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Error opeing file" << filename << "\n";
  }

  string line;
  vector<string> content;

  while (getline(file, line)) {
    content.push_back(line);
  }

  file.close();
  return content;
}

int solve(const vector<int> &target, const vector<vector<int>> &buttons) {
  int len_rows = target.size();
  int len_cols = buttons.size();
  vector<vector<int>> matrix;

  // transpose
  for (int r = 0; r < len_rows; r++) {
    vector<int> row;
    for (int c = 0; c < len_cols; c++) {
      row.push_back(buttons[c][r]);
    }
    row.push_back(target[r]);
    matrix.push_back(row);
  }

  // make the ladder
  vector<int> pivot_col(len_rows, -1);

  for (int row = 0, col = 0; row < len_rows && col < len_cols; row++, col++) {
    int pivot_row = row;

    while (pivot_row < len_rows && matrix[pivot_row][col] == 0) {
      pivot_row++;
    }

    if (pivot_row == len_rows) {
      // start ladder from next col
      row--;
      continue;
    }

    swap(matrix[row], matrix[pivot_row]);

    // clean above and below the the current step of the ladder
    pivot_col[row] = col;
    for (int r = 0; r < len_rows; r++) {
      if (r != row && matrix[r][col] == 1) {
        for (int c = col; c <= len_cols; c++) {
          matrix[r][c] ^= matrix[row][c];
        }
      }
    }
  }

  // getting free cols
  unordered_set<int> pivot_col_set(pivot_col.begin(), pivot_col.end());

  vector<int> free_cols;
  for (int c = 0; c < len_cols; c++) {
    if (pivot_col_set.find(c) == pivot_col_set.end()) {
      free_cols.push_back(c);
    }
  }

  int min_b_press = INT_MAX;
  int free_len = free_cols.size();
  int possible_comb = 1 << free_len;

  for (int pb = 0; pb < possible_comb; pb++) {
    vector<int> sol(len_cols, 0);

    for (int b = 0; b < free_len; b++) {
      if ((pb >> b) & 1) {
        sol[free_cols[b]] = 1;
      }
    }

    for (int r = len_rows - 1; r >= 0; r--) {
      int step = pivot_col[r];

      if (step == -1)
        continue; // it's a free col
      int step_val = matrix[r][len_cols];

      for (int c = step; c < len_cols; c++) {
        if (matrix[r][c] == 1) {
          step_val ^= sol[c];
        }
      }

      sol[step] = step_val;
    }

    int current_comb_presses = accumulate(sol.begin(), sol.end(), 0);
    min_b_press = min(min_b_press, current_comb_presses);
  }

  return min_b_press;
}

vector<Matrix> parseMatrix(const vector<string> &content) {
  regex light_pattern("\\{(.*?)\\}");
  regex button_pattern("\\((.*?)\\)");

  // lights vector
  auto str_vector = [](const string &s) {
    vector<int> vec;
    vec.reserve(s.size());

    for (char c : s)
      vec.push_back(c - '0');
    return vec;
  };

  // buttons
  auto ind_to_buttons = [&](const string &ind_str, int length) {
    vector<int> buttons(length, 0);

    regex comma(",");

    auto token_it =
        sregex_token_iterator(ind_str.begin(), ind_str.end(), comma, -1);
    auto token_end = sregex_token_iterator();

    for (; token_it != token_end; ++token_it) {
      int index = stoi(*token_it);
      if (index >= 0 && index < length)
        buttons[index] = 1;
    }

    return buttons;
  };

  vector<Matrix> init_matrix;
  transform(
      content.begin(), content.end(), back_inserter(init_matrix),
      [&](const string &val) -> Matrix {
        Matrix m;

        smatch lightMatch;
        if (regex_search(val, lightMatch, light_pattern)) {
          m.target = str_vector(lightMatch[1]);
        }

        auto begin = sregex_iterator(val.begin(), val.end(), button_pattern);
        auto end = sregex_iterator();

        for (; begin != end; ++begin) {
          m.buttons.push_back(ind_to_buttons((*begin)[1], m.target.size()));
        }

        return m;
      });

  return init_matrix;
}
