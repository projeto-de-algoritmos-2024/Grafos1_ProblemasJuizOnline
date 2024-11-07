#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Solution { 

public:
  
    bool isBipartite(vector<vector<int>>& graph){
        int numNos = graph.size();  //checa o tamanho do grafo
            
        vector<int> cor(numNos, -1); //vetor para marcar as cores -1 nao foi visitado

        for(int inicio=0; inicio<numNos; inicio++){ //percorre o grafo
            if(cor[inicio]== -1){
                queue<int> fila;
                fila.push(inicio);
                cor[inicio] = 1; //marca o primeiro com uma cor

                while(!fila.empty()){
                    int pai = fila.front(); //acrescenta os nós na fila conforme uma BFS
                    fila.pop();
        
                    for (int vizinho : graph[pai]) { 
                        if (cor[vizinho]== -1) {
                            cor[vizinho] = 1 - cor[pai]; //se o vizinho nao foi visitado, marca com uma cor oposta ao pai
                            fila.push(vizinho);
                    } else if(cor[vizinho] == cor[pai]) return false; // se tiverem a mesma cor nao pode ser bipartido
                } 
             }
            }
         }
        
        return true; 
    
}
};



