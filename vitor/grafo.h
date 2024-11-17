#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000000

typedef struct NO {
    int v;
    struct NO *prox;
} NO;

typedef NO * P_NO;

typedef struct GRAFO {
    P_NO *adjacencia;
    int num;
} GRAFO;

typedef GRAFO * P_GRAFO;

// Funçãp de crição do grafo
P_GRAFO criarGrafo(int num);

// Funções de liberação do grafo
void liberarGrafo(P_GRAFO g);
void liberarLista(P_NO lista);

// Funções de remover aresta
void removerAresta(P_GRAFO g, int u, int v);
P_NO removerDaLista(P_NO lista, int v);

// Funções de inserir aresta
void inserirAresta(P_GRAFO g, int u, int v);
P_NO inserirNaLista(P_NO lista, int v);

// REFAZER AS FUNÇÕES ABAIXO E ESTUDAR TUDO NO ONIBUS

// Busca em Largura
void buscaEmLargura(GRAFO *grafo, int inicio);

// Busca em Profundidade
int * encontraComponentes(P_GRAFO g);
void visitaRec(P_GRAFO g, int *componentes, int comp, int v);

// Dijkstra
void dijkstra(GRAFO *grafo, int inicio);

// Árvore Geradora Mínima (Algoritmo de Prim)
void arvoreGeradoraMinima(GRAFO *grafo);

#endif
