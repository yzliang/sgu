#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void Multiply(vector<int>* a, int x) {
  for (vector<int>::iterator i = a->begin(); i != a->end(); i++)
    (*i) *= x;
  for (int i = 0; i < a->size() - 1; i++) {
    if ((*a)[i] >= 1000) {
      (*a)[i + 1] += (*a)[i] / 1000;
      (*a)[i] %= 1000;
    }
  }
  while (a->back() >= 1000) {
    int carry = a->back() / 1000;
    a->back() %= 1000;
    a->push_back(carry);
  }
}

int Compare(const vector<int>& a, const vector<int>& b) {
  if (a.size() != b.size())
    return a.size() - b.size();
  for (int i = a.size() - 1; i >= 0; i--)
    if (a[i] != b[i])
      return a[i] - b[i];
  return 0;
}

void Subtract(vector<int>* a, const vector<int>& b) {
  int carry = 0;
  for (int i = 0; i < b.size(); i++) {
    if ((*a)[i] < b[i] + carry) {
      (*a)[i] = (*a)[i] + 1000 - b[i] - carry;
      carry = 1;
    } else {
      (*a)[i] -= b[i] + carry;
      carry = 0;
    }
  }
  for (int i = b.size(); i < a->size(); i++) {
    if (carry && (*a)[i] == 0)
      (*a)[i] = 999;
    else {
      (*a)[i] -= carry;
      break;
    }
  }
  while (a->size() > 1 && a->back() == 0)
    a->pop_back();
}

void Print(const vector<int>& a) {
  cout << a.back();
  for (int i = a.size() - 2; i >= 0; i--) {
    if (a[i] == 0)
      cout << "000";
    else {
      for (int j = 0; j < 2 - log10(a[i]); j++)
        cout << '0';
      cout << a[i];
    }
  }
}

int main () {
  int a, b;
  cin >> a >> b;
  vector<int> na, nb;
  na.push_back(1);
  nb.push_back(1);

  for (int i = 0; i < b; i++) {
    Multiply(&na, a);
  }
  for (int i = 0; i < a; i++) {
    Multiply(&nb, b);
  }
  if (Compare(na, nb) < 0) {
    Subtract(&nb, na);
    cout << '-';
    Print(nb);
  } else {
    Subtract(&na, nb);
    Print(na);
  }
  cout << endl;
  return 0;
}
