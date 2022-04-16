#include <iostream>
#include <vector>

using namespace std;
using Matrix_i = vector<vector<int>>;
using Matrix_b = vector<vector<bool>>;

int n, m;

Matrix_i read_coin_distribution(){
    Matrix_i A(n, vector<int>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> A[i][j];
        }
    }
    return A;
}

/*
bool not_threatens(const Matrix_b& mkd, const int& i, const int& j){
    if(i > 1){
        if(j > 0 and mkd[i - 2][j - 1]) return false;
        if(j < m - 1 and mkd[i - 2][j + 1]) return false;
    }
    if(i < n - 2){
        if(j > 0 and mkd[i + 2][j - 1]) return false;
        if(j < m - 1 and mkd[i + 2][j + 1]) return false;
    }
    if(j > 1){
        if(i > 0 and mkd[i - 1][j - 2]) return false;
        if(i < n - 1 and mkd[i + 1][j - 2]) return false;
    }
    if(j < m - 2){
        if(i > 0 and mkd[i - 1][j + 2]) return false;
        if(i < n - 1 and mkd[i + 1][j + 2]) return false;
    }
    return true;
}*/


//Millora del not_threatens, si ens ficxem, com que generem de dalt cap a baix, no ens cal
//comprovar si a les files de dalt hi ha un cavall o no
bool not_threatens(const Matrix_b& mkd, const int& row, const int& col){
    if(row  - 2 >= 0 and col + 1 < m and mkd[row - 2][col + 1]) return false;
    if(row  - 2 >= 0 and col - 1 >= 0 and mkd[row - 2][col - 1]) return false;
    if(row  - 1 >= 0 and col + 2 < m and mkd[row - 1][col + 2]) return false;
    if(row  - 1 >= 0 and col - 2 >= 0 and mkd[row - 1][col - 2]) return false;
    return true;
}

void coin_counter(int row, int col, Matrix_i& A, Matrix_b& mkd, int& max_total_coins, int possible_coins){
    if(col == m){
        ++row;
        col = 0;
    }
    if(row == n){
        if(max_total_coins < possible_coins) max_total_coins = possible_coins;
        return;
    }
    coin_counter(row, col + 1, A, mkd, max_total_coins, possible_coins);
    if(not_threatens(mkd, row, col)){
        mkd[row][col] = true;
        coin_counter(row, col + 1, A, mkd, max_total_coins, possible_coins + A[row][col]);
        mkd[row][col] = false;
    }
}

int main(){
    while(cin >> n >> m){
        Matrix_i A = read_coin_distribution();
        Matrix_b mkd(n, vector<bool>(m, false));
        int max_total_coins = 0;
        coin_counter(0, 0, A, mkd, max_total_coins, 0);
        cout << max_total_coins << endl;
    }
}
