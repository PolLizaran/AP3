//given an integer s and a subset of integers we want to
//find all the permutations that have s as the sum of all its elements
#include <iostream>
#include <vector>
using namespace std;

int s, n;

//returns a vector with the elements of the input
vector<int> read_subset(){
    vector<int> seq(n);
    for(int i = 0; i < n; ++i) cin >> seq[i];
    return seq;
}

//prints the solution with the required format
void print_subset(const vector<int>& seq, const vector<int>& possible_perm){
    cout << '{';
    bool first = true;
    //it writes the elements of the positions that aren't null
    for(int l = 0; l < n; ++l){
        if(possible_perm[l] == 1){
            if(not first) cout << ',';
            cout << seq[l];
            first = false;
        }
    }
    cout << '}' << endl;
}

//we generate combinations with 0 and 1, if we've added an element, we check if the sum is equal s, if notwe have
//to keep iterating. IMPORTANT: not to write ELSE, as we want to keep iterating even though having written the partial solution
void gen(int curr_sum, int k, const vector<int>& seq, vector<int>& possible_perm, bool last_elm){
    if(curr_sum == s and last_elm) print_subset(seq, possible_perm);
    if(k < n){
        possible_perm[k] = 1;
        gen(curr_sum + seq[k], k + 1, seq, possible_perm, true);
        possible_perm[k] = 0;
        gen(curr_sum, k + 1, seq, possible_perm, false);
    }
}

int main(){
    cin >> s >> n;
    vector<int> seq = read_subset();
    vector<int> possible_perm(n, -1);
    gen(0, 0, seq, possible_perm, true);//is true as we have to consder the case that the sum has to be 0

}
