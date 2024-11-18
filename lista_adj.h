#ifndef GRAFO_H
#define GRAFO_H

#include "auxiliares.h"

typedef struct NO {
    int v;
    int peso;
    struct NO *prox;
} NO;

typedef NO * P_NO;

typedef struct GRAFO {
    P_NO *adjacencia;
    int num;
} GRAFO;

typedef GRAFO * P_GRAFO;

// Função de crição do grafo
P_GRAFO criarGrafoLA(int num);

// Funções de liberação do grafo
void liberarGrafoLA(P_GRAFO g);
void liberarListaLA(P_NO lista);

// Funções de remover aresta
void removerArestaLA(P_GRAFO g, int u, int v);
P_NO removerDaListaLA(P_NO lista, int v);

// Funções de inserir aresta
void inserirArestaLA(P_GRAFO g, int u, int v, int peso);
P_NO inserirNaListaLA(P_NO lista, int v, int peso);

// Busca em Largura
BUSCA buscaEmLarguraLA(P_GRAFO g, int s);

// Busca em Profundidade
BUSCA buscaEmProfundidadeLA(P_GRAFO g, int s);

// Dijkstra
BUSCA dijkstraLA(P_GRAFO g, int s);

// Árvore Geradora Mínima
BUSCA arvoreGeradoraMinimaPrimLA(P_GRAFO g, int s);

#endif
