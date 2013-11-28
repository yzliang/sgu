#include <iostream>
using namespace std;

int n;
int a[5][5];
int b[5][5];
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

void read_input() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> b[i][j];
}

bool check_equal(int row, int col) {
  int larger = 0;
  for (int i = 0; i < 4; i++)
    if (a[row + dx[i]][col + dy[i]] > a[row][col]) larger++;
  return larger == b[row][col];
}

bool check(int row, int col) {
  int larger = 0;
  for (int i = 0; i < 2; i++)
    if (a[row + dx[i]][col + dy[i]] > a[row][col]) larger++;
  return larger <= b[row][col];
}

bool search(int row, int col) {
  if (row == n + 1) {
    for (int i = 1; i <= n; i++)
      if (!check_equal(n, i)) return false;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n - 1; j++) cout << a[i][j] << ' ';
      cout << a[i][n] << endl;
    }
    return true;
  }
  int n_row = col == n ? row + 1 : row;
  int n_col = col == n ? 1 : col + 1;
  if (a[row][col] != -1)
    return search(n_row, n_col);
  for (int i = 0; i < 10; i++) {
    a[row][col] = i;
    if (row > 1 && !check_equal(row - 1, col)) continue;
    if (!check(row, col)) continue;
    if (search(n_row, n_col)) return true;
  }
  a[row][col] = -1;
  return false;
}

int main() {
  read_input();
  // Init.
  for (int i = 0; i <= n + 1; i++)
    for (int j = 0; j <= n + 1; j++)
      a[i][j] = -1;
  // Fill the known place.
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] == 0)
        a[i][j] = 9;
      else if (b[i][j] == 4)
        a[i][j] = 0;
    }
  }
  if (!search(1, 1)) cout << "NO SOLUTION" << endl;
  return 0;
}
