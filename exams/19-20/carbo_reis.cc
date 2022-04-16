#include <iostream>
#include <vector>

using namespace std;

int n, budget, elev_limit, productivity, salary, weight;
//requirements: -total sum of salaries <= budget
//              -total sum of weights <= elev_lim
//              -maximum productivity

struct Miner{
    int productivity = 0;
    int salary = 0;
    int weight = 0;
};

vector<Miner> miners;

Miner is_in_bounds(const vector<vector<Miner>>& A, int k, int l, int pos_miner){
    int x = A[k][l].salary + miners[pos_miner].salary;
    int y = A[k][l].weight + miners[pos_miner].weight;
    if(x <= budget and y <= elev_limit){
        return {A[k][l].productivity + miners[pos_miner].productivity, x, y};
    }
    else return A[k][l]; //no minner has been added
}


void optimization(vector<vector<Miner>>& A){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            Miner x = is_in_bounds(A, i - 1, j - 1, i - 1);
            Miner y = is_in_bounds(A, i, j - 1, i - 1);
            Miner z = is_in_bounds(A, i, j - 1, i - 1);//pos_min is i-1 as vector miners is 0 indexed
            int k1 = max(x.productivity, y.productivity);
            int k2 = max(y.productivity, z.productivity);
            int k = max(k1, k2);
            if(k == x.productivity) A[i][j] = x;
            else if(k == y.productivity) A[i][j] = y;
            else A[i][j] = z;
        }
    }
}

int main(){
    while(cin >> n >> budget >> elev_limit){
        miners = vector<Miner>(n);
        for(int i = 0; i < n; ++i){
            cin >> productivity >> salary >> weight;
            if(salary < budget and weight < elev_limit){
                miners[i] = {productivity, salary, weight};
            }
        }
        vector<vector<Miner>> A(n + 1, vector<Miner>(n + 1)); //first row and column we don't take any miner
        optimization(A);
        cout << A[n][n].productivity << endl;
    }
}
