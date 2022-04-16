//idea to calculate the inversions. Make the loop in reversed order going from the biggest number to the most little
//being the numbers already assigned and bigger than x the current inversions

#include <iostream>
#include <vector>

using namespace std;

int n, s; //s is the total inversions we want
const int& UNDEF = -1;

void print_candidate(const vector<int>& v){
    cout << '(';
    for(int i = 0; i < n; ++i){
        cout << (i == 0 ? "" : ",") << v[i] + 1;
    }
    cout << ')' << endl;
}

//returns the total possible inversions that can still be made
int possible_inv(int k){
    int r = n - k;
    //cout << x << end;
    return (r * (r - 1))/2;;
}

//curr_inv is a counter of the inversions at the moment
void gen_inv(int k, vector<int>& v, vector<bool>& mkd, int curr_inv){
    if(curr_inv > s) return;
    if(k == n and curr_inv == s) print_candidate(v);
    else{
        for(int j = n - 1; j >= 0; --j){
            if(not mkd[j]){
                if(curr_inv + possible_inv(k) >= s){
                mkd[j] = true;
                v[k] = j;
                //cout << "curr_inv" << curr_inv << endl;
                gen_inv(k + 1, v, mkd, curr_inv);
                v[k] = UNDEF;
                mkd[j] = false;
                }
            }else{
                ++curr_inv; //an inversion is added as we have skipped one element
            }
        }
    }
}



int main(){
    cin >> n >> s;
    vector<int> v(n, UNDEF);
    vector<bool> mkd(n, false);
    gen_inv(0, v, mkd, 0);

}
