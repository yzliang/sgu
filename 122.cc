#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int n;
bool can[1000][1000];
int cycle[1000];
char line[2500];

int check_cycle() {
  for (int i = 0; i < n; i++)
    if (!can[cycle[i]][cycle[i + 1]]) return i;
  return -1;
}

void swap(int& i, int &j) {
  int temp = i;
  i = j;
  j = temp;
}

int main() {
  // Input.
  scanf("%d\n", &n);
  for (int i = 0; i < n; i++) {
    fgets(line, sizeof(line), stdin);
    int len = strlen(line);
    int j = 0;
    while (j < len) {
      int k = j + 1;
      while (isdigit(line[k])) k++;
      line[k] = '\0';
      int ami = atoi(&line[j]);
      can[i][ami - 1] = can[ami - 1][i] = true;
      j = k + 1;
    }
  }
  // Palmer's algorithm.
  for (int i = 0; i < n; i++)
    cycle[i] = i;
  while (true) {
    int i = check_cycle();
    if (i == -1) break;
    int j;
    for (j = 0; j < n; j++) {
      if (can[cycle[i]][cycle[j]] && can[cycle[i + 1]][cycle[j + 1]])
        break;
    }
    int l = i + 1, r = j;
    while (l < r) swap(cycle[l++], cycle[r--]);
  }
  // Output.
  for (int i = 0; i < n; i++) cout << cycle[i] + 1 << ' ';
  cout << cycle[0] + 1 << endl;
  return 0;
}
