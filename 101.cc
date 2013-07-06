#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int from, to;
  bool used, rotate;
} e[100];

vector<int> g[7];
vector<int> path, stack;
vector<bool> rotate;
int deg[7];

void Euler(int x) {
  for (int i = 0; i < g[x].size(); i++) {
    if (e[g[x][i]].used)
      continue;
    // Mark the edge as "used".
    stack.push_back(g[x][i]);
    e[g[x][i]].used = true;
    Euler(e[g[x][i]].from == x ? e[g[x][i]].to : e[g[x][i]].from);
  }
  // Edge pop out.
  if (stack.empty())
    return;
  int id = stack.back();
  stack.pop_back();
  path.push_back(id);
  e[id].rotate = e[id].from == x ? false : true;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> e[i].from >> e[i].to;
    g[e[i].from].push_back(i);
    g[e[i].to].push_back(i);
    deg[e[i].from]++;
    deg[e[i].to]++;
  }

  // Test degree.
  int num_odd = 0, odd, nonzero;
  for (int i = 0; i < 7; i++) {
    if (deg[i] % 2 != 0) {
      num_odd++;
      odd = i;
    }
    if (deg[i] > 0)
      nonzero = i;
  }
  if (num_odd > 2) {
    cout << "No solution" << endl;
    return 0;
  }

  // Construct an Euler circuit.
  Euler(num_odd == 0 ? nonzero : odd);

  if (path.size() < n) {
    cout << "No solution" << endl;
    return 0;
  }

  for (int i = 0; i < n; i++)
    cout << path[i] + 1 << ' ' << (e[path[i]].rotate ? '-' : '+') << endl;
  return 0;
}
