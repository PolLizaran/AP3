#include <iostream>
#include <vector>

using namespace std;
using matrix_int = vector<vector<int>>;
using matrix_bool = vector<vector<bool>>;

const int& UNDEF = -2;
int n;

//return the square in where we are
int current_square(int i, int j){
    return (i / 3) * 3 + j / 3;
}

//function that converts the input into a matrix
//in case it reads a '.' it means there is a blank space
void read_sudoku(matrix_int& a, matrix_bool& num_in_square, matrix_bool& num_in_row, matrix_bool& num_in_col){
    string elem;
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            cin >> elem;
            if(elem[0] != '.'){
                int x = (elem[0] - '0') - 1; //convert the char into in integer, we work with elements from 0 to 8
                a[i][j] = x;
                num_in_row[i][x] = true;
                num_in_col[j][x] = true;
                num_in_square[current_square(i, j)][x] = true;
            }
        }
    }
}

void print_sudoku(const matrix_int& sol){
    cout << endl;
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            cout << ' ' << sol[i][j] + 1;
        }
        cout << endl;
    }

}


//returns true in case no retstrictions are violated
bool is_candidate(const matrix_bool& num_in_square, const matrix_bool& num_in_row,
                  const matrix_bool& num_in_col, int i, int j, int k){
   return not(num_in_row[i][k] and num_in_col[j][k] and num_in_square[current_square(i, j)][k]);
}


//HEM D'ELIMINAR AQUELLES OPCIONS QUE JA NO ENS PORTEN ENLLOC
void gen(matrix_int& sol, matrix_bool& num_in_square,
         matrix_bool& num_in_row, matrix_bool& num_in_col, int i){
    if(i == 9) print_sudoku(sol); //means we've filled all sqaures
    else{
        for(int j = 0; j < 9; ++j){//rows
            if(j == 8) ++i;
            for(int k = 0; k < 9; ++k){//possible values
                if(sol[i][j] == UNDEF and is_candidate (num_in_square, num_in_row, num_in_col, i, j, k)){
                    sol[i][j] = k;
                    num_in_row[i][k] = true;
                    num_in_col[j][k] = true;
                    num_in_square[current_square(i, j)][k] = true;
                    gen(sol, num_in_square, num_in_row, num_in_col, i);
                    sol[i][j] = UNDEF; //return to its original position
                    num_in_row[i][k] = false;
                    num_in_col[j][k] = false;
                    num_in_square[current_square(i, j)][k] = false;
                }
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    while(n--){
        matrix_int sol(9, vector<int>(9, UNDEF)); //UNDEF for empty positions
        matrix_bool num_in_square(9, vector<bool>(9, false));//row 1 = square 1, position 1 = 1 (means that 1 is in the 1st square)
        matrix_bool num_in_row(9, vector<bool>(9, false));
        matrix_bool num_in_col(9, vector<bool>(9, false));
        read_sudoku(sol, num_in_square, num_in_row, num_in_col);
        /*for(int h = 0; h < 9; ++h){
            for(int g = 0; g < 9; ++g){
                cout << current_square(h, g) << ' ';
            }
            cout << endl;
        }*/
        //gen(sol, num_in_square, num_in_row, num_in_col, 0);
    }
}
