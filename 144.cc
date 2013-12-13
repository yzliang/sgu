#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int x, y;
  double z;
  cin >> x >> y >> z;
  double l = (y - x) * 60;
  double prob = 1 - (1 - z / l) * (1 - z / l);
  cout << fixed << setprecision(7) << prob << endl;
  return 0;
}
