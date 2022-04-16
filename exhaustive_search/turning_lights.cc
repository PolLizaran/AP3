//Un punt indica una bombeta apagada, i un asterisc una bombeta encesa.
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
using MI = vector<vector<int>>;

int n, m;
int best_config = INT_MAX;

//reads data and modifies opened_lights
MI read_bulbs_states(int& opened_lights){
    MI InitialPanel (n, vector<int>(m));
    char state;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> state;
            if(state == '.') InitialPanel[i][j] = 0;
            else if(state == '*'){
                InitialPanel[i][j] = 1;
                opened_lights++;
            }
        }
    }
    return InitialPanel;
}

void change_config(int i, int j, MI& ModifiedPanel){
    if(i != 0){
        ModifiedPanel[i - 1][j] = (ModifiedPanel[i - 1][j] + 1) % 2; //up
        if(j != 0)
            ModifiedPanel[i - 1][j - 1] = (ModifiedPanel[i - 1][j - 1] + 1) % 2; //up-left
        if(j != m - 1){
            ModifiedPanel[i - 1][j + 1] = (ModifiedPanel[i - 1][j + 1] + 1) % 2; //up-right
        }
    }
    if(i != n - 1){
        ModifiedPanel[i + 1][j] = (ModifiedPanel[i + 1][j] + 1) % 2; //down
        if(j != 0)
            ModifiedPanel[i + 1][j - 1] = (ModifiedPanel[i + 1][j - 1] + 1) % 2; //down-left
        if(j != m - 1){
            ModifiedPanel[i + 1][j + 1] = (ModifiedPanel[i + 1][j + 1] + 1) % 2; //down-right
        }
    }
    if(j != 0) ModifiedPanel[i][j - 1] = (ModifiedPanel[i][j - 1] + 1) % 2; //left
    if(j != m -1) if(j != 0) ModifiedPanel[i][j + 1] = (ModifiedPanel[i][j + 1] + 1) % 2; //right
    ModifiedPanel[i][j] = ModifiedPanel[i][j] - 1; //actual position 
}

//modifies the state of the lights in those positions near the interruptor
bool dark_room(const MI& InitialPanel, MI& changes_in_lights){
    MI ModifiedPanel = InitialPanel;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(changes_in_lights[i][j] == 1) change_config(i, j, ModifiedPanel);
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(ModifiedPanel[i][j] == 1) return false;
        }
    }
    return true;
}

void compute_cost(int row, int col, const MI& InitialPanel,  MI& changes_in_lights, int num_switches){
    if(col == m){
        col = 0;
        ++row;
    }
    if(row == n){
        if(num_switches < best_config and dark_room(InitialPanel, changes_in_lights)){
            best_config = num_switches;
        }
        return;
    }
    changes_in_lights[row][col] = 0;
    compute_cost(row, col + 1, InitialPanel, changes_in_lights, num_switches);
    changes_in_lights[row][col] = 1;
    num_switches++;
    compute_cost(row, col + 1, InitialPanel, changes_in_lights, num_switches);
}

int main(){
    while(cin >> n >> m){
        int opened_lights = 0;
        MI InitialPanel = read_bulbs_states(opened_lights);
        if(opened_lights == 0){
            cout << 0 << endl; //all lights turned off
        }else{
            MI changes_in_lights(n, vector<int>(m)); //if 1 it means we chenge the state;
            compute_cost(0, 0, InitialPanel, changes_in_lights, 0);
            if(best_config != INT_MAX) cout << best_config << endl;
            else cout << "no" << endl;
        }
    }
}