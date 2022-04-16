#include <iostream>
#include <vector>

using namespace std;
using row = vector<int>;
using Matrix = vector<row>;

const int UNDEF = -1;
int n;

//we use the same strategy as with grafs, so we decalre a list of lists;
void read_precedences(Matrix& prec, vector<int>& num_precedences){
    int x, y;
    cin >> x >> y;
    prec[x].push_back(y); //the row x of the list of lists contains the numbers that have to go after x
    ++num_precedences[y]; //as x has to be situated before y, it means that y now has one more precedence
}

//action that prints the solution
void print_ordering(const vector<int>& possible_top_ord){
    cout << possible_top_ord[0];
    for(int k = 1; k < n; ++k) cout << ' ' << possible_top_ord[k];
    cout << endl;
}

/* action that generates al the combinations that fulfill the precedences given. In order to detect whether
a number can be put, it checks that the vector containing the number of precedences of each element is 0.
That will mean that all the precedences have been already put in the vector.
*/
void gen(int k, vector<int>& possible_top_ord, const Matrix& prec, vector<int>& num_precedences ){
    if(k == n) print_ordering(possible_top_ord);
    else{
        for(int l = 0; l < n; ++l){
            if(num_precedences[l] == 0){ //means no precedences left
                num_precedences[l] = UNDEF; //we assign an undefined number so that this number can't be again used.
                                             //If not we would have topological orderings with repeated elements
                for(auto& x1 : prec[l]) --num_precedences[x1]; //we substract one from each element that had to go after l
                                                               //as we have just added l to the partial solution
                possible_top_ord[k] = l;
                gen(k + 1, possible_top_ord, prec, num_precedences);
                for(auto& x2 : prec[l]) ++num_precedences[x2]; //return to initial positions so that future iterations can be made
                ++num_precedences[l] = 0;
            }
        }
    }
}

void search_orderings(int m){
    Matrix prec(n, vector<int>(0)); //initially is 0 as for the moments no numbers have restrictions yet
    vector<int> num_precedences(n); //contains the amout of numbers that have to be put before
    for(int i = 0; i < m; ++i){
        read_precedences(prec, num_precedences);
    }
    vector<int> possible_top_ord(n); //vector where we'll store the partial solution
    gen(0, possible_top_ord, prec, num_precedences);
}

//in this program we won't need a boolean of marked places as the vector count will act like it
//moreover precedences aren't stored in a Matrix as we would have to go throughout the wole row to check if precedences are violated or not
int main(){
    int m;
    cin >> n >> m;
    search_orderings(m);
}
