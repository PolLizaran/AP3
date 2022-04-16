#include <iostream>
#include <vector>

using namespace std;
using Matrix = vector<vector<int>>;

void read_costs(vector<int>& v){
    for(int i = 0; i < v.size(); ++i) cin >> v[i];
}

int edition_distance_min_cost(const vector<int>& costs, const string& A, const string& B){
    int s1 = A.size(), s2 = B.size();
    Matrix LCS(A.size() + 1, vector<int>(B.size() + 1, 0)); //we add a row and a column (empty subsequence)
    LCS[0][0] = 0; //cost of empty to empty
    for(int i = 1; i <= s1; ++i) LCS[i][0] = LCS[i - 1][0] + costs[A[i - 1] - 'a']; //cost of converting empty subsequence of B into word A
    for(int j = 1; j <= s2; ++j) LCS[0][j] = LCS[0][j - 1] + costs[B[j - 1] - 'a']; //cost of converting empty subsequence of A into word B
    for(int i = 1; i <= s1; ++i){
        for(int j = 1; j <= s2; ++j){
            if(A[i - 1] == B[j - 1]){
                LCS[i][j] = LCS[i - 1][j - 1]; //no need to add cost as the letters are equal
            }else{
                LCS[i][j] = min(LCS[i - 1][j] + costs[A[i - 1] - 'a'], LCS[i][j - 1] + costs[B[j - 1] - 'a']); //we take the min cost of adding a letter in A or in B
            }
        }
    }
    return LCS[s1][s2];
}

int main(){
    int num_letters;
    while(cin >> num_letters){
        vector<int> costs(num_letters);
        read_costs(costs);
        string A, B;
        cin >> A >> B;
        cout << edition_distance_min_cost(costs, A, B) << endl;
    }
}
