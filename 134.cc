#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int n;
int size[16001];  // subtree size
int value[16001];  // associated value (min size of components)
bool visit[16001];
vector<int> graph[16001];

void dfs1(int root, int parent) {
  visit[root] = true;
  for (int i = 0; i < graph[root].size(); i++)
    if (!visit[graph[root][i]])
      dfs1(graph[root][i], root);
  // Compute the size of each subtree.
  size[root] = 1;
  for (int i = 0; i < graph[root].size(); i++)
    if (graph[root][i] != parent)
      size[root] += size[graph[root][i]];
}

void dfs2(int root, int parent, int parent_size) {
  visit[root] = true;
  // Compute the value for root.
  value[root] = parent_size;
  for (int i = 0; i < graph[root].size(); i++)
    if (graph[root][i] != parent)
      value[root] = max(value[root], size[graph[root][i]]);
  // DFS.
  for (int i = 0; i < graph[root].size(); i++)
    if (!visit[graph[root][i]])
      dfs2(graph[root][i], root,
           parent_size + size[root] - size[graph[root][i]]);
}

int main() {
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  dfs1(1, -1);
  memset(visit, 0, sizeof(visit));
  dfs2(1, -1, 0);
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (ans.empty())
      ans.push_back(i);
    else if (value[ans.back()] > value[i]) {
      ans.clear();
      ans.push_back(i);
    } else if (value[ans.back()] == value[i])
      ans.push_back(i);
  }
  cout << value[ans.front()] << ' ' << ans.size() << endl;
  cout << ans.front();
  for (int i = 1; i < ans.size(); i++)
    cout << ' ' << ans[i];
  cout << endl;
  return 0;
}
