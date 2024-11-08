#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;

typedef struct adj {
    int vertice;
    struct adj *prox;
} adjacencia;

typedef struct vert {
    adjacencia *head;
} vertice;

typedef struct graph {
    int vertices;
    int arestas;
    vertice *adj;
} grafo;

// Função para criar o grafo
grafo *criar_grafo(int v){
    int ind;
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (vertice *)malloc(v * sizeof(vertice));
    for(ind = 0; ind < v; ind++){
        g->adj[ind].head = NULL;
    }
    return g;
}

// Função para criar uma adjacência (aresta)
adjacencia *criar_adj(int v){
    adjacencia *salva = (adjacencia *)malloc(sizeof(adjacencia));
    salva->vertice = v;
    salva->prox = NULL;
    return salva;
}

// Função para adicionar uma aresta direcionada no grafo
bool criar_aresta(grafo *graph, int vert_inicio, int vert_final){
    if (!graph) return false;
    if (vert_final < 0 || vert_final >= graph->vertices) return false;
    if (vert_inicio < 0 || vert_inicio >= graph->vertices) return false;

    // Cria uma adjacência do vértice inicial para o vértice final
    adjacencia *novo = criar_adj(vert_final);
    novo->prox = graph->adj[vert_inicio].head;
    graph->adj[vert_inicio].head = novo;

    graph->arestas++;
    return true;
}

int main() {
    int num;                   // Número de aviões (vértices) no grafo
    scanf("%d", &num);

    // Cria o grafo com n vértices
    grafo *g = criar_grafo(num);

    // Ler as preferências de cada avião e adiciona uma aresta direcionada no grafo
    for(int i = 0; i < num; i++){
        int vi, vf;
        scanf("%d", &vf);     // Lê o número do avião que o avião i+1 gosta
        vf--;
        vi=i;                 
        criar_aresta(g, i, vf); // Adiciona uma aresta de i para f no grafo
    }

    // Verificar se há um triângulo de amor (um ciclo de 3 vértices)
    for(int i = 0; i < num; i++){
        int A = i;                      // Define a como o vértice inicial
        adjacencia *adjB = g->adj[A].head; // Pega a primeira adjacência de a

        if(adjB){                      // Verifica se a tem uma adjacência
            int B = adjB->vertice;     // Define b como o vértice destino de a
            adjacencia *adjC = g->adj[B].head; // Pega a primeira adjacência de b

            if(adjC){                  // Verifica se b tem uma adjacência
                int C = adjC->vertice; // Define c como o vértice destino de b
                adjacencia *adjA = g->adj[C].head; // Pega a primeira adjacência de c

                if(adjA && adjA->vertice == A){ // Verifica se c aponta de volta para a
                    printf("YES\n");    // Um triângulo de amor foi encontrado
                    return 0;           
                }
            }
        }
    }

    printf("NO\n");                     // Se nenhum triângulo foi encontrado, imprime "NO"
    return 0;
}