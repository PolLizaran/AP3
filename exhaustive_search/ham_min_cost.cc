//in this problem we are asked to find the hamiltonian cylcle of minimum cost, so is very similiar to
//the 'tsp' problem. The unique difference is that we are not asked to find the best cycle but the cheapest cost

#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using Matrix_cost = vector<vector<int>>; //cost of going from i to j, it does not have to be symetric

//global variables
const int& UNDEF = -1;
const int& MAX_INT = numeric_limits<int>::max();
int n, best_cost = MAX_INT; //best_cost simulates infinite

//k is the invariant. The last_node visited is the number that was lastly added in the vector. s is the partial solution
//by making s[last_node] = j what we achieve is that the path is computed like jumping from one place to another
void hamiltonian(int k, int last_node, int cost, vector<int>& s, const Matrix_cost& weights){
    if(k == n){
        cost += weights[last_node][0]; //return to initial position
        if(cost < best_cost) best_cost = cost;
    }else{
        for(int j = 0; j < n; ++j){
            if(j != last_node and s[j] == UNDEF and (cost + weights[last_node][j] < best_cost)){
                //s[j] = UNDEF means that this element has not been visited yet, so is a possible destiny
                s[last_node] = j; //destiny
                hamiltonian(k + 1, j, cost + weights[last_node][j], s, weights); //last_node = j
                s[j] = UNDEF; //restore initial state
            }
        }
    }
}

void search_min_cost(){
    while(cin >> n){
        Matrix_cost weights(n, vector<int>(n));
        for(auto& R : weights) for(auto& x : R) cin >> x;
        vector<int> s(n, UNDEF); //partial solution
        hamiltonian(1, 0, 0, s, weights);
        //k = 1 at begining as we need one iteration less than n to find a hamiltonian path because the last
        //iteration is already known: going from that element to the initial position
        cout << best_cost << endl;
        best_cost = MAX_INT;
    }
}

int main(){
    search_min_cost();
}
