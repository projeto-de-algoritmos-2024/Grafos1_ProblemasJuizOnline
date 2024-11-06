#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAX 100000000 

typedef int bool; 
typedef int valorPeso; 

// Estrutura para representar uma adjacência, ou seja, uma aresta para outro vértice
typedef struct adj {
    int vertice; // Vértice de destino
    valorPeso peso; // Peso associado à aresta que leva ao vértice de destino
    struct adjacencia *prox; // Ponteiro para o próximo elemento da lista de adjacências
} adjacencia;

// Estrutura para representar um vértice
typedef struct vert {
    adjacencia *head; // Cabeça da lista de adjacências (arestas ligadas a este vértice)
} vertice;

// Estrutura para representar o grafo
typedef struct graph {
    int vertices; // Número total de vértices
    int arestas; // Número total de arestas
    vertice *adj; // Array de vértices
} grafo;

// Função para criar o grafo
grafo *criar_grafo(int v){
    int ind;

    grafo *g = (grafo *)malloc(sizeof(grafo)); // Aloca memória para o grafo
    g->vertices = v; // Define o número de vértices
    g->arestas = 0; // Inicia o número de arestas em 0
    g->adj = (vertice *)malloc(v * sizeof(vertice)); // Aloca memória para os vértices

    for(ind = 0; ind < v; ind++){
        g->adj[ind].head = NULL; // Inicializa a lista de adjacências de cada vértice como vazia
    }

    return g;
}

// Função para criar uma adjacência, ou seja, uma aresta que leva a outro vértice
adjacencia *criar_adj(int v, int peso){
    adjacencia *salva = (adjacencia *)malloc(sizeof(adjacencia)); // Aloca memória para a nova adjacência
    salva->vertice = v; // Define o vértice de destino
    salva->peso = peso; // Define o peso da aresta
    salva->prox = NULL; // Inicializa o próximo como NULL
    return salva;
}

// Função para adicionar uma aresta bidirecional no grafo
bool criar_aresta(grafo *graph, int vert_inicio, int vert_final, valorPeso p){
    if (!graph) return false; // Verifica se o grafo existe
    if (vert_final < 0 || vert_final >= graph->vertices) return false; // Verifica se o vértice final é válido
    if (vert_inicio < 0 || vert_inicio >= graph->vertices) return false; // Verifica se o vértice inicial é válido

    // Cria uma adjacência do vértice inicial para o vértice final
    adjacencia *novo = criar_adj(vert_final, p);
    novo->prox = graph->adj[vert_inicio].head; // Insere no início da lista de adjacências
    graph->adj[vert_inicio].head = novo;

    // Cria uma adjacência na direção oposta (vértice final para o inicial)
    novo = criar_adj(vert_inicio, p);
    novo->prox = graph->adj[vert_final].head;
    graph->adj[vert_final].head = novo;

    graph->arestas++; // Incrementa o número de arestas
    return true;
}

// Algoritmo de Dijkstra para encontrar o caminho mais curto do vértice de inicio para os demais
void dijkstra(grafo *graph, int inicio, int distancia[], int pai[]){
    bool visited[graph->vertices]; // Array para marcar os vértices visitados

    // Inicializa as distâncias como "infinito" e os pais como -1 (nenhum caminho encontrado ainda)
    for (int i = 0; i < graph->vertices; i++) {
        distancia[i] = MAX;
        pai[i] = -1;
        visited[i] = false;
    }

    distancia[inicio] = 0; // A distância para a inicio é 0

    // Loop principal do algoritmo de Dijkstra
    for (int i = 0; i < graph->vertices; i++) {
        int min = MAX, u = -1;

        // Encontra o vértice não visitado com a menor distância até o momento
        for (int j = 0; j < graph->vertices; j++) {
            if (!visited[j] && distancia[j] < min) {
                min = distancia[j];
                u = j;
            }
        }

        if (u == -1) break; // Se não há vértices restantes, encerra o loop

        visited[u] = true; // Marca o vértice atual como visitado

        // Atualiza as distâncias para os vértices adjacentes
        adjacencia *adj = graph->adj[u].head;
        while(adj){
            int v = adj->vertice;
            int peso = adj->peso;

            if(distancia[u] + peso < distancia[v]){
                distancia[v] = distancia[u] + peso; // Atualiza a distância para o vértice
                pai[v] = u; // Define o pai do vértice como o vértice atual
            }

            adj = adj->prox; // Vai para o próximo adjacente
        }
    }
}

int main(){
    int c, e;

    // Lê os casos de teste até encontrar "0 0" para encerrar
    while(scanf("%d %d", &c, &e) && (c != 0 && e != 0)){
        int d;
        grafo *graph = criar_grafo(c); // Cria o grafo com c vértices

        // Lê as e arestas e cria as conexões no grafo
        for(int i = 0; i < e; i++){
            int c1, c2, t;
            scanf("%d %d %d", &c1, &c2, &t);
            criar_aresta(graph, c1-1, c2-1, t); // Ajusta para índice 0
        }

        scanf("%d", &d); // Lê a cidade atual de Valentina
        d--;

        int distancia[c], pai[c]; // Arrays para armazenar as distâncias e os pais dos vértices
        dijkstra(graph, d, distancia, pai); // Executa Dijkstra a partir da cidade atual

        int tempoTotal = distancia[0]; // A distância para a cidade de inicio (cidade 1)

        // Verifica se Valentina chegará a tempo ou vai se atrasar
        if(tempoTotal <= 120){ 
            printf("Will not be late. Travel time - %d - best way - ", tempoTotal);
            
            // Imprime o caminho de volta para a cidade de inicio
            int destino = 0;
            int pilha[c], topo = 0; // Pilha para armazenar o caminho na ordem correta

            while(pai[destino] != -1){ // Armazena os vértices em ordem reversa
                pilha[topo++] = destino;
                destino = pai[destino];
            }

            printf("%d ", destino + 1); // Imprime a cidade de inicio

            while(topo > 0){ // Imprime o caminho na ordem correta
                printf("%d ", pilha[--topo] + 1);
            }

            printf("\n");

        } else{ // Caso haja atraso, o calcula
            int atraso = tempoTotal - 120;
            printf("It will be %d minutes late. Travel time - %d - best way - ", atraso, tempoTotal);
            
            // Imprime o caminho de volta para a cidade de inicio
            int destino = 0;
            int pilha[c], topo = 0;
            
            while(pai[destino] != -1){
                pilha[topo++] = destino;
                destino = pai[destino];
            }

            printf("%d ", destino + 1);

            while(topo > 0){
                printf("%d ", pilha[--topo] + 1);
            }
            printf("\n");
        }
    }

    return 0;
}