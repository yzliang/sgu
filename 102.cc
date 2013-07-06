#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

bool prime[10001];
vector<int> p;

void CalculatePrimes() {
  for (int i = 0; i <= 10000; i++)
    prime[i] = true;
  for (int i = 2; i <= 10000; i++) {
    if (!prime[i])
      continue;
    p.push_back(i);
    for (int j = i + i; j <= 10000; j += i)
      prime[j] = false;
  }
}

int main() {
  CalculatePrimes();
  int n;
  cin >> n;
  if (prime[n]) {
    cout << n - 1 << endl;
    return 0;
  }
  int ans = n;
  for (int i = 0; i < p.size() && p[i] <= floor(sqrt(n)); i++) {
    if (n % p[i] == 0)
      ans = ans / p[i] * (p[i] - 1);
  }
  cout << ans << endl;
  return 0;
}
