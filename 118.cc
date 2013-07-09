#include <iostream>
using namespace std;

int num[1000];

inline int DigitRoot(int x) {
  if (x < 10)
    return x;
  int ret = 0;
  for (; x > 0; x /= 10)
    ret += x % 10;
  return ret < 10 ? ret : DigitRoot(ret);
}

int main() {
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int n;
    cin >> n;
    for (int j = 0; j < n; j++)
      cin >> num[j];
    int ans = 0;
    for (int j = n - 1; j >= 0; j--)
      ans = DigitRoot(ans * DigitRoot(num[j]) + DigitRoot(num[j]));
    cout << ans << endl;
  }
  return 0;
}
