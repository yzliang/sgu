#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Point {
  int x, y;
  int h_id, v_id;  // Id of its horizontal and vertical companions.
};

struct Event {
  int type;  // 1) horizontal remove; 2) vertical check; 3) horizontal add; 
  int id;  // Point id.
  Event(int type, int id) : type(type), id(id) {}
};

int n;
Point points[10000];
vector<Event> events;
int counts[70000];

bool compare_points_by_x(int id1, int id2) {
  if (points[id1].x != points[id2].x)
    return points[id1].x < points[id2].x;
  else
    return points[id1].y < points[id2].y;
}

bool compare_points_by_y(int id1, int id2) {
  if (points[id1].y != points[id2].y)
    return points[id1].y < points[id2].y;
  else
    return points[id1].x < points[id2].x;
}

// Find neighbors for each point.
// Return true iff. all points are used.
bool find_companions() {
  vector<int> ids(n);
  for (int i = 0; i < n; i++) ids[i] = i;
  sort(ids.begin(), ids.end(), compare_points_by_x);
  int i = 0;
  while (i < n) {
    int j = i + 1;
    while (j < n && points[ids[j]].x == points[ids[i]].x)
      j++;
    if ((j - i) % 2 != 0)
      return false;  // Must be even number of points with the same x.
    for (int k = i; k < j; k += 2) {
      points[ids[k]].v_id = ids[k + 1];
      points[ids[k + 1]].v_id = ids[k];
    }
    i = j;
  }
  sort(ids.begin(), ids.end(), compare_points_by_y);
  i = 0;
  while (i < n) {
    int j = i + 1;
    while (j < n && points[ids[j]].y == points[ids[i]].y)
      j++;
    if ((j - i) % 2 != 0)
      return false;  // Must be even number of points with the same y.
    for (int k = i; k < j; k += 2) {
      points[ids[k]].h_id = ids[k + 1];
      points[ids[k + 1]].h_id = ids[k];
    }
    i = j;
  }
  return true;
}

// Return true if all points form a single connected-components.
bool check_integrity() {
  vector<bool> visit(n, false);
  queue<int> q;
  int total = 0;
  q.push(0);
  visit[0] = true;
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    total++;
    if (!visit[points[head].h_id]) {
      visit[points[head].h_id] = true;
      q.push(points[head].h_id);
    }
    if (!visit[points[head].v_id]) {
      visit[points[head].v_id] = true;
      q.push(points[head].v_id);
    }
  }
  return total == n;
}

// Sort events by x-coordinates and types.
// Order of types: remove < check < add.
bool compare_events(const Event& e1, const Event& e2) {
  if (points[e1.id].x != points[e2.id].x)
    return points[e1.id].x < points[e2.id].x;
  else
    return e1.type < e2.type;
}

void make_events() {
  for (int i = 0; i < n; i++) {
    if (points[i].x < points[points[i].h_id].x)
      events.push_back(Event(3, i));
    else
      events.push_back(Event(1, i));
    if (points[i].y < points[points[i].v_id].y)
      events.push_back(Event(2, i));
  }
  sort(events.begin(), events.end(), compare_events);
}

int segment_sum() {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (points[i].x < points[points[i].h_id].x)
      ans += points[points[i].h_id].x - points[i].x;
    if (points[i].y < points[points[i].v_id].y)
      ans += points[points[i].v_id].y - points[i].y;
  }
  return ans;
}

void tree_add(int id, int l, int r, int key, int val) {
  while (l < r) {
    counts[id] += val;
    int m = l + (r - l) / 2;
    if (key <= m) {
      id = id * 2 + 1;
      r = m;
    } else {
      id = id * 2 + 2;
      l = m + 1;
    }
  }
  counts[id] += val;
}

// If there exists a value in interval [p, q].
bool tree_contains(int id, int l, int r, int p, int q) {
  if (p <= l && q >= r) return counts[id] > 0;
  if (counts[id] == 0) return false;
  int m = l + (r - l) / 2;
  if (p <= m && q >= l && tree_contains(id * 2 + 1, l, m, p, q))
    return true;
  if (p <= r && q > m && tree_contains(id * 2 + 2, m + 1, r, p, q))
    return true;
  return false;
}

const int MIN_Y = -10000;
const int MAX_Y = 10000;

bool check_intersection() {
  for (int i = 0; i < events.size(); i++) {
    if (events[i].type == 1) {
      tree_add(0, MIN_Y, MAX_Y, points[events[i].id].y, -1);
    } else if (events[i].type == 2) {
      int y_min = points[events[i].id].y;
      int y_max = points[points[events[i].id].v_id].y;
      if (y_min + 1 > y_max - 1) continue;
      if (tree_contains(0, MIN_Y, MAX_Y, y_min + 1, y_max - 1)) return false;
    } else {
      tree_add(0, MIN_Y, MAX_Y, points[events[i].id].y, 1);
    }
  }
  return true;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> points[i].x >> points[i].y;
  if (!find_companions() || !check_integrity()) {
    cout << 0 << endl;
    return 0;
  }
  make_events();
  if (!check_intersection()) {
    cout << 0 << endl;
    return 0;
  }
  cout << segment_sum() << endl;
  return 0;
}
