#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class Grafo { 

public:
  
    bool temCaminho(int numNos, vector<vector<int>> arestas, int inicio, int final){
            if(inicio == final) return true;
            
            vector<vector<int>> listaAdj(numNos);

            for(vector<int> v : arestas){
                listaAdj[v[0]].push_back(v[1]);
                listaAdj[v[1]].push_back(v[0]);
            }
            map<int, bool> visitado;
            return DFS(inicio, final, listaAdj, visitado);
}

    bool DFS(int u, int final, vector<vector<int>>&listaAdj, map<int, bool> &visitado) {
        if (u == final) {
            return true; 
        }

        visitado[u] = true;

        for (auto v : listaAdj[u]) {
            if (!visitado[v]) {
                if (DFS(v, final, listaAdj, visitado)) {
                    return true; 
                }
            }
        }
        
        return false; 
    }
};



