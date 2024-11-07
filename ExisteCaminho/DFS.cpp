#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Solution { 

public:
  
    bool validPath(int numNos, vector<vector<int>> arestas, int inicio, int final){
            if(inicio == final) return true;
            
            vector<vector<int>> listaAdj(numNos);

            for(vector<int> v : arestas){
                listaAdj[v[0]].push_back(v[1]);
                listaAdj[v[1]].push_back(v[0]);
            }
            vector<bool> visitado(numNos, false);
            return DFS(inicio, final, listaAdj, visitado);
}

    bool DFS(int inicio, int final, vector<vector<int>>&listaAdj, vector<bool> &visitado) {
        stack<int> pilha;
        pilha.push(inicio);
        visitado[inicio] = true;

        while(!pilha.empty()){
            int u = pilha.top();
            pilha.pop();
            if (u == final) return true; 
        
            for (auto v : listaAdj[u]) {
                if (!visitado[v]) {
                    visitado[v] = true;
                    pilha.push(v);
                    }
                }
        }
        
        return false; 
    }
};



