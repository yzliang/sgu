#include <iostream>
using namespace std;

const int beginning = 6;  // Dimanche, 31.12.2000.
const int num[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
  int n, m;
  cin >> n >> m;

  // Range check.
  if (m > 12 || n > num[m]) {
    cout << "Impossible" << endl;
    return 0;
  }

  int total = 0;
  for (int i = 1; i < m; i++) total += num[i];
  total += n;
  cout << (beginning + total) % 7 + 1 << endl;
  return 0;
}
