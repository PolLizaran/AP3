#include <iostream>
#include <vector>

using namespace std;

void print_sol(const vector<int>& radio){
    int s = radio.size();
    bool first = true;
    for(int i = 0; i < s; ++i){
        if(radio[i] == 1){
            if(first){
                cout << i;
                first = false;
            }else cout <<  "," << i;
        }
    }
    cout << endl;
}

//given a song it changes the vector of satisfation if someone is now happy
void check_if_happy(int song, vector<int>& satisfied_friends,
                    const vector<vector<bool>>& interests, int& total_happy_friends,
                    int add){
    for(int i = 0; i < interests.size(); ++i){
        if(interests[i][song]){
            if(add == 1 and satisfied_friends[i] == 0){ //wasn't satisfied yet
                ++total_happy_friends;
            }
            if(add == -1 and satisfied_friends[i] == 1){ //this song was the only one it liked
                --total_happy_friends;
            }
            satisfied_friends[i] += add;
        }
    }
}

//played = number of songs already played. Has to be lower than max_songs
//We will have a vector that determines if a friend is already satisfied. Has to be all tru at the end
//We will have a function that "propagates" if a friend is satisfied with that new song played
//Podríem tenir un comptador per indicar quantes pelis diferents té respecte la resta per maximitzar les repetides
void generate(int k, int played, const int& max_songs, vector<int>& radio,
              vector<int>& satisfied_friends, const vector<vector<bool>>& interests,
              int total_happy_friends, vector<bool>& used){
    if(total_happy_friends == interests.size()){ //could be that more songs can be put but they are all already happy
        print_sol(radio);
    }else if(k < radio.size()){
        radio[k] = 0;
        generate(k + 1, played, max_songs, radio, satisfied_friends, interests, total_happy_friends, used); //sond not played
        if(played < max_songs){
        ++played;
        radio[k] = 1;
        check_if_happy(k, satisfied_friends, interests, total_happy_friends, +1); //modifies satisfaction of each one
        generate(k + 1, played, max_songs, radio, satisfied_friends, interests, total_happy_friends, used); //song played
        check_if_happy(k, satisfied_friends, interests, total_happy_friends, -1);
        --played;
        }
    }
}

int main(){
    int n, num_friends;
    cin >> n >> num_friends;
    vector<vector<bool>> interests(num_friends, vector<bool>(n)); //each friend (row) likes songs (col)
    for(int i = 0; i < num_friends; ++i){
        int x;
        cin >> x;
        for(int j = 0; j < x; ++j){
            int song;
            cin >> song;
            interests[i][song] = true;
        }
    }
    int max_songs;
    cin >> max_songs;

    vector<int> radio(n); //vector of 0 and 1. If 0 the song is not chosen. If one, is chosen
    vector<int> satisfied_friends(n, 0); //if true it means a song it likes has been played
    vector<bool> used(n, false);
    generate(0, 0, max_songs, radio, satisfied_friends, interests, 0, used);
}

/*for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
        cout << interests[i][j] << ' ';
    }
    cout << endl;
}*/
