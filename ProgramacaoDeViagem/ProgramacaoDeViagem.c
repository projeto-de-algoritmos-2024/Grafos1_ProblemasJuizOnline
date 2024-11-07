#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MAX 100000000 

typedef int bool; 
typedef int valorPeso; 

typedef struct adj {
    int vertice;
    valorPeso peso;
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

grafo *criar_grafo(int v){
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (vertice *)malloc(v * sizeof(vertice));

    for (int i = 0; i < v; i++)
        g->adj[i].head = NULL;

    return g;
}

adjacencia *criar_adj(int v, int peso){
    adjacencia *nova = (adjacencia *)malloc(sizeof(adjacencia));
    nova->vertice = v;
    nova->peso = peso;
    nova->prox = NULL;
    return nova;
}

bool criar_aresta(grafo *graph, int vert_inicio, int vert_final, valorPeso p){
    if (!graph) return false;
    if (vert_final < 0 || vert_final >= graph->vertices) return false;
    if (vert_inicio < 0 || vert_inicio >= graph->vertices) return false;

    adjacencia *novo = criar_adj(vert_final, p);
    novo->prox = graph->adj[vert_inicio].head;
    graph->adj[vert_inicio].head = novo;

    novo = criar_adj(vert_inicio, p);
    novo->prox = graph->adj[vert_final].head;
    graph->adj[vert_final].head = novo;

    graph->arestas++;
    return true;
}

void dijkstra(grafo *graph, int inicio, int distancia[], int pai[]){
    bool visited[graph->vertices];

    for (int i = 0; i < graph->vertices; i++) {
        distancia[i] = MAX;
        pai[i] = -1;
        visited[i] = false;
    }

    distancia[inicio] = 0;

    for (int i = 0; i < graph->vertices; i++) {
        int min = MAX, u = -1;

        for (int j = 0; j < graph->vertices; j++) {
            if (!visited[j] && distancia[j] < min) {
                min = distancia[j];
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        adjacencia *adj = graph->adj[u].head;
        while (adj) {
            int v = adj->vertice;
            int peso = adj->peso;

            if (distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                pai[v] = u;
            }

            adj = adj->prox;
        }
    }
}

int main(){
    int c, e;

    while (scanf("%d %d", &c, &e) && (c != 0 && e != 0)){
        int d;
        grafo *graph = criar_grafo(c);

        for (int i = 0; i < e; i++){
            int c1, c2, t;
            scanf("%d %d %d", &c1, &c2, &t);
            criar_aresta(graph, c1 - 1, c2 - 1, t);
        }

        scanf("%d", &d);
        d--;

        int distancia[c], pai[c];
        dijkstra(graph, d, distancia, pai);

        int tempoTotal = distancia[0];

        if (tempoTotal <= 120){
            printf("Will not be late. Travel time - %d - best way - ", tempoTotal);

            int destino = 0;
            int pilha[c], topo = 0;

            while (pai[destino] != -1) {
                pilha[topo++] = destino;
                destino = pai[destino];
            }

            printf("%d", destino + 1);

            while (topo > 0) {
                printf(" %d", pilha[--topo] + 1);
            }
            printf("\n");

        } else {
            int atraso = tempoTotal - 120;
            printf("It will be %d minutes late. Travel time - %d - best way - ", atraso, tempoTotal);

            int destino = 0;
            int pilha[c], topo = 0;

            while (pai[destino] != -1) {
                pilha[topo++] = destino;
                destino = pai[destino];
            }

            printf("%d", destino + 1);

            while (topo > 0) {
                printf(" %d", pilha[--topo] + 1);
            }
            printf("\n");
        }

        for (int i = 0; i < c; i++) {
            adjacencia *adj = graph->adj[i].head;
            while (adj) {
                adjacencia *temp = adj;
                adj = adj->prox;
                free(temp);
            }
        }
        free(graph->adj);
        free(graph);
    }

    return 0;
}
