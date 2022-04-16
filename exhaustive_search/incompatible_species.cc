#include <iostream>
#include <vector>
#include <string>


using namespace std;


//reads all the species without taking into account the blank spaces
vector<char> read_species(const int& n){
    vector<char> v(n);
    char x;
    for(int i = 0; i < n; ++i){
        while(cin >> x and x == ' '){}
        v[i] = x;
    }
    return v;
}

int char_to_int (const char& c){
    if(c >= 'a' and c <= 'z') return c - 'a'; // lower case, positions from {0 - 25}
    return (c - 'A') + 26;
}

void read_incompatibilities(int m, int n, vector<vector<bool>>& incomp){
    string x;
    for(int k = 0; k < m; ++k){
        cin >> x;
        char c1 = x[0], c2 = x[1];
        int i = char_to_int(c1);
        int j = char_to_int(c2);
        incomp[i][j] = true;
        incomp[j][i] = true; //biyective relationship
    }
}

void write_legal_comb(const vector<int>& perm, const vector<char>& v){
    for(const int& l : perm) cout << v[l];
    cout << endl;
}

//given two chars if a char can be put in the permutation
//without being incompatible
bool is_legal(char c1, char c2, const vector<vector<bool>>& incomp){
    int i = char_to_int(c1);
    int j = char_to_int(c2);
    return not incomp[i][j];
}

//generates all combinations taking into account the restrictions
void gen(int k, const vector<char>& v, vector<bool>& mkd, vector<int>& perm, const vector<vector<bool>>& incomp){
    if(k == v.size()) write_legal_comb(perm, v);
    else{
        for(int l = 0; l < v.size(); ++l){
            if(not mkd[l]){
                if(k == 0 or is_legal(v[l], v[perm[k - 1]], incomp)){
                    //cout << c1 << ' ' << i << "    " << c2 << ' ' << j << "    " << "incomp[i][j]   " << incomp[i][j] << endl;
                    mkd[l] = true;
                    perm[k] = l;
                    gen(k + 1, v, mkd, perm, incomp);
                    mkd[l] = false;
                }
            }
        }
    }
}


int main(){
    int n;
    cin >> n;
    vector<char> v = read_species(n);
    int m;
    cin >> m;
    vector<vector<bool>> incomp(52, vector<bool>(52, false));
    read_incompatibilities(m, n, incomp);
    vector<bool> mkd(n, false);
    vector<int> perm(n);
    gen(0, v, mkd, perm, incomp);
}
