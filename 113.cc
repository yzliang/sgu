#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

bool is_prime[40000];
vector<int> primes;

void ComputePrimes() {
  for (int i = 0; i < 40000; i++) is_prime[i] = true;
  for (int i = 2; i < 40000; i++) {
    if (!is_prime[i]) continue;
    primes.push_back(i);
    for (int j = i + i; j < 40000; j += i) is_prime[j] = false;
  }
}

int main() {
  ComputePrimes();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    bool nearly = false;
    for (int j = 0; j < primes.size() && primes[j] <= sqrt(x); j++) {
      if (x % primes[j] != 0) continue;
      int p2 = x / primes[j];
      bool is_prime = true;
      for (int k = 0; k < primes.size() && primes[k] <= sqrt(p2); k++) {
        if (p2 % primes[k] == 0) {
          is_prime = false;
          break;
        }
      }
      if (is_prime) {
        nearly = true;
        break;
      }
    }
    cout << (nearly ? "Yes" : "No") << endl;
  }
  return 0;
}
