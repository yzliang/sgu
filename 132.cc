#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int m, n, num_states;
int row, source;
char map[71][10];
/* f[i][s1][s2]: row 0~(i-1) are well-covered. row (i-1) is fixed. */
int f[2][128][128];  
const int BIG = 1000;
int s0, s1, s2;

void read_input() {
  cin >> m >> n;
  for (int i = 0; i < m; i++)
    cin >> map[i];
}

inline bool is_set(int x, int pos) {
  return x & (1 << pos);
}

inline void set(int& x, int pos) {
  x |= (1 << pos);
}

inline void clear(int& x, int pos) {
  x &= ~(1 << pos);
}

void expand(int pos, int num_add) {
  if (pos == n) {
    f[(row + 1) % 2][s1][s2] = min(f[(row + 1) % 2][s1][s2], source + num_add);
  } else if (is_set(s1, pos) || map[row][pos] == '*') {
    expand(pos + 1, num_add);
  } else {
    // we know that cell (row, pos) is empty.
    if (map[row + 1][pos] == '.') {
      set(s1, pos);
      set(s2, pos);
      expand(pos + 1, num_add + 1);
      clear(s1, pos);
      clear(s2, pos);
    }
    if (pos + 1 < n && !is_set(s1, pos + 1) && map[row][pos + 1] == '.') {
      set(s1, pos);
      set(s1, pos + 1);
      expand(pos + 2, num_add + 1);
      clear(s1, pos);
      clear(s1, pos + 1);
    }
    // what if not cover cell (row, pos) ?
    if ((pos == 0 || map[row][pos - 1] == '*' || is_set(s1, pos - 1)) &&
        (row == 0 || map[row - 1][pos] == '*' || is_set(s0, pos))) {
      expand(pos + 1, num_add);
    }
  }
}

int main() {
  read_input();
  num_states = pow(2, n);
  for (int i = 0; i < n; i++)
    map[m][i] = '*';
  for (int i = 0; i < num_states; i++)
    for (int j = 0; j < num_states; j++)
      f[0][i][j] = BIG;
  f[0][num_states - 1][0] = 0;
  for (row = 0; row < m; row++) {
    for (int i = 0; i < num_states; i++)
      for (int j = 0; j < num_states; j++)
        f[(row + 1) % 2][i][j] = BIG;
    for (int i = 0; i < num_states; i++)
      for (int j = 0; j < num_states; j++) {
        source = f[row % 2][i][j];
        if (source == BIG) continue;
        s0 = i;
        s1 = j;
        s2 = 0;
        expand(0, 0);
      }
  }
  int ans = BIG;
  for (int i = 0; i < num_states; i++)
    ans = min(ans, f[m % 2][i][0]);
  cout << ans << endl;
  return 0;
}
