#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

struct Segment {
  int x1, y1;
  int x2, y2;
};

int k, x0, y0;
Segment s[10000];

void read_input() {
  cin >> k;
  for (int i = 0; i < k; i++)
    cin >> s[i].x1 >> s[i].y1 >> s[i].x2 >> s[i].y2;
  cin >> x0 >> y0;
}

bool on_segment(int x, int y, Segment& s) {
  if (s.x1 == s.x2)
    return x == s.x1 && y >= min(s.y1, s.y2) && y <= max(s.y1, s.y2);
  else
    return y == s.y1 && x >= min(s.x1, s.x2) && x <= max(s.x1, s.x2);
}

bool on_border() {
  for (int i = 0; i < k; i++) {
    if (on_segment(x0, y0, s[i])) return true;
  }
  return false;
}

// Test a ray from (x0, y0) to (+inf, y0)
bool inside() {
  int num_cross = 0;
  pair<int, int> point;
  for (int i = 0; i < k; i++) {
    if (s[i].x1 == s[i].x2) {
      if (s[i].x1 < x0) continue;
      if (y0 <= max(s[i].y1, s[i].y2) && y0 > min(s[i].y1, s[i].y2))
        num_cross++;
    }
    // All segments that are parallel to the x-axis are considered disjoint.
  }
  return num_cross % 2 == 1;
}

int main() {
  read_input();
  cout << (on_border() ? "BORDER" : (inside() ? "INSIDE" : "OUTSIDE")) << endl;
  return 0;
}
