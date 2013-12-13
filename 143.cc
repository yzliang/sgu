#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int n;
int p[16000];
int f[16000][2];
vector<int> g[16000];

void read_input() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> p[i];
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x - 1].push_back(y - 1);
    g[y - 1].push_back(x - 1);
  }
}

void compute(int root, int parent) {
  f[root][0] = INT_MIN;
  f[root][1] = p[root];
  for (int i = 0; i < g[root].size(); i++) {
    int child = g[root][i];
    if (child == parent) continue;
    compute(child, root);
    f[root][0] = max(f[root][0], max(f[child][0], f[child][1]));
    if (f[child][1] > 0)
      f[root][1] += f[child][1];
  }
}

int main() {
  read_input();
  compute(0, -1);
  cout << max(f[0][0], f[0][1]) << endl;
  return 0;
}
