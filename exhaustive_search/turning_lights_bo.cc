//Un punt indica una bombeta apagada, i un asterisc una bombeta encesa.
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using MC = vector<vector<char>>;

//reads data and modifies opened_lights
void read_bulbs_states(vector<vector<char>>& InitialPanel, int& opened_lights, int n, int m){
    char state;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> state;
            InitialPanel[i][j] = state;
            if(state == '*') ++opened_lights;
        }
    }
}

//modifies the state of the lights in those positions near the interruptor
int update(MC& Panel, int row, int col, int n, int m){
    int changed_lights = 0; //diference between on and off lights
    for(int ii = - 1; ii <= 1; ++ii){
        for(int jj = - 1; jj <= 1; ++jj){
            if(row + ii >= 0 && row + ii < n and 
               col + jj >= 0 && col + jj < m){ //dins límits
                if(Panel[row + ii][col + jj] == '*'){
                    Panel[row + ii][col + jj] = '.';
                    --changed_lights; //una llum menys encesa
                }else if(Panel[row + ii][col + jj] == '.'){
                    Panel[row + ii][col + jj] = '*';
                    ++changed_lights;
                }
            }
        }
    }
    return changed_lights;
}

//la primera columna i fila s'han de generat pels dos casos perquè no tornarem a tenir oportunitat de canviar-les
//generem d'esquerra a dreta i de dalt a baix
void compute_cost(int row, int col, MC& Panel, int& best_config, int num_switches, int on, int n, int m){
    if(num_switches < best_config){ //restricció de poda en la generació
        if(on == 0){
            best_config = num_switches;
        }else if(row < n){
            char c = 'k'; //caracter random que usarem per generar per la primera fila i columna
            if(row > 0 && col > 0) c = Panel[row - 1][ col - 1];

            if(c != '*'){ //significa que ja tenim la llum apagada i per tant ens interessa mantenir-ho
                if(col < m - 1) compute_cost(row, col + 1, Panel, best_config, num_switches, on, n , m); //encara no hem arribat al final de la fila
                else compute_cost(row + 1, 0, Panel, best_config, num_switches, on, n, m);
            }

            if(c != '.'){ //llum encesa, convé apagar
                int num_changes = update(Panel, row, col, n, m);

                //modifiquem el Panel, per tant polsem un interruptor
                if(col < m - 1) compute_cost(row, col + 1, Panel, best_config, num_switches + 1, on + num_changes, n, m); 
                else compute_cost(row + 1, 0, Panel, best_config, num_switches + 1, on + num_changes, n, m);
                update(Panel, row, col, n, m); //MOOOOOLT IMPORTANT, retornem a estat inicial
            }
        }
    }
}

int main(){
    int n, m;
    while(cin >> n >> m){
        int opened_lights = 0;
        int best_config = INT_MAX;
        vector<vector<char>> InitialPanel(n, vector<char>(m));
        read_bulbs_states(InitialPanel, opened_lights, n, m);
        compute_cost(0, 0, InitialPanel, best_config, 0, opened_lights, n, m);
        if(best_config != INT_MAX) cout << best_config << endl;
        else cout << "no" << endl;
    }
}