#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int total_sum = 0;

int main(){
    int n;
    while(cin >> n){
        vector<int> v(3 * n);
        for(int i = 0; i < 3 * n; i = i + 3){
            for(int j = i; j < i + 3; ++j) cin >> v[j];
        }
        sort(v.begin(), v.end());
        
        for(int j = 0; j < v.size(); ++j) if(j % 3 != 0) total_sum += v[j];
        cout << total_sum <<  endl;
        total_sum = 0;
    }
}
