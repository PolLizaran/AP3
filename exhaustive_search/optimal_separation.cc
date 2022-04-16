#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void generate(int left, int right, int remaining, int& best, const vector<int>& values, int k){
    int n = values.size();
    int current_diference = abs(left - right);
    if(current_diference > remaining and current_diference - remaining > best) return;
    if(k == n){
        best = current_diference;
        return;
    }else{
        generate(left + values[k], right, remaining - values[k], best, values, k + 1);
        generate(left, right + values[k], remaining - values[k], best, values, k + 1);
    }
}

int main(){
    int n;
    while(cin >> n){
        vector<int> values(n);
        int best = INT_MAX;
        int total = 0;
        for(int i = 0; i < n; ++i){
            cin >> values[i];
            total += values[i];
        }
        generate(0, 0, total, best, values, 0);
        cout << best << endl;
    }
}


/*
void generate(int difference, int remaining, int& best, const vector<int>& values, int k){
    int n = values.size();
    if(difference - remaining > best) return; //ni posant-ho tot a un lloc millorem la solució
    if(k == n){
        if(abs(difference) < best) best = abs(difference);
        return;
    }else{
        generate(difference + values[k], remaining - values[k], best, values, k + 1);
        generate(difference - values[k], remaining - values[k], best, values, k + 1);
    }
}
*/
