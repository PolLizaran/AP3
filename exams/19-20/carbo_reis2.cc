#include <iostream>
#include <vector>

using namespace std;

const int& UNDEF = -1;

struct Miner{

};

bool legal_miner(){
    //salaries[i - 1] + salary <= budget and weights[i - 1] + weight <= elev_limit
}

int optimization(vector<vector<int>>& A, int i, int j){
    if(res != UNDEF) return res;
}

int main(){
    int n, budget, elev_limit, productivity, salary = 0, weight = 0;
    //requirements: -total sum of salaries <= budget
    //              -total sum of weights <= elev_lim
    //              -maximum productivity
    vector<int> productivities, salaries, weights;
    while(cin >> n >> budget >> elev_limit){
        for(int i = 0; i < n; ++i){
            cin >> productivities[i] >> salaries[i] >> weights[i];
        }
        //vector<vector<int>> A(n + 1, vector<int>(n + 1, UNDEF)); //first row and column we don't take any miner
        //cout << optimization(A, n + 1, n + 1) << endl;
    }
}
