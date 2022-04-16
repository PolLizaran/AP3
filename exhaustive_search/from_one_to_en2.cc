//we have to write all the possible permutations
//such that they only have one cycle each of them
#include <iostream>
#include <vector>
using namespace std;

//global variable
int n; //cardinal of the permutations

/* action that given a permutation stored in the vector
prints the output by adding one to each element as we
want the numbers to go from 1 to n*/
void write_permutations(const vector<int>& v){
    for(int i = 0; i < v.size(); ++i) cout << (i != 0 ? "," : "(") << v[i] + 1;
    cout << ')' << endl;
}

void gen(int k, vector<int>& v, vector<bool>& alr_used, int u){ //are the positions filled
    if(u == n) write_permutations(v); //all positions have been already filled
    else{
        for(int j = 0; j < n; ++j){
            if(not alr_used[j] and v[k] == -1){
                //alr_used is for not repeating numbers and v[k] is for not reassigning
                //values to positions already occupied
                    alr_used[j] = true;
                    v[k] = j;
                    gen(j, v, alr_used, u + 1);//saltem a la posició j
                    alr_used[j] = false;
                    v[k] = -1;
            }
        }
    }
}

int main(){
    cin >> n;
    vector<int> v(n, -1);
    vector<bool> alr_used(n, false);
    gen(0, v, alr_used, 0);//generation action
}
