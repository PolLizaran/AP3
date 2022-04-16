#include <iostream>
#include <vector>

using namespace std;

const int& UNDEF = -1;


/*Estructura:
-tenir iterador que si és < 0 significa que ja hem acabat aquella branca --> return 0
-Si el nombre de uns és més petit que 0 significa que ja hem col·locat massa uns i per tant aquella branca no és una solució
-Modificar els valors dels vectors i canviar el comptador de uns en relació al que hem posat
*/

/*
int sequences(int n, int u, vector<int>& w10, vector<int>& w11
              vector<int>& w01){
    if(n <= 1) return n + 1;
    else{
        if(u < 0 or u > n) return 0;
        for(int i = 3; i <= n; ++i){
            return res = w10[n]  + w11[n] + w01[n];
                w10[i] = w01[i - 1] + w11[i - 1];
                w11[i] = w01[i - 1]; //no pot ser w11 perquè no podem tenir 3 uns seguits
                w01[i] = w10[i - 1]; //després d'un 0 hem de tenir un 1
        }
    }
}*/

void sequences(int n, int u, vector<vector<int>>& v, int row, int i){
    if(i == n)
    if(u < 0) return 0; //hem posat massa uns
    int res0& = v[0][i];
    int res1& = v[1][i];
    int res2& = v[2][i];
    else{
        res0 = v[] [i - 1] + w11[i - 1];
        w11[i] = w01[i - 1]; //no pot ser w11 perquè no podem tenir 3 uns seguits
        w01[i] = w10[i - 1]; //després d'un 0 hem de tenir un 1
        sequences(n, u, w10, w11, w01, i + 1);
    }
    return v[0][n] + v[1][n] + v[2][n];
}


int main(){
    int z, u;
    while(cin >> z >> u){
        vector<vector<int>> v (3, UNDEF);
        v[0][2] = v [1][2] = v[2][2] = 1; // w10 (1st row) = w11 (2nd row) = w01 (3rd row)
        //les paraules són 10, 11, 01
        cout << sequences(z + u, u, v) << endl;
    }
}
