#include <cmath>
#include <cstring>
#include <iostream>
#include <stdint.h>
using namespace std;

int m, n, num_states;
int row;
int64_t source;
int64_t f[2][512];
int s1, s2;

inline bool is_set(int x, int pos) {
  return x & (1 << pos);
}

inline void set(int& x, int pos) {
  x |= (1 << pos);
}

inline void clear(int& x, int pos) {
  x &= ~(1 << pos);
}

void expand(int pos) {
  if (pos == n) {
    f[(row + 1) % 2][s2] += source;
  } else if (s1 & (1 << pos)) {
    expand(pos + 1);
  } else {
    set(s1, pos);
    if (!is_set(s2, pos)) {
      set(s2, pos);
      expand(pos + 1);
      clear(s2, pos);
    }
    if (pos + 1 < n && !is_set(s1, pos + 1)) {
      set(s1, pos + 1);
      expand(pos + 1);
      clear(s1, pos + 1);
    }
    if (pos + 1 < n && !is_set(s1, pos + 1) && !is_set(s2, pos)) {
      set(s1, pos + 1);
      set(s2, pos);
      expand(pos + 1);
      clear(s1, pos + 1);
      clear(s2, pos);
    }
    if (pos + 1 < n && !is_set(s1, pos + 1) && !is_set(s2, pos + 1)) {
      set(s1, pos + 1);
      set(s2, pos + 1);
      expand(pos + 1);
      clear(s1, pos + 1);
      clear(s2, pos + 1);
    }
    if (pos > 0 && !is_set(s2, pos - 1) && !is_set(s2, pos)) {
      set(s2, pos - 1);
      set(s2, pos);
      expand(pos + 1);
      clear(s2, pos - 1);
      clear(s2, pos);
    }
    if (pos + 1 < n && !is_set(s2, pos) && !is_set(s2, pos + 1)) {
      set(s2, pos);
      set(s2, pos + 1);
      expand(pos + 1);
      clear(s2, pos);
      clear(s2, pos + 1);
    }
    clear(s1, pos);
  }
}

int main() {
  cin >> m >> n;
  num_states = pow(2, n);
  f[0][0] = 1;
  for (row = 0; row < m; row++) {
    memset(f[(row + 1) % 2], 0, sizeof(f[(row + 1) % 2]));
    for (int code = 0; code < num_states; code++) {
      if (f[row % 2][code] == 0) continue;
      source = f[row % 2][code];
      s1 = code;
      s2 = 0;
      expand(0);
    }
  }
  cout << f[m % 2][0] << endl;
  return 0;
}
