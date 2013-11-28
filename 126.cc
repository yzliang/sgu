#include <cstdlib>
#include <iostream>
using namespace std;

int gcd(int a, int b) {
  int temp;
  while (b > 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int main(int argc, char** argv) {
  int a, b;
  cin >> a >> b;
  if (a == 0 || b == 0) {
    cout << 0 << endl;
    return 0;
  }
  int moves = 1;
  while (a != b) {
    if ((a % 4 + b % 4) % 4 != 0) {
      cout << -1 << endl;
      return 0;
    }
    if (a >= b) {
      a -= b;
      b *= 2;
    } else {
      b -= a;
      a *= 2;
    }
    int common = gcd(a, b);
    a /= common;
    b /= common;
    moves++;
  }
  cout << moves << endl;
  return 0;
}
