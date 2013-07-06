#include <iostream>
#include <vector>
using namespace std;

int f, v;
int a[101][101];
int opt[101][101], prev[101][101];

int main() {
  cin >> f >> v;
  for (int i = 1; i <= f; i++)
    for (int j = 1; j <= v; j++)
      cin >> a[i][j];

  // Dynamic programming.
  for (int i = 1; i <= f; i++)
    for (int j = 1; j <= v; j++)
      opt[i][j] = -10000;
  for (int i = 1; i <= f; i++) {
    for (int j = i; j <= v; j++) {
      int max_sum = -10000, choice;
      for (int k = i - 1; k < j; k++) {
        if (opt[i - 1][k] > max_sum) {
          max_sum = opt[i - 1][k];
          choice = k;
        }
      }
      opt[i][j] = max_sum + a[i][j];
      prev[i][j] = choice;
    }
  }

  int max_sum = -10000;
  int last_f = f, last_v;
  for (int i = f; i <= v; i++) {
    if (opt[f][i] > max_sum) {
      max_sum = opt[f][i];
      last_v = i;
    }
  }
  cout << max_sum << endl;
  vector<int> pos;
  while (last_f > 0) {
    pos.push_back(last_v);
    last_v = prev[last_f][last_v];
    last_f--;
  }
  cout << pos.back();
  pos.pop_back();
  while (!pos.empty()) {
    cout << ' ' << pos.back();
    pos.pop_back();
  }
  cout << endl;
  return 0;
}
