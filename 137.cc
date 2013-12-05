#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void compute(int n, int k, vector<int>& s) {
  if (n == 1) {
    s.resize(1);
    s[0] = k;
    return;
  }
  int num1 = k % n, num0 = n - num1;
  if (num0 > num1) {
    // 0..., 1, 0..., 1
    compute(num1, num0, s);
    reverse(s.begin(), s.begin() + num1);
    vector<int> t;
    t.reserve(n);
    for (int i = 0; i < num1; i++) {
      for (int j = 0; j < s[i]; j++)
        t.push_back(k / n);
      t.push_back(k / n + 1);
    }
    s.swap(t);
  } else {
    // 0, 1..., 0, 1...
    compute(num0, num1, s);
    vector<int> t;
    t.reserve(n);
    for (int i = 0; i < num0; i++) {
      t.push_back(k / n);
      for (int j = 0; j < s[i]; j++)
        t.push_back(k / n + 1);
    }
    s.swap(t);
  }
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> s;
  compute(n, k, s);
  cout << s[0];
  for (int i = 1; i < n; i++)
    cout << ' ' << s[i];
  cout << endl;
  return 0;
}
