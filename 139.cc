#include <iostream>
using namespace std;

int main() {
  int a[16];
  int zx, zy;
  int reverse_count = 0;
  for (int i = 0; i < 16; i++) {
    cin >> a[i];
    if (a[i] == 0) {
      zx = i / 4;
      zy = i % 4;
    }
    for (int j = 0; j < i; j++)
      if (a[j] > a[i]) reverse_count++;
  }
  cout << (((3 - zx + 3 - zy) % 2 != reverse_count % 2) ? "YES" : "NO") << endl;
  return 0;
}
