#include <cmath>
#include <iostream>
using namespace std;

#define PI 3.1415926535897932 

struct Point {
  double x, y;
};

double Distance(Point& p1, Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Nasty math.
Point GetCenter(int n, int n1, int n2, Point& p1, Point& p2) {
  double angle = PI * (n - 2) / n;

  // Draw a segment from n1 to n2, forming angle1.
  double angle1 = (PI * (n2 - n1 - 1) - angle * (n2 - n1 - 1)) / 2;

  // Left or right?
  if (n2 - n1 <= n / 2) {
    double angle2 = angle / 2 - angle1;

    // Rotate with reference to p1, clockwise.
    double x = (p2.x - p1.x) / (2 * cos(angle2));
    double y = (p2.y - p1.y) / (2 * cos(angle2));
    Point center;
    center.x = p1.x + cos(angle2) * x + sin(angle2) * y;
    center.y = p1.y -sin(angle2) * x + cos(angle2) * y;
    return center;
  }
  else {
    double angle2 = angle1 - angle / 2;

    // Rotate with reference to p1, counterclockwise.
    double x = (p2.x - p1.x) / (2 * cos(angle2));
    double y = (p2.y - p1.y) / (2 * cos(angle2));
    Point center;
    center.x = p1.x + cos(angle2) * x - sin(angle2) * y;
    center.y = p1.y + sin(angle2) * x + cos(angle2) * y;
    return center;
  }
}

int main() {
  int n, n1, n2;
  Point p1, p2;
  cin >> n >> n1 >> n2;
  cin >> p1.x >> p1.y >> p2.x >> p2.y;

  Point center = GetCenter(n, n1, n2, p1, p2);
  double angle = PI * 2 / n;
  Point ans[151];
  ans[n1].x = p1.x - center.x;
  ans[n1].y = p1.y - center.y;
  ans[n2].x = p2.x - center.x;
  ans[n2].y = p2.y - center.y;
  for (int i = n1 - 1; i >= 1; i--) {
    double x = ans[i + 1].x;
    double y = ans[i + 1].y;
    ans[i].x = cos(angle) * x - sin(angle) * y;
    ans[i].y = sin(angle) * x + cos(angle) * y;
  }
  for (int i = n1 + 1; i <= n; i++) {
    if (i == n2)
      continue;
    double x = ans[i - 1].x;
    double y = ans[i - 1].y;
    ans[i].x = cos(angle) * x + sin(angle) * y;
    ans[i].y = - sin(angle) * x + cos(angle) * y;
  }

  cout << fixed;
  cout.precision(6);
  for (int i = 1; i <= n; i++) {
    ans[i].x += center.x;
    ans[i].y += center.y;
    if (fabs(ans[i].x) < 1e-7)
      ans[i].x = 0;
    if (fabs(ans[i].y) < 1e-7)
      ans[i].y = 0;
    cout << ans[i].x << ' ' << ans[i].y << endl;
  }
  return 0;
}
