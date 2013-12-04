#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int n;
double x[10000], y[10000];

void draw_polygon(double sx, double sy) {
  cout << std::fixed;
  cout.precision(3);
  cout << sx << ' ' << sy << endl;
  for (int i = 0; i < n - 1; i++) {
    sx = 2 * x[i] - sx;
    sy = 2 * y[i] - sy;
    cout << sx << ' ' << sy << endl;
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  double x_sum = 0, y_sum = 0;
  int sign = 1;
  for (int i = n - 1; i >= 0; i--) {
    x_sum += sign * x[i];
    y_sum += sign * y[i];
    sign = -sign;
  }
  if (n % 2 == 0) {
    if (fabs(x_sum) < 1e-6 && fabs(y_sum) < 1e-6) {
      cout << "YES" << endl;
      draw_polygon(-1, 1);
    } else {
      cout << "NO" << endl;
    }
  } else {
      cout << "YES" << endl;
      draw_polygon(x_sum, y_sum);
  }
  return 0;
}
