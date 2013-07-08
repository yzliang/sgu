#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> sp;  // Super primes.
bool is_prime[10000];
int f[10001], from[10001];

void CalculateSuperPrimes() {
  for (int i = 2; i < 10000; i++)
    is_prime[i] = true;
  for (int i = 2; i < 10000; i++) {
    if (!is_prime[i]) continue;
    for (int j = i + i; j < 10000; j += i)
      is_prime[j] = false;
  }
  int index = 0;
  for (int i = 2; i < 10000; i++) {
    if (is_prime[i] && is_prime[++index])
      sp.push_back(i);
  }
}

int main() {
  CalculateSuperPrimes();

  int n;
  cin >> n;

  // Dynamic programming.
  for (int i = 0; i < sp.size(); i++)
    f[sp[i]] = 1;
  for (int i = 3; i < 10000; i++) {
    if (f[i] == 0) continue;
    for (int j = 0; j < sp.size(); j++) {
      if (i + sp[j] > 10000) break;
      if (f[i + sp[j]] == 0 || f[i] + 1 < f[i + sp[j]]) {
        f[i + sp[j]] = f[i] + 1;
        from[i + sp[j]] = i;
      }
    }
  }

  // Output.
  cout << f[n] << endl;
  if (f[n] == 0) return 0;
  vector<int> nums;
  for (int i = n; i != 0; i = from[i])
    nums.push_back(i - from[i]);
  sort(nums.begin(), nums.end());
  cout << nums.back();
  for (nums.pop_back(); !nums.empty(); nums.pop_back())
    cout << ' ' << nums.back();
  cout << endl;
  return 0;
}
