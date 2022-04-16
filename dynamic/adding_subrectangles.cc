/*the resolution is based on the inclusion exclusion principle. Due to how the problem
is defined, we know that the solution will be the result of one position above, plus the one
of the left position, less the one of the upper position in the diagonal*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using Matrix_int = vector<vector<int>>;

void print_result(const Matrix_int& subrectangles){
    for(int i = 0; i < subrectangles.size(); ++i){
        for(int j = 0; j < subrectangles[0].size(); ++j){
             cout << (j == 0 ? "" : " ") << subrectangles[i][j];
        }
        cout << endl;
    }
}

//Action that reads strings and stores them in a vector of string, that simulate a matrix
vector<string> read_letters(){
    string row;
    vector<string> letters;
    while(cin >> row){
        letters.push_back(row);
    }
    return letters;
}


//bottom up solution
void add_subrectangles(Matrix_int& subrectangles, vector<string>& letters,
                      const vector<int>& weight_letters){
    int n_row = subrectangles.size();
    int n_col = subrectangles[0].size();
    for(int i = 0; i < n_row; ++i){
        for(int j = 0; j < n_col; ++j){
            subrectangles[i][j] = weight_letters[int(letters[i][j] - 'A')]; //valor del caracter actual
            if(j > 0) subrectangles[i][j] += subrectangles[i][j - 1]; //valor del rectangle de dalt
            if(i > 0) subrectangles[i][j] += subrectangles[i - 1][j]; //valor del rectangle del cantó
            if(j > 0 and i > 0) subrectangles[i][j] -= subrectangles[i - 1][j - 1]; //part repetida en la suma
        }
    }
}


int main(){
    vector<string> letters = read_letters();
    Matrix_int subrectangles(letters.size(), vector<int>(letters[0].size(), 0));
    vector<int> weight_letters(27);
    for(int i = 1; i < 28; ++i){ //no seria necessari, directament podem llegir la matriu i anar canviant les lletres per números
        weight_letters[i - 1] = i * (i + 1)/2; // 1 + 2 + 3 + ... + n = n(n+1)/2
    }
    add_subrectangles(subrectangles, letters, weight_letters);
    print_result(subrectangles);
}
