#include <cmath>
#include <iostream>
#include <stdint.h>
using namespace std;

int64_t extended_euclid(int64_t a, int64_t b, int64_t& x, int64_t& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    int64_t x1, y1;
    int64_t d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
  }
}

int64_t compute(int64_t a, int64_t b, int64_t c, int64_t x1, int64_t x2,
                int64_t y1, int64_t y2) {
  if (y1 > y2 || x1 > x2) return 0;
  if (a == 0 && b == 0) {
    if (c == 0)
      return (int64_t) (y2 - y1 + 1) * (x2 - x1 + 1);
    else
      return 0;
  } else if (a == 0) {
    if (c % b == 0 && c / b >= y1 && c / b <= y2)
      return x2 - x1 + 1;
    else
      return 0;
  } else if (b == 0) {
    if (c % a == 0 && c / a >= x1 && c / a <= x2)
      return y2 - y1 + 1;
    else
      return 0;
  }
  // Unification: a * x + b * y = -c, a > 0
  c = -c;
  if (a < 0) {
    a = -a;
    b = -b;
    c = -c;
  }
  int64_t x, y;
  int64_t d = extended_euclid(a, abs(b), x, y);
  if (b < 0) y = -y;
  // ax + by = d
  if (c % d != 0) return 0;
  // solution space:
  //   x = {(c/d)x0 + (b/d)*k}, x1<=x<=x2
  //   y = {(c/d)y0 - (a/d)*k}, y1<=y<=y2
  double upper = (double) (x2 - c / d * x) / (b / d);
  double lower = (double) (x1 - c / d * x) / (b / d);
  if (b < 0) {
    double temp = upper;
    upper = lower;
    lower = temp;
  }
  upper = min(upper, (double) (c / d * y - y1) / (a / d));
  lower = max(lower, (double) (c / d * y - y2) / (a / d));
  upper = floor(upper);
  lower = ceil(lower);
  return upper >= lower ? upper - lower + 1 : 0;
}

int main() {
  int64_t a, b, c;
  int64_t x1, x2, y1, y2;
  cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
  cout << compute(a, b, c, x1, x2, y1, y2) << endl;
  return 0;
}
