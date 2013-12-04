#include <algorithm>
#include <iostream>
using namespace std;

struct Interval {
  int a, b;
  bool operator<(const Interval& that) const {
    if (a != that.a)
      return a < that.a;
    else
      return b > that.b;
  }
} ints[16000];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> ints[i].a >> ints[i].b;
  sort(ints, ints + n);
  int total = 1;
  for (int i = 1; i < n; i++) {
    if (ints[total - 1].a < ints[i].a)
      ints[total++] = ints[i];
  }
  int rest = 1;
  for (int i = 1; i < total; i++) {
    if (ints[i].b > ints[rest - 1].b)
      ints[rest++] = ints[i];
  }
  cout << n - rest << endl;
  return 0;
}
