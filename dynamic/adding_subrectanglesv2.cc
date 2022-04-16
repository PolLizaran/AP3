#include <iostream>
#include <vector>
using namespace std;

using Grid = vector<vector<int>>;

void read_and_compute_grid(Grid& VAL){
    string row;
    while(cin >> row){
        vector <int> rows_values(row.size());
        for(int j = 0; j < row.size(); ++j){
            int x = row[j] - 'A' + 1;
            rows_values[j] = x * (x + 1)/2;
        }
        VAL.push_back(rows_values);
    }
    for(int i = 0; i < VAL.size(); ++i){
        for(int j = 0; j < VAL[0].size(); ++j){
            if(i != 0){ //first row;
                VAL[i][j] += VAL[i - 1][j];
            }
            if(j != 0){//first column
                VAL[i][j] += VAL[i][j - 1];
            }
            if(i != 0 and j != 0){
                VAL[i][j] -= VAL[i - 1][j - 1]; 
            }
        }
    }
}

void print_solution(const Grid& VAL){
    for(int i = 0; i < VAL.size(); ++i){
        for(int j = 0; j < VAL[0].size(); ++j){
            cout << (j == 0 ? "" : " ") << VAL[i][j];
        }
        cout << endl;
    }
}

int main(){
    vector<vector<int>> VAL;
    read_and_compute_grid(VAL);
    print_solution(VAL);
}