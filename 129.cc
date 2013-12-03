#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct Point {
  double x, y;
};

const double EPSILON = 1e-6;

int n;
Point points[400];

void read_polygon() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> points[i].x >> points[i].y;
}

double cross_product(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double sgn(double x) {
  return (fabs(x) < EPSILON) ? 0 : (x > 0 ? 1 : -1);
}

bool couter_clockwise_compare(const Point& p1, const Point& p2) {
  return cross_product(points[0], p1, p2) > 0;
}

void make_polygon() {
  int base = 0;  // index of the lowest-leftmost point.
  for (int i = 1; i < n; i++) {
    if (points[i].y < points[base].y || (points[i].y == points[base].y &&
                                         points[i].x < points[base].x))
      base = i;
  }
  swap(points[0], points[base]);
  sort(points + 1, points + n, couter_clockwise_compare);
}

bool point_on_line(const Point& p, const Point& p1, const Point& p2) {
  return (p2.x - p1.x) * (p.y - p1.y) == (p2.y - p1.y) * (p.x - p1.x);
}

double dis(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool segment_on_polygon(Point& p1, Point& p2) {
  for (int i = 0; i < n; i++) {
    Point& p3 = points[i];
    Point& p4 = points[(i + 1) % n];
    if (point_on_line(p1, p3, p4) && point_on_line(p2, p3, p4))
      return true;
  }
  return false;
}

int main() {
  read_polygon();
  make_polygon();
  int m;
  Point p1, p2;
  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    if (segment_on_polygon(p1, p2)) {
      cout << "0.00" << endl;
      continue;
    }
    // Extend the segment.
    int dx = p2.x - p1.x, dy = p2.y - p1.y;
    Point p3 = {p1.x - 30000 * dx, p1.y - 30000 * dy};
    Point p4 = {p2.x + 30000 * dx, p2.y + 30000 * dy};
    double k1 = 1e10, k2 = 1e10;
    for (int j = 0; j < n; j++) {
      Point& p5 = points[j];
      Point& p6 = points[(j + 1) % n];
      if (sgn(cross_product(p3, p4, p5)) *
          sgn(cross_product(p3, p4, p6)) <= 0 &&
          sgn(cross_product(p5, p6, p3)) *
          sgn(cross_product(p5, p6, p4)) <= 0) {
        // Compute the intercept.
        double k = cross_product(p5, p6, p1) /
          ((p2.x - p1.x) * (p6.y - p5.y) - (p2.y - p1.y) * (p6.x - p5.x));
        if (fabs(k - k1) < EPSILON || fabs(k - k2) < EPSILON) continue;
        if (k1 == 1e10)
          k1 = k;
        else
          k2 = k;
      }
    }
    if (k1 > k2) {
      double temp = k1;
      k1 = k2;
      k2 = temp;
    }
    if (k1 == 1e10 || k2 == 1e10 || k2 <= 0 || k1 >= 1) {
      cout << "0.00" << endl;
      continue;
    }
    k2 = min(k2, 1.0);
    k1 = max(k1, 0.0);
    cout << fixed << setprecision(2) << (k2 - k1) * dis(p1, p2) << endl;
  }
  return 0;
}
