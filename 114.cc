#include <algorithm>
#include <iostream>
using namespace std;

int n, total;

struct City {
  int x;
  int p;

  bool operator<(const City& that) const {
    return x < that.x;
  }
} c[15000];

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> c[i].x >> c[i].p;
    total += c[i].p;
  }
  sort(c, c + n, less<City>());

  int i = 0, step = (total + 1) / 2;
  while (step > c[i].p) step -= c[i++].p;
  cout << c[i].x << ".00000" << endl;
  return 0;
}
