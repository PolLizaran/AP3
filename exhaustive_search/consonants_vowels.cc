#include <iostream>
#include <vector>

using namespace std;


vector<char> read_sequence(int n){
    vector<char> letters(n);
    for(int i = 0;  i < n; ++i) cin >> letters[i];
    return letters;
}

void print_seq(const vector<char>& final_perm){
    for(int j = 0; j < final_perm.size(); ++j) cout << final_perm[j];
    cout << endl;
}

void gen(int k, const vector<char>& cons, const vector<char>& vowl, vector<char>& final_perm, vector<bool>& mkd, int n){
    if(k == 2 * n){ // as we supose both vector are like concatenated, the total size is 2n
        print_seq(final_perm);
    }else{
        for(int i = 0; i < n; ++i){
            if(k % 2 == 0){ //consonants are in even positions
                if(not mkd[i]){
                    final_perm[k] = cons[i];
                    mkd[i] = true;
                    gen(k + 1, cons, vowl, final_perm, mkd, n);
                    mkd[i] = false;
                }
            }else{ //vowels are in odd positions
                if(not mkd[i + n]){
                    final_perm[k] = vowl[i];
                    mkd[i + n] = true;
                    gen(k + 1, cons, vowl, final_perm, mkd, n);
                    mkd[i + n] = false;
                }
            }
        }
    }
}

void all_perm(int n){ //create all vectors and call gen action
    vector<char> cons = read_sequence(n);
    vector<char> vowl = read_sequence(n);
    vector<bool> mkd(2*n, false); //positions from {0 ... n-1} are the ones from consonants and {n ... 2n - 1} from vowels
    vector<char> final_perm(2*n);
    gen(0, cons, vowl, final_perm, mkd, n);
}


int main(){
    int n;
    cin >> n;
    all_perm(n);
}
