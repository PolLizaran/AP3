#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

int total_candidates;

struct Partit{
    int num;
    int escons;
    int perfil; //0 <= perfil <= 1000 (extr.dreta)
};

void write_solution(const vector<set<int>>& v, const vector<Partit>& partits){
    /*
    cout << "President de";
    int partit_anterior;
    for(int x : v[i]){
        if(partits[x].escons != partit_anterior)
        partit_anterior = partits[x].escons;
        cout << ' ' << x;
    }*/
    vector<string> s = {"A favor", "Abstenció", "En contra"};
    for(int i = 0; i < v.size(); ++i){
        cout << s[i];
        for(auto x : v[i]) cout << ' ' << x; //vote = 0
        cout << endl;
    }
    cout << endl;
}

//will determine, given a distribution of the candidates if the distribution is possible taking
//into account restrictions among candidates
void propagate_forbiddings(vector<vector<int>>& forbiddings, const vector<vector<bool>>& compatible,
                           int vote, int add, int party1){
    for(int party2 = 0; party2 < compatible.size(); ++party2){
        if(not compatible[party1][party2]){ //
            forbiddings[vote][party2] += add;
        }
    }
}

//PETA PQ EN PROPAGATE_FORBIDDINGS POT ENTRAR QUAN HI HA EN CONTRA, I NO INTERESSA

//balance will deternime the difference between in favor and against parties
void search_investidure(int k, const vector<Partit>& partits, vector<set<int>>& v,
                        vector<bool>& used, vector<vector<int>>& forbiddings,
                        const vector<vector<bool>>& compatible,
                        int balance, int already_voted){
    if(k == partits.size()){
        write_solution(v, partits);
        return;
    }else{
        for(int vote = 0; vote <= 2; ++vote){ //0 in favor, 1 abstence, 2 against
            if(not used[k]){ //the candidate can vote that
                if(vote == 2 or forbiddings[vote][k] == 0){
                    if(vote == 0) balance += partits[k].escons; //in favor
                    if(vote == 2) balance -= partits[k].escons; //against
                    used[k] = true;
                    already_voted -= partits[k].escons;
                    if(vote != 2) propagate_forbiddings(forbiddings, compatible, vote, 1, k);
                    v[vote].insert(k);
                    search_investidure(k + 1, partits, v, used, forbiddings, compatible, balance, already_voted);
                    if(vote == 0) balance -= partits[k].escons; //in favor
                    if(vote == 2) balance += partits[k].escons; //against
                    already_voted += partits[k].escons;
                    if(vote != 2) propagate_forbiddings(forbiddings, compatible, vote, -1, k);
                    used[k] = false;
                }
            }
        }
    }
}

void set_compatibilities(const vector<Partit>& partits, vector<vector<bool>>& compatible,
                         int diference, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(partits[j].perfil > partits[i].perfil - diference and
               partits[j].perfil < partits[i].perfil + diference){
                   compatible[i][j] = compatible[j][i] = true;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<Partit> partits(n);
    total_candidates = 0;
    for(int i = 0; i < n; ++i){
        partits[i].num = i;
        cin >> partits[i].escons >> partits[i].perfil;
        total_candidates += partits[i].escons;
    }
    int diference;
    cin >> diference;
    vector<vector<bool>> compatible(n, vector<bool>(n, false));
    set_compatibilities(partits, compatible, diference, n);
    vector<set<int>> v(3);
    vector<bool> used(n);
    vector<vector<int>> forbiddings(2, vector<int>(n));
    //first row means that a candidate is forbiden to be in that group
    //only 2 rows because a party can always vote against
    search_investidure(0, partits, v, used, forbiddings, compatible, 0, 0);
}
