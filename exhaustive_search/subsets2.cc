#include <iostream>
#include <vector>
using namespace std;

vector<string> read_sequence(int n){
    vector<string> seq(n);
    for(int i = 0; i < n; ++i) cin >> seq[i];
    return seq;
}

void print_seq(const vector<int>& integer_seq, const vector<string>& seq){
    cout << '{' << seq[integer_seq[0]];
    for(int j = 1; j < integer_seq.size(); ++j) cout << ',' << seq[integer_seq[j]];
    cout << '}' << endl;
}

//we use k as a jumper to determine from which value do we start in order to not repeat permutations
void gen(int k, vector<int>& integer_seq, vector<bool>& elem_used, const vector<string>& seq, int last_used){
    if(integer_seq.back() != -1) print_seq(integer_seq, seq); //all positions have been fit

    else{
        for(int l = 0; l < seq.size(); ++l){
            if(not elem_used[l] and l > last_used){
                /* as we don't want to repeat permutations we start permuting having into account that
                the last element used has to be in a smaller position in the vector than the following.
                Doing it like this way we avoid repeating the same permutations but reversed */
                    elem_used[l] = true;
                    integer_seq[k] = l;
                    gen(k + 1, integer_seq, elem_used, seq, l); //l is the last element used in the sequence
                    integer_seq[k] = -1;
                    elem_used[l] = false;
            }
        }
    }
}

int main(){
    int m, n;
    cin >> m >> n;
    if(m == 0) cout << "{}" << endl;
    else{
        vector<string> seq = read_sequence(n);
        vector<int> integer_seq(m, -1);
        vector<bool> elem_used(n, false);
        gen(0, integer_seq, elem_used, seq, -1);
    }
}
