#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, p;
vector<string> words;

void print_partition(const vector<int>& perm){
    int counter = 0;
    bool first = true;
    for(int i = 0; i < p; ++i){ //IMPORTNANT el bucle fer-lo només fins a p
        cout << "subset " << counter + 1 << ": {";
        for(int j = 0; j < n; ++j){
            if(perm[j] == counter){
                cout << (first ? "" : ",") << words[j];
                first = false;
            }
        }
        cout << '}' << endl;
        ++counter;
        first = true;
    }
    cout << endl;
}


void partitions(int k, vector<int>& perm){
    if(k == n){
        print_partition(perm);
    }else{
        for(int i = 0; i < p; ++i){
            perm[k] = i;
            partitions(k + 1, perm);
        }
    }
}

int main(){
    cin >> n;
    words = vector<string>(n);
    vector<int> perm(n);
    for(int i = 0; i < n; ++i) cin >> words[i];
    cin >> p;
    partitions(0, perm);
}
