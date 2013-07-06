#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int n, k;

struct Index {
  int order;  // Original order.
  int index;  // Index of self-number.
  int num;
} s[5000];

int CompareIndex(const void* e1, const void* e2) {
  const Index* p1 = static_cast<const Index*>(e1);
  const Index* p2 = static_cast<const Index*>(e2);
  return p1->index - p2->index;
}

int CompareOrder(const void* e1, const void* e2) {
  const Index* p1 = static_cast<const Index*>(e1);
  const Index* p2 = static_cast<const Index*>(e2);
  return p1->order - p2->order;
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    s[i].order = i;
    cin >> s[i].index;
  }
  qsort(s, k, sizeof(Index), CompareIndex);

  int total = 0, next = 0;
  bool buffer[64];
  int index = 0;
  for (int i = 0; i < 64; i++)
    buffer[i] = true;
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    for (int x = i; x > 0; x /= 10)
      sum += x % 10;
    buffer[(index + sum) & 63] = false;
    if (buffer[index]) {
      total++;
      while (next < k && s[next].index == total) {
        s[next].num = i;
        next++;
      }
    } else {
      buffer[index] = true;
    }
    index = (index + 1) & 63;
  }
  cout << total << endl;
  qsort(s, k, sizeof(Index), CompareOrder);
  cout << s[0].num;
  for (int i = 1; i < k; i++)
    cout << ' ' << s[i].num;
  cout << endl;
  return 0;
}
