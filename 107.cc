#include <algorithm>
#include <iostream>
using namespace std;

int n, ans;
int d[9], res[10];

void Search(int pos) {
  if (pos == 9) {
    ans++;
  }
  else {
    int carry = res[pos];
    for (d[pos] = (pos == n - 1 ? 1 : 0);
        d[pos] <= (pos >= n ? 0 : 9);
        d[pos]++) {
      // Recompute the result of res[pos]
      res[pos] = carry;
      for (int i = 0; i <= pos; i++)
        res[pos] += d[i] * d[pos -i];
      res[pos + 1] = res[pos] / 10;
      res[pos] %= 10;
      // Check.
      if (res[pos] != pos + 1)
        continue;
      Search(pos + 1);
    }
  }
}

int main() {
  cin >> n;
  // Backtracking.
  Search(0);

  if (n > 9) {
    ans *= 9;
    cout << ans;
    for (int i = 0; i < n - 10; i++)
      cout << '0';
    cout << endl;
  } else {
    cout << ans << endl;
  }
  return 0;
}
