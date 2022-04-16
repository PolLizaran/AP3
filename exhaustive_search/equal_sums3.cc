//same as equal_sums1 but we can do better backtracking as the inputs are greater or equal than 0
#include <iostream>
#include <vector>
using namespace std;

int s, n;


//returns a vector with the elements of the input
vector<int> read_subset(int& input_sum){
    vector<int> seq(n);
    for(int i = 0; i < n; ++i){
        cin >> seq[i];
        input_sum += seq[i];
    }
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
void gen(int curr_sum, int k, const vector<int>& seq, vector<int>& possible_perm, bool last_elm, int restants){
    if(curr_sum > s) return; //ens hem passat de s. IMPORTANT, NO HEM DE SUMAR seq[i] PQ RESTRINGIM MÉS DEL COMPTE LA GENERACIÓ
    if(restants + curr_sum <  s) return; // no tenim suficients elements que ens queden per posar tal que si els sumem arribem a s
    if(curr_sum == s and last_elm) print_subset(seq, possible_perm);
    if(k < n) {
        possible_perm[k] = 1;
        restants -= seq[k]; // restem el valor que afegirem ara
        gen(curr_sum + seq[k], k + 1, seq, possible_perm, true, restants);
        possible_perm[k] = 0;
        gen(curr_sum, k + 1, seq, possible_perm, false, restants);

    }
}

int main(){
    cin >> s >> n;
    int input_sum = 0;
    vector<int> seq = read_subset(input_sum);
    vector<int> possible_perm(n, -1);
    gen(0, 0, seq, possible_perm, true, input_sum);//is true as we have to consder the case that the sum has to be 0
}
