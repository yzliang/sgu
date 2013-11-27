#include <stdint.h>
#include <iostream>
using namespace std;

int main() {
  int k;
  cin >> k;
  int64_t sum = 0, a = 0, b = 1;
  for (int i = 0; i < k; i++) {
    int64_t c = a + b;
    a = b;
    b = c;
    sum += a;
  }
  cout << sum << endl;
  return 0;
}
