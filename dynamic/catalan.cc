#include <iostream>
#include <vector>

using namespace std;

const int& UNDEF = -1;

long int cat_num(int n, vector<long int>& part_sol){
    long int& res = part_sol[n];
    if(res != UNDEF) return res; //already asigned
    if(n == 0) return res = 1; //for n == 0 we have one possible parenthesization: the null set
    else{
        res = 0; //quit the UNDEF value
        for(int len1 = 0; len1 <= n - 2; ++len1){ //for every position we compute the cartesian product
            int len2 = n - 2 - len1; //we know that |E1| + |E2| + 2 = n
            res += cat_num(len1, part_sol) * cat_num(len2, part_sol); //cartesian product
        }
        return res;
    }
}

int main(){
    int n;
    vector<long int> part_sol(68, UNDEF);
    for(int i = 0; i < 68; ++i){
        if(i % 2 != 0) part_sol[i] = 0;
    }
    while(cin >> n){
        cout << cat_num(n, part_sol) << endl;
    }
}
