#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int n;
Point points[400];

void read_polygon() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> points[i].x >> points[i].y;
}

int cross_product(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int sgn(int x) {
  return x == 0 ? 0 : (x > 0 ? 1 : -1);
}

/* p3 or p4 on (p1, p2) are also considered as cross! */
bool weak_cross(Point& p1, Point& p2, Point& p3, Point& p4) {
  return cross_product(p1, p2, p3) * cross_product(p1, p2, p4) <= 0 &&
      (sgn(cross_product(p3, p4, p1)) ^ sgn(cross_product(p3, p4, p2))) == -2;
}

bool couter_clockwise_compare(const Point& p1, const Point& p2) {
  return cross_product(points[0], p1, p2) > 0;
}

void swap(Point& p1, Point& p2) {
  Point temp = p1;
  p1 = p2;
  p2 = temp;
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

bool point_on_segment(const Point& p, const Point& p1, const Point& p2) {
  if (!point_on_line(p, p1, p2)) return false;
  return (p.x - p1.x) * (p.x - p2.x) + (p.y - p1.y) * (p.y - p2.y) <= 0;
}

double dis(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/* return -1 inside the polygon;
 *         0 on the polygon;
 *         1 outside the polygon.
 */
int point_on_polygon(const Point& p) {
  int num_cross = 0;
  Point p1, p2;
  for (int i = 0; i < n; i++) {
    p1 = points[i];
    p2 = points[(i + 1) % n];
    if (point_on_segment(p, p1, p2)) return 0;
  }
  Point pp = p;
  pp.x += 100000;  // simulate a ray (x, y) -> (x + 1e5, y)
  for (int i = 0; i < n; i++) {
    p1 = points[i];
    p2 = points[(i + 1) % n];
    // p and pp should be on both sides of [p1, p2].
    if ((sgn(cross_product(p1, p2, p)) ^ sgn(cross_product(p1, p2, pp))) != -2)
      continue;
    int s1 = sgn(cross_product(p, pp, p1));
    int s2 = sgn(cross_product(p, pp, p2));
    num_cross += ((s1 ^ s2) == -2) || (s1 == 0 && s2 == -1) ||
        (s1 == -1 && s2 == 0);
  }
  return num_cross % 2 == 0 ? 1 : -1;
}

double compute_intercept(Point& p1, Point& p2, Point& p3, Point& p4) {
  double k = (double) cross_product(p3, p4, p1) /
      ((p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x));
  return k * dis(p1, p2);
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
    double len = 0;
    int pos1 = point_on_polygon(p1);
    int pos2 = point_on_polygon(p2);
    if (pos1 + pos2 < 0) {  // (-1, -1), (0, -1)
      len = dis(p1, p2);
    } else if (pos1 == 0 && pos2 == 0) {  // (0, 0)
      if (!segment_on_polygon(p1, p2))
        len = dis(p1, p2);
    } else if (pos1 * pos2 <= 0) {  // (-1, 1), (0, 1)
      // Need to exclude the case where [p1, p2] is on one line of the polygon.
      if (pos1 * pos2 < 0 || !segment_on_polygon(p1, p2)) {
        if (pos1 > pos2) swap(p1, p2);  // inside/on_board -> outside.
        for (int j = 0; j < n; j++) {
          Point& p3 = points[j];
          Point& p4 = points[(j + 1) % n];
          if (weak_cross(p1, p2, p3, p4)) {
            len = compute_intercept(p1, p2, p3, p4);
            break;
          }
        }
      }
    } else {  // (1, 1)
      if (!segment_on_polygon(p1, p2)) {
        double max_k = -1, min_k = 1e10;
        bool has_cross = false;
        for (int j = 0; j < n; j++) {
          Point& p3 = points[j];
          Point& p4 = points[(j + 1) % n];
          if (!weak_cross(p1, p2, p3, p4)) continue;
          has_cross = true;
          double k = compute_intercept(p1, p2, p3, p4);
          max_k = max(max_k, k);
          min_k = min(min_k, k);
        }
        if (has_cross) {
          len = max_k - min_k;
          if (len < 1e-6) len == 0;
        }
      }
    }
    cout << fixed << setprecision(2) << len << endl;
  }
  return 0;
}
