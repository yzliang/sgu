#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

char x[1002];

const int kBase = 100;

struct BigNumber {
  int num[1005];
  int len;
};

int Compare(const BigNumber& a, const BigNumber& b) {
  if (a.len != b.len)
    return a.len - b.len;
  for (int i = a.len - 1; i >= 0; i--)
    if (a.num[i] != b.num[i])
      return a.num[i] - b.num[i];
  return 0;
}

void Add(const BigNumber& a, const BigNumber& b, BigNumber* c) {
  for (int i = 0; i < min(a.len, b.len); i++)
    c->num[i] = a.num[i] + b.num[i];
  if (a.len > b.len)
    memcpy(c->num + b.len, a.num + b.len, (a.len - b.len) * sizeof(int));
  else if (a.len < b.len)
    memcpy(c->num + a.len, b.num + a.len, (b.len - a.len) * sizeof(int));
  c->len = max(a.len, b.len);
  for (int i = 0; i < c->len; i++) {
    if (c->num[i] >= kBase) {
      c->num[i + 1]++;
      c->num[i] -= kBase;
    }
  }
  if (c->num[c->len] > 0)
    c->len++;
}

void Div2(BigNumber* a) {
  int r = 0;
  for (int i = a->len - 1; i >= 0; i--) {
    r = r * kBase + a->num[i];
    a->num[i] = r / 2;
    r %= 2;
  }
  if (a->len > 1 && a->num[a->len - 1] == 0)
    a->len--;
}

void Square(BigNumber& a, BigNumber* b) {
  memset(b->num, 0, sizeof(b->num));
  for (int i = 0; i < a.len; i++)
    for (int j = 0; j < a.len; j++)
      b->num[i + j] += a.num[i] * a.num[j];
  b->len = a.len + a.len - 1;
  for (int i = 0; i < b->len; i++) {
    if (b->num[i] >= kBase) {
      b->num[i + 1] += b->num[i] / kBase;
      b->num[i] %= kBase;
    }
  }
  if (b->num[b->len] > 0)
    b->len++;
}

void Inc(BigNumber* a) {
  a->num[a->len] = 0;
  a->num[0]++;
  for (int i = 0; a->num[i] >= kBase; i++) {
    a->num[i + 1]++;
    a->num[i] -= kBase;
  }
  if (a->num[a->len] > 0)
    a->len++;
}

void Dec(BigNumber* a) {
  int i = 0;
  while (a->num[i] == 0)
    i++;
  a->num[i]--;
  for (i--; i >= 0; i--)
    a->num[i] = kBase - 1;
  if (a->num[a->len - 1] == 0)
    a->len--;
}

void show(BigNumber& a) {
  for (int i = a.len - 1; i >= 0; i--) {
    if (i < a.len - 1 && a.num[i] < 10)
      cout << '0';
    cout << a.num[i];
  }
  cout << endl;
}

int main() {
  cin >> x;
  int x_len = strlen(x);
  BigNumber x_num;
  x_num.len = 0;
  for (int i = x_len - 1; i >= 0; i -= 2)
    x_num.num[x_num.len++] = (x[i] - '0') + (i > 0 ? 10 * (x[i - 1] - '0') : 0);

  BigNumber l_num, r_num, mid_num, square_num;
  l_num.len = max(x_num.len / 2, 1);
  memset(l_num.num, 0, sizeof(l_num.num));
  l_num.num[l_num.len - 1] = 1;
  r_num.len = x_num.len / 2 + 1;
  for (int i = 0; i < r_num.len; i++)
    r_num.num[i] = 99;
  while (Compare(l_num, r_num) <= 0) {
    Add(l_num, r_num, &mid_num);
    Div2(&mid_num);
    Square(mid_num, &square_num);
    if (Compare(square_num, x_num) <= 0) {
      // l = mid + 1
      l_num = mid_num;
      Inc(&l_num);
    } else {
      // r = mid - 1
      r_num = mid_num;
      Dec(&r_num);
    }
  }

  show(r_num);
  return 0;
}
