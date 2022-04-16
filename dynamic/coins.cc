#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void print_sol(const vector<int>& coins, const vector<int>& solution, int goal){
    bool first = true;
    while(goal > 0){
        if(not first) cout << ",";
        first = false;
        cout << solution[goal];
        if(solution[goal] == -1) goal = -1;
        else goal -= solution[goal];
    }
    cout << endl;
}


void search_best_config(int n, int goal, const vector<int>& coins, vector<int>& solution){
    for(int i = 0; i < n; ++i){ //passem els valors de les monedes al vector de solucions
        if(coins[i] <= goal) solution[coins[i]] = coins[i];
    }
    for(int j = coins[0]; j < goal; ++j){
        if(solution[j] != -1){
            for(int k = 0; k < n; ++k){
                if(j + coins[k] <= goal)
                    solution[j + coins[k]] = max(solution[j + coins[k]], coins[k]);
            }
        }
    }
    print_sol(coins, solution, goal);
}

void gen(int n, const int& goal, vector<int>& coins){
    sort(coins.begin(), coins.end());
    vector<int> solution(goal + 1, -1);
    search_best_config(n, goal, coins, solution);
}

int main(){
    int n;
    while(cin >> n){
        vector<int> coins(n);
        for(int i = 0; i < n; ++i){
            cin >> coins[i];
        }
        int goal;
        cin >> goal;
        gen(n, goal, coins);
    }
}
