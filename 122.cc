#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int MAX_LENGTH = 5000;  // Must be sufficiently large!
int n;
bool can[1000][1000];
bool used[1000];
list<int> cycle;
char line[MAX_LENGTH];
int conn[1000];  // The direct connection in the cycle.

void update_connection(int i) {
  for (int j = 0; j < n; j++)
    if (can[i][j]) conn[j] = i;
}

int main() {
  // Input. Use C I/O, otherwise TLE.
  fgets(line, MAX_LENGTH, stdin);
  n = atoi(line);
  for (int i = 0; i < n; i++) {
    fgets(line, MAX_LENGTH, stdin);
    char* token = strtok(line, " ");
    while (token != NULL) {
      int ami = atoi(token);
      can[i][ami - 1] = can[ami - 1][i] = true;
      token = strtok(NULL, " ");
    }
  }
  // Main algorithm.
  for (int i = 0; i < n; i++) conn[i] = -1;
  cycle.push_back(0);
  used[0] = true;
  update_connection(0);
  while (cycle.size() < n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
      if (used[i]) continue;
      if (can[i][cycle.front()]) {
        used[i] = found = true;
        cycle.push_front(i);
        update_connection(i);
        break;
      } else if (can[i][cycle.back()]) {
        used[i] = found = true;
        cycle.push_back(i);
        update_connection(i);
        break;
      }
    }
    if (!found) break;
  }
  while (true) {
    // Is the path a circle?
    if (can[cycle.front()][cycle.back()]) {
      if (cycle.size() == n) break;
      // Extend the circle. O(n).
      int i = 0;
      while (used[i] || conn[i] == -1) i++;
      used[i] = true;
      list<int>::iterator it = cycle.begin();
      while (*it != conn[i]) it++;
      rotate(cycle.begin(), it, cycle.end());
      cycle.push_front(i);
      update_connection(i);
    } else {
      // Rearrange the path to be a cycle. O(n).
      // There exists c[k-1] and c[k] s.t. c[0] connects c[k] and c[len - 1]
      // connects c[k - 1].
      list<int>::iterator it1 = cycle.begin();
      list<int>::iterator it2 = cycle.begin();
      it2++;
      while (it2 != cycle.end()) {
        if (can[cycle.front()][*it2] && can[*it1][cycle.back()]) {
          reverse(it2, cycle.end());
          break;
        }
        it1++;
        it2++;
      }
    }
  }
  // Output.
  for (list<int>::iterator it = cycle.begin(); it != cycle.end(); it++) {
    if (*it == 0) {
      rotate(cycle.begin(), it, cycle.end());
      break;
    }
  }
  for (list<int>::iterator it = cycle.begin(); it != cycle.end(); it++) {
    cout << *it + 1 << ' ';
  }
  cout << cycle.front() + 1 << endl;
  return 0;
}
