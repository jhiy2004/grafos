#ifndef GRAFO_H
#define GRAFO_H

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

// Função de crição do grafo
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

// Busca em Largura
int * buscaEmLargura(P_GRAFO g, int s);

// Busca em Profundidade
int * buscaEmProfundidade(P_GRAFO g, int s);

// Dijkstra

// Árvore Geradora Mínima (Algoritmo de Prim)

#endif
