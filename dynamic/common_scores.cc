#include <iostream>
#include <vector>

using namespace std;
using Matrix = vector<vector<int>>;

void read_sequences(vector<int>& v){
    for(int i = 0; i < v.size(); ++i) cin >> v[i];
}

int common_scores(Matrix& LCS, const vector<int>& v1, const vector<int>& v2){
    int s1 = v1.size(), s2 = v2.size();
    for(int i = 1; i <= s1; ++i){
        for(int j = 1; j <= s2; ++j){
            if(v1[i - 1] == v2[j - 1]){
                LCS[i][j] = LCS[i - 1][j - 1] + 1; //add 1 in case the numbers are equal
            }else{
                LCS[i][j] = max(LCS[i][j - 1], LCS[i - 1][j]);
            }
        }
    }
    return LCS[s1][s2];
}

int main(){
    int l1, l2;
    while(cin >> l1 >> l2){
        vector<int> v1(l1);
        read_sequences(v1);
        vector<int> v2(l2);
        read_sequences(v2);
        Matrix LCS(l1 + 1, vector<int>(l2 + 1, 0)); //we add a row and a column (empty subsequence)
        cout << common_scores(LCS, v1, v2) << endl;
    }
}
