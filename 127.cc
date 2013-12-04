#include <iostream>
using namespace std;

int k, n;
int count[10];

int main() {
  char number[5];
  cin >> k >> n;
  for (int i = 0; i < n; i++) {
    cin >> number;
    count[number[0] - '0']++;
  }
  int total = 2;
  for (int i = 0; i < 10; i++)
    total += (count[i] + k - 1) / k;
  cout << total << endl;
  return 0;
}
