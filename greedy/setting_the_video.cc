#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using episode = pair<int, int>; //stores the beggining and ending of each episode

const int& UNDEF = -1;

struct info{
    int id;
    episode duration;
    int lenght;
};

bool compare_initial_moment(const info& A, const info& B){
    return A.duration.first < B.duration.first;
}

bool compare_lenghts(const info& A, const info& B){
    if(A.lenght == B.lenght) return A.id < B.id;
    return A.lenght < B.lenght;
}

void read_episodes(vector<info>& episodes_by_init){
    int begining, ending;
    for(int i = 0; i < episodes_by_init.size(); ++i){
        cin >> begining >> ending;
        episodes_by_init[i] = {UNDEF, {begining, ending}, ending - begining};
    }
}

void set_identifier(vector<info>& episodes_by_init){
    int id = 0;
    for(info& u : episodes_by_init){
        u.id = id;
        ++id;
    }
}

bool compatible(const vector<info>& episodes_by_init, int i, int j){
    //cout << episodes[i].duration.second << '<' << episodes[j].duration.first << endl;
    return episodes_by_init[i].duration.second < episodes_by_init[j].duration.first;
}

//now ordered by lenght
int recorderings(const vector<info>& episodes_by_lenght,
                 const vector<vector<int>>& overlaps){
    vector<bool> mkd(episodes_by_lenght.size(), false);
    int num_episodes = 0, marked_elements = 0;
    for(int i = 0; i < episodes_by_lenght.size() and marked_elements < episodes_by_lenght.size(); ++i){
        if(not mkd[i]){ //i is the element of episodes_by_lenght
            mkd[i] = true;
            ++marked_elements;
            ++num_episodes;
            for(int u : overlaps[episodes_by_lenght[i].id]){
                if(not mkd[u]){
                    mkd[u] = true;
                    ++marked_elements;
                }
            }
        }
    }
    return num_episodes;
}


void set_overlaps(vector<vector<int>>& overlaps, const vector<info>& episodes_by_init){
    for(int i = 0; i < overlaps.size(); ++i){
        int j = i + 1;
        while(j < overlaps.size() and not compatible(episodes_by_init, i, j)){
                overlaps[i].push_back(j);
                overlaps[j].push_back(i);
                ++j;
        }
        //if(episodes[i].duration.second << '<' << episodes[j].duration.first
    }
}

int main(){
    int n;
    while(cin >> n){
        vector<info> episodes_by_init(n);
        read_episodes(episodes_by_init);
        sort(episodes_by_init.begin(), episodes_by_init.end(), compare_initial_moment);
        set_identifier(episodes_by_init);
        vector<vector<int>> overlaps(n);
        set_overlaps(overlaps, episodes_by_init);
        vector<info> episodes_by_lenght = episodes_by_init;
        sort(episodes_by_lenght.begin(), episodes_by_lenght.end(), compare_lenghts);
        cout << recorderings(episodes_by_lenght, overlaps) << endl;
    }
}
