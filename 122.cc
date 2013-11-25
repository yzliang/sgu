#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int n;
bool can[1000][1000];
int cycle[1000];
char line[2500];

void expand() {
  vector<bool> go(n, false);
  cycle[0] = 0;
  for (int i = 1; i < n; i++) {
    cycle[i] = 0;
    for (int j = 1; j < n; j++) {
      if (can[cycle[i - 1]][j] && !go[j]) {
        go[j] = true;
        cycle[i] = j;
        break;
      }
    }
    if (cycle[i] == 0) {
      for (int j = 1; j < n; j++) {
        if (!go[j]) {
          go[j] = true;
          cycle[i] = j;
          break;
        }
      }
    }
  }
}

void swap(int& i, int &j) {
  int temp = i;
  i = j;
  j = temp;
}

void reverse(int l, int r) {
  while (l != r) {
    swap(cycle[l], cycle[r]);
    l = (l + 1) % n;
    if (l == r) break;
    r = (r + n - 1) % n;
  }
}

int main() {
  // Input.
  cin >> n;
  string line;
  getline(cin, line);
  for (int i = 0; i < n; i++) {
    getline(cin, line);
    istringstream iss(line);
    int ami;
    while (iss >> ami) can[i][ami - 1] = can[ami - 1][i] = true;
  }
  // Palmer's algorithm.
  expand();
  bool gap;
  do {
    gap = false;
    for (int i = 0; i < n; i++) {
      int next_i = (i + 1) % n;
      if (can[cycle[i]][cycle[next_i]]) continue;
      gap = true;
      for (int j = 0; j < n; j++) {
        int next_j = (j + 1) % n;
        if (j == i || next_j == i || j == next_i || next_j == next_i) continue;
        if (can[cycle[i]][cycle[j]] && can[cycle[next_i]][cycle[next_j]]) {
          reverse(next_i, j);
          break;
        }
      }
    }
  } while (gap);
  // Output.
  int pos = 0;
  while (cycle[pos] != 0) pos++;
  cout << cycle[pos] + 1;
  for (int i = 0; i < n; i++) {
    pos = (pos + 1) % n;
    cout << ' ' << cycle[pos] + 1;
  }
  cout << endl;
  return 0;
}
