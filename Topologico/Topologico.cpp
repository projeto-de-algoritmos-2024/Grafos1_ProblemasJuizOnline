#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Solution {
    void DFS(int x, int atual, vector<vector<int>> &ancestrais, vector<vector<int>> &Grafofilho){

        for(int u : Grafofilho[atual]){
            if(ancestrais[u].empty() || ancestrais[u].back() != x){ //se nao tem ancestrais ou nao tem x como anc, add x
                ancestrais[u].push_back(x); //funcao de adicionar ao final do vetor
                DFS(x, u, ancestrais, Grafofilho); //continua a dfs
            }
        }
    }

public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> ancestrais(n), Grafofilho(n);
        for(auto& e : edges){
            Grafofilho[e[0]].push_back(e[1]); //coloca e[1] como filho de e[0]
        }
        for(int i=0; i<n; i++) DFS(i, i, ancestrais, Grafofilho);

        return ancestrais; //retorna o vetor de ancetrais de cada nó
    }
};