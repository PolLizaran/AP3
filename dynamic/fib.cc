#include <iostream>
#include <vector>

using namespace std;

const int UNDEF = -1;
vector<int> f;

int F(int k) {
  int& res = f[k];
  if (res != UNDEF) return res; // already computed: return
  if (k <= 1) return res = 1;   // store computed value
  return res = F(k-2) + F(k-1); // store computed value
}
int main() {
  int k;
  cin >> k;
  f = vector<int>(k+1, UNDEF);  // all UNDEFined at first
  cout << F(k) << endl;
}
