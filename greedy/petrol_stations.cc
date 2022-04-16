#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void read_stations(vector<int>& v, int n){
    for(int i = 1; i <= n; ++i){ //avoid 0 for future easyness to be able to start at 1
        cin >> v[i];
    }
}

int count_necessary_stops(const vector<int>& v, int x, int d){
    int i = 1, fuel = x, num_stops = 0;
    fuel = fuel - v[1]; //cost of going from the begining to position 1
    while(i < v.size() - 1 and v[i] <= d){
        if(fuel - (v[i + 1] - v[i]) < 0){
            ++num_stops;
            fuel = x;
        }
        fuel = fuel - (v[i + 1] - v[i]);
        ++i;
    }
    return num_stops;
}


int main(){
    int x, d, n;
    while(cin >> x >> d >> n){
        vector<int> v(n + 1, 0); //inicialized at 0 as we asume the initial cost of going
        //from the departing place to anywhere is 0 as it is not yet initialized
        read_stations(v, n);
        v.push_back(d); //as we have to reach d, we can consider it is an other
        //station to make it easier to check wether we can arrive to it from the
        //last petrol station without filling the tank of fuel
        sort(v.begin(), v.end());
        cout << count_necessary_stops(v, x, d) << endl;
    }
}
