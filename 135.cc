#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  if (n % 2 == 0)
    cout << (n / 2) * (n + 1) + 1 << endl;
  else
    cout << (n + 1) / 2 * n + 1 << endl;
  return 0;
}
