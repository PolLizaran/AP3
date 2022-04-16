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
        cout << (i == 0 ? "" : ",") << v[i] + 1; //we print in the desired format {1 ... n}
    }
    cout << ')' << endl;
}

//returns the total possible inversions that can still be made
int possible_inv(int k){
    int r = n - k;
    return (r * (r + 1))/2;
}

//curr_inv is a counter of the inversions at the moment
void gen_inv1(int k, vector<int>& v, vector<bool>& mkd, int curr_inv){
    if(curr_inv > s or curr_inv + possible_inv(k) < s) return; //the partial solution can still be extended
    if(k == n) {
        print_candidate(v);
    }else{
        int compt = 0;
        for(int j = 0; j < n; ++j){
            if(not mkd[j]){
                mkd[j] = true;
                v[k] = j;
                gen_inv1(k + 1, v, mkd, curr_inv + compt);
                ++compt; //cada cop que generem per una unitat més s'incrementa en un el comptador
                v[k] = UNDEF;
                mkd[j] = false;
            }
        }
    }
}

void gen_inv_reves(int k, vector<int>& v, vector<bool>& mkd, int curr_inv){
    if(curr_inv > s or curr_inv + possible_inv(k) < s) return; //the partial solution can still be extended
    if(k == n) {
        print_candidate(v);
    }else{
        int compt = 0;
        for(int j = n - 1; j >= 0; --j){
            if(not mkd[j]){
                mkd[j] = true;
                v[k] = j;
                gen_inv_reves(k + 1, v, mkd, curr_inv + compt);
                ++compt; //cada cop que generem per una unitat més s'incrementa en un el comptador
                v[k] = UNDEF;
                mkd[j] = false;
            }
        }
    }
}

int main(){
    cin >> n >> s;
    vector<int> v(n, UNDEF);
    vector<bool> mkd(n, false);
    if(s > possible_inv(1)/2){ //comencem el for al revés per estalviar haver de recórrer el vector senser cada cop
        s = possible_inv(1) - s;
        gen_inv_reves(0, v, mkd, 0);//es el mateix calcular-ho amb 10 - 45, que amb 10 - 0 si comencem al reves
    }else{
        gen_inv1(0, v, mkd, 0);
    }
}
