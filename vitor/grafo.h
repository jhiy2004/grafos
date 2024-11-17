#ifndef GRAFO_H
#define GRAFO_H

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
P_GRAFO criarGrafo(int num);

// Funções de liberação do grafo
void liberarGrafo(P_GRAFO g);
void liberarLista(P_NO lista);

// Funções de remover aresta
void removerAresta(P_GRAFO g, int u, int v);
P_NO removerDaLista(P_NO lista, int v);

// Funções de inserir aresta
void inserirAresta(P_GRAFO g, int u, int v, int peso);
P_NO inserirNaLista(P_NO lista, int v, int peso);

// Busca em Largura
int * buscaEmLargura(P_GRAFO g, int s);

// Busca em Profundidade
int * buscaEmProfundidade(P_GRAFO g, int s);

// Dijkstra

// Árvore Geradora Mínima
int * arvoreGeradoraMinimaPrim(P_GRAFO g, int raiz);

void exibirResultadoBusca(int *resultado, int numVertices);

#endif
