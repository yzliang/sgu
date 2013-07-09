#include <iostream>
using namespace std;

int PowerMod(int x, int m, int k) {
  if (m == 1)
    return x % k;
  int half = PowerMod(x, m / 2, k);
  int ret = half * half % k;
  if (m % 2)
    ret = ret * x % k;
  return ret;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  int total = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (PowerMod(x, m, k) == 0)
      total++;
  }
  cout << total << endl;
  return 0;
}
