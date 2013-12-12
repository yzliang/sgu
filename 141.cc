#include <cmath>
#include <iostream>
using namespace std;

int x1, x2, p, k;
int p1, n1, p2, n2;

int extended_euclid(int a, int b, int& x, int& y) {
  if (b == 0) {
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
  int a, b;
  // a*x1 + b*x2 = gcd(x1,x2)
  int d = extended_euclid(x1, x2, a, b);
  if (p % d != 0) return false;
  // Solution space:
  // P1 - N1 = a*(p/d) + r*(x2/d)
  // P2 - N2 = b*(p/d) - r*(x1/d)
  // P1 + N1 + P2 + N1 = k
  a = a * (p / d);
  b = b * (p / d);
  x1 /= d;
  x2 /= d;
  // Case 1: P1 >= N1, P2 >= N2
  double upper = (double) b / x1;
  double lower = (double) -a / x2;
  int r;
  if (x2 == x1) {
    if (a + b <= k && (k - a - b) % 2 == 0 && ceil(lower) <= floor(upper)) {
      r = ceil(lower);
      n1 = 0;
      n2 = (k - a - b) / 2;
      p1 = a + r * x2;
      p2 = n2 + b - r * x1;
      return true;
    }
  } else if (x2 > x1) {
    upper = min(upper, (double) (k - a - b) / (x2 - x1));
  } else {
    lower = max(lower, (double) (k - a - b) / (x2 - x1));
  }
  if (ceil(lower) <= floor(upper)) {
    r = ceil(lower);
    if ((k - a - b - r * (x2 - x1)) % 2 != 0) r++;
    if (r <= floor(upper) && (k - a - b - r * (x2 - x1)) % 2 == 0) {
      n1 = (k - a - b - r * (x2 - x1)) / 2;
      n2 = 0;
      p1 = n1 + a + r * x2;
      p2 = b - r * x1;
      return true;
    }
  }
  // Case 2: P1 >= N1, P2 <= N2
  upper = (double) (k - a + b) / (x1 + x2);
  lower = max((double) -a / x2, (double) b / x1);
  if (ceil(lower) <= floor(upper)) {
    r = ceil(lower);
    if ((k - a + b - r * (x2 + x1)) % 2 != 0) r++;
    if (r <= floor(upper) && (k - a + b - r * (x2 + x1)) % 2 == 0) {
      n1 = (k - a - r * x2 + b - r * x1) / 2;
      p2 = 0;
      p1 = n1 + a + r * x2;
      n2 = -(b - r * x1);
      return true;
    }
  }
  // Case 3: P1 <= N1, P2 >= N2
  upper = min((double) -a / x2, (double) b / x1);
  lower = (double) (b - a - k) / (x1 + x2);
  if (ceil(lower) <= floor(upper)) {
    r = ceil(lower);
    if ((k + (a + r * x2) - (b - r * x1)) % 2 != 0) r++;
    if (r <= floor(upper) && (k + (a + r * x2) - (b - r * x1)) % 2 == 0) {
      p1 = (k + (a + r * x2) - (b - r * x1)) / 2;
      n2 = 0;
      n1 = p1 - (a + r * x2);
      p2 = b - r * x1;
      return true;
    }
  }
  // Case 4: P1 <= N1, P2 <= N2
  upper = (double) -a / x2;
  lower = (double) b / x1;
  if (x1 == x2) {
    if (k + a + b >= 0 && (k + a + b) % 2 == 0 && ceil(lower) <= floor(upper)) {
      r = ceil(lower);
      p1 = (k + a + b) / 2;
      p2 = 0;
      n1 = p1 - (a + r * x2);
      n2 = p2 - (b - r * x1);
      return true;
    }
  } else if (x1 > x2) {
    upper = min(upper, (double) (k + a + b) / (x1 - x2));
  } else {
    lower = max(lower, (double) (k + a + b) / (x1 - x2));
  }
  if (ceil(lower) <= floor(upper)) {
    r = ceil(lower);
    if ((k + (a + r * x2) + (b - r * x1)) % 2 != 0) r++;
    p1 = (k + (a + r * x2) + (b - r * x1)) / 2;
    p2 = 0;
    n1 = p1 - (a + r * x2);
    n2 = -(b - r * x1);
    return true;
  }
  return false;
}

int main() {
  cin >> x1 >> x2 >> p >> k;
  if (compute()) {
    cout << "YES" << endl;
    cout << p1 << ' ' << n1 << ' ' << p2 << ' ' << n2 << endl;
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
