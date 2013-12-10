#include <iostream>
using namespace std;

int n, p, b;
int a[100], x[100];

int extended_euclid(int a, int b, int& x, int& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  } else if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    int x0;
    int y0;
    int d = extended_euclid(b, a % b, x0, y0);
    x = y0;
    y = x0 - a / b * y0;
    return d;
  }
}

bool compute() {
  int d = 0;
  int t;
  for (int i = 0; i < n; i++) {
    a[i] %= p;
    // d = a[0]*x[0] + ... + a[i-1]*x[i-1]) = gcd(a[0],...,a[i-1])
    // t * (a[0]*x[0] + ... + a[i-1]*x[i-1]) + a[i]*x[i] = gcd(d,a[i])
    d = extended_euclid(d, a[i], t, x[i]);
    // modulo by P
    d %= p;
    x[i] %= p;
    t %= p;
    for (int j = 0; j < i; j++)
      x[j] = (x[j] * t) % p;
  }
  // (a[0]*x[0] + ... + a[n]*x[n]) % p = gcd(a[0...n]) % p
  // t * (a[0]*x[0] + ... + a[n]*x[n]) + y * p = gcd(a[...], p)
  int y;
  d = extended_euclid(d, p, t, y);
  if (b % d != 0) return false;
  t %= p;
  for (int i = 0; i < n; i++) {
    x[i] = ((x[i] * t) % p * (b / d)) % p;
    if (x[i] < 0) x[i] += p;
  }
  return true;
}

int main() {
  cin >> n >> p >> b;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  if (compute()) {
    cout << "YES" << endl;
    cout << x[0];
    for (int i = 1; i < n; i++)
      cout << ' ' << x[i];
    cout << endl;
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
