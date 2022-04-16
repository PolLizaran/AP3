#include <iostream>
#include <vector>

using namespace std;

vector<int> m;
vector<vector<int>> c;

int f(int i , int x) {
    if (x < 0) return 0;
    int& res = c[i][x];
    if (res != -1) return res;
    if (i == 0) {
        if (x == 0) return res = 1;
        else return res = 0;
    }
    return res = f(i - 1, x) + f(i - 1, x - m[i - 1]);
}

int main() {
    int n;
    cin >> n;
    m = vector<int>(n);
    for (int& k : m) cin >> k;
    int v;
    cin >> v;
    c = vector<vector<int>>(n + 1, vector<int>(v + 1, -1));
    cout << f(n, v) << endl;
}
