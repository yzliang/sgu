#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  long a, b, c;
  long x1, x2, y1, y2;
  cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;

  if (x1 > x2 || y1 > y2) {
    cout << 0 << endl;
    return 0;
  }

  if (a == 0 && b == 0) {
    cout << (c == 0 ? (x2 - x1 + 1) * (y2 - y1 + 1) : 0) << endl;
    return 0;
  }

  long min_x, max_x, min_y, max_y;
  if (a != 0) {
    double v1 = static_cast<double>(-b * y1 - c) / a;
    double v2 = static_cast<double>(-b * y2 - c) / a;
    if (v1 <= v2) {
      min_x = ceil(v1);
      max_x = floor(v2);
    } else {
      min_x = ceil(v2);
      max_x = floor(v1);
    }
  }

  if (b != 0) {
    double v1 = static_cast<double>(-a * x1 - c) / b;
    double v2 = static_cast<double>(-a * x2 - c) / b;
    if (v1 <= v2) {
      min_y = ceil(v1);
      max_y = floor(v2);
    } else {
      min_y = ceil(v2);
      max_y = floor(v1);
    }
  }

  min_x = max(min_x, x1);
  max_x = min(max_x, x2);
  min_y = max(min_y, y1);
  max_y = min(max_y, y2);

  // Horizontal.
  if (a == 0) {
    cout << (min_y == max_y ? x2 - x1 + 1 : 0) << endl;
    return 0;
  }

  // Vertical.
  if (b == 0) {
    cout << (min_x == max_x ? y2 - y1 + 1 : 0) << endl;
    return 0;
  }

  if (min_x > max_x || min_y > max_y) {
    cout << 0 << endl;
    return 0;
  }

  // a * x = -c (mod b)
  return 0;
}
