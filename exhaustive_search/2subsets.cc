#include <iostream>
#include <vector>
using namespace std;

vector<string> read_sequence(int n){
    vector<string> seq(n);
    for(int i = 0; i < n; ++i) cin >> seq[i];
    return seq;
}

void print_seq(int m, const vector<bool>& perm, const vector<string>& seq){
    cout << '{';
    int x = 0;
    for(int i = 0; i < perm.size(); ++i){
        if(perm[i]) {
            ++ x;
            cout << seq[i];
            if(x < m) cout << ',';
        }
    }
    cout << '}' << endl;
}

//we use booleans to generate all possible permutations, and the variable ones counts the elements currently fit
void gen(int k, int m, vector<bool>& perm, const vector<string>& seq, int ones){
    if(perm.size() - k < m - ones) return; //there is not enough space to fit all the ones that last
    if(ones == m){
        print_seq(m, perm, seq);
    }
    else{
            gen(k + 1, m, perm, seq, ones);
            perm[k] = true;
            gen(k + 1, m, perm, seq, ones + 1);
            perm[k] = false;
    }
}

int main(){
    int m, n;
    cin >> m >> n;
    if(m == 0) cout << "{}" << endl;
    else{
        vector<string> seq = read_sequence(n);
        vector<bool> perm(n, false);
        gen(0, m, perm, seq, 0);
    }
}
