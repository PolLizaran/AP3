#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void read_inputs(vector<int>& v, int n){
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }
}

int interval_covering(const vector<int>& v, const int& k, const int& n){
    int begining = v[0], ending = begining + k;
    int i = 0, number_intervals = 1;
    while(i < n){
        if(v[i] <= ending){
            ++i;
        }else{
            begining = v[i];
            ending = begining + k;
            ++number_intervals;
        }
    }
    return number_intervals;
}

int main(){
    int k, n;
    while(cin >> k >> n){
        vector<int> v(n);
        read_inputs(v, n);
        sort(v.begin(), v.end());
        cout << interval_covering(v, k, n) << endl;
    }
}
