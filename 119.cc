#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, a, b;

int main() {
  cin >> n >> a >> b;
  vector<pair<int, int> > ans;
  for (int i = 0; i < n; i++)
    ans.push_back(make_pair(a * i % n, b * i % n));
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i].first << ' ' << ans[i].second << endl;
  return 0;
}
