#include <iostream>
using namespace std;

int Code(int n, int x, int y) {
  return (x - 1) * n + y;
}

int main() {
  int n;
  cin >> n;
  int step = (n % 2 == 0) ? n + 1 : n;
  for (int i = 1; i <= n / 2; i++) {
    if (2 * i == n) {
      cout << step << ' ' << Code(n, i, i) << endl;
      step += 2;
      cout << step << ' ' << Code(n, i, i + 1) << ' ' << Code(n, i + 1, i);
      cout << endl;
      break;
    }
    // Even -> odd.
    cout << step;
    step += 2;
    for (int j = i; j <= n - i + 1; j++) {
      if ((i + j) % 2 == 0)
        cout << ' ' << Code(n, i, j);
      if ((n - i + 1 + j) % 2 == 0)
        cout << ' ' << Code(n, n - i + 1, j);
    }
    for (int j = i + 1; j < n - i + 1; j++) {
      if ((j + i) % 2 == 0)
        cout << ' ' << Code(n, j, i);
      if ((n - i + 1 + j) % 2 == 0)
        cout << ' ' << Code(n, j, n - i + 1);
    }
    cout << endl;

    // Odd -> even.
    cout << step;
    step += 2;
    for (int j = i; j <= n - i + 1; j++) {
      if ((i + j) % 2 != 0)
        cout << ' ' << Code(n, i, j);
      if ((n - i + 1 + j) % 2 != 0)
        cout << ' ' << Code(n, n - i + 1, j);
    }
    for (int j = i + 1; j < n - i + 1; j++) {
      if ((j + i) % 2 != 0)
        cout << ' ' << Code(n, j, i);
      if ((n - i + 1 + j) % 2 != 0)
        cout << ' ' << Code(n, j, n - i + 1);
    }
    cout << endl;
  }
  return 0;
}
