#include <iostream>
#include <vector>
#include <string>

using namespace std;
using Matrix = vector<vector<int>>;

int size1, size2, max;
const int& NOMATCH = 0;

void max_com_sub(const Matrix& LCS, const string& word1){
    int max = -1;
    string com_word;
    for(int i = 0; i < size1; ++i){
        for(int j = 0; j < size2; ++j){
            if(LCS[i][j] > max){
                max = LCS[i][j];
                com_word = word1.substr(i - max + 1, max);
            }
        }
    }
    for(int k = 0; k < size1; ++k){
        for(int l = 0; l < size2; ++l){
            if(LCS[k][l] == max){
                string s;
                s = word1.substr(k - max + 1, max);
                if(com_word > s){
                    com_word = s;
                }
            }
        }
    }
    cout << com_word << endl;
}


//i is index of the words
void fill_LCS(const string& word1, const string& word2,  Matrix& LCS){
    size1 = int(word1.size()), size2 = int(word2.size());
    for(int i = 0; i < size1; ++i){
        for(int j = 0; j < size2; ++j){
            if(word2[j] == word1[i]){
                if(i == 0 or j == 0) LCS[i][j] = 1;
                else LCS[i][j] = LCS[i - 1][j - 1] + 1; //we add one to the maximum lenght in that position
            }
        }
    }
}


int main(){
    string word1, word2;
    while(cin >> word1 >> word2){
        int size1 = int(word1.size()), size2 = int(word2.size());
        Matrix LCS(size1, vector<int>(size2, NOMATCH));
        fill_LCS(word1, word2, LCS);
        max_com_sub(LCS, word1);
    }

}
