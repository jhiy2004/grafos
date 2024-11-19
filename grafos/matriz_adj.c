#include <limits.h>
#include <stdlib.h>
#include "../auxiliares/fila.h"
#include "../auxiliares/pilha.h"
#include "../auxiliares/heap_bin.h"
#include "matriz_adj.h"

// Cria um grafo representado por uma matriz de adjacência.
Grafo* criarGrafoMA(int n) {
    int i, j;
    Grafo* g = malloc(sizeof(Grafo));

    g->n = n;
    g->adj = malloc(n * sizeof(int*));
    for(i = 0; i < n; i++)
        g->adj[i] = malloc(n * sizeof(int));

    // Inicializa a matriz com 0 (sem arestas).
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            g->adj[i][j] = 0;

    return g;
}

// Destrói um grafo e libera a memória.
void destruirGrafoMA(Grafo* g) {
    int i;
    for(i = 0; i < g->n; i++)
        free(g->adj[i]);

    free(g->adj);
    free(g);
}


// Insere uma aresta não direcionada entre os vértices u e v.
void inserirArestaMA(Grafo* g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

// Insere uma aresta com peso entre os vértices u e v.
void inserirArestaPesoMA(Grafo* g, int u, int v, int peso) {

    g->adj[u][v] = peso;
    g->adj[v][u] = peso;
}


// Remove a aresta entre os vértices u e v.
void removerArestaMA(Grafo* g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}


// Verifica se existe uma aresta entre u e v.
int possuiArestaMA(Grafo* g, int u, int v) {
    return g->adj[u][v];
}

// Busca em profundidade utilizando pilha.
BUSCA buscaProfundidadeMA(Grafo *g, int s) {
    int v;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->n * sizeof(int));
    resultado.custo = (int *)malloc(g->n * sizeof(int));
    int *visitado = (int*) malloc(g->n * sizeof(int));

    P_PILHA p = criarPilha();

    // Inicializa os vetores de resultado e os estados dos vértices.
    for(v = 0; v < g->n; v++) {
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    // Processa o vértice inicial.
    empilhar(p, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;

    // Explora os vértices.
    while(!pilhaVazia(p)) {
        v = desempilar(p);
        visitado[v] = 1;

        for(int i = 0; i < g->n; i++) {
            if(g->adj[v][i] && !visitado[i]) {
                resultado.pai[i] = v;
                resultado.custo[i] = resultado.custo[v] + g->adj[v][i];
                empilhar(p, i);
            }
        }
    }

    destroiPilha(p);
    free(visitado);
    return resultado;
}

// Busca em largura utilizando fila.
BUSCA buscaLarguraMA(Grafo *g, int s) {
    int v;
    BUSCA resultado;
    resultado.pai = (int*)malloc(g->n * sizeof(int));
    resultado.custo = (int*)malloc(g->n * sizeof(int));
    int *visitado = (int*)malloc(g->n * sizeof(int));

    P_FILA f = criarFila();

    // Inicializa os vetores de resultado e os estados dos vértices.
    for(v = 0; v < g->n; v++) {
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    // Processa o vértice inicial.
    enfileira(f, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    visitado[s] = 1;

    // Explora os vértices.
    while(!filaVazia(f)) {
        v = desenfileira(f);
        for(int i = 0; i < g->n; i++) {
            if(g->adj[v][i] && !visitado[i]) {
                resultado.pai[i] = v;
                resultado.custo[i] = resultado.custo[v] + g->adj[v][i];
                enfileira(f, i);
                visitado[i] = 1;
            }
        }
    }

    destroiFila(f);
    free(visitado);
    return resultado;
}

// Algoritmo de Dijkstra para encontrar o caminho mínimo.
BUSCA dijkstraMA(Grafo* g, int s) {
    int v;
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->n * sizeof(int));
    resultado.custo = (int*) malloc(g->n * sizeof(int));
    FP* h = criarFprio(g->n);

    // Inicializa os vetores de resultado e a fila de prioridade.
    for (v = 0; v < g->n; v++) {
        resultado.pai[v] = -1;
        resultado.custo[v] = INT_MAX;
        insereFP(h, v, INT_MAX);
    }

    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    diminuiprioridade(h, s, 0);

    // Executa o algoritmo de Dijkstra.
    while (!vaziaFP(h)) {
        v = extraiMinimoFP(h);
        int custoAtual = resultado.custo[v];
        if (prioridadeFP(h, v) != INT_MAX) {
            for (int i = 0; i < g->n; i++) {
                int novoCusto = custoAtual + g->adj[v][i];
                if (g->adj[v][i] && novoCusto < prioridadeFP(h, i)) {
                    resultado.custo[i] = novoCusto;
                    diminuiprioridade(h, i, novoCusto);
                    resultado.pai[i] = v;
                }
            }
        }
    }

    return resultado;
}


BUSCA geradoraMinimaMA(Grafo* g, int s) {
    int v;
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->n * sizeof(int));
    resultado.custo = (int*) malloc(g->n * sizeof(int));
    int *visitado = (int*)malloc(g->n * sizeof(int));
    
    FP* h = criarFprio(g->n);
    for (v = 0; v < g->n; v++) {
        resultado.pai[v] = -1;
        resultado.custo[v] = INT_MAX;
        insereFP(h, v, INT_MAX);
        visitado[v] = 0;
    }
    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    diminuiprioridade(h, s, 0);
    visitado[0] = 1;

    while (!vaziaFP(h)) {
        v = extraiMinimoFP(h);

        visitado[v] = 1;

        if (prioridadeFP(h, v) != INT_MAX)
            for (int i = 0; i < g->n; i++){
                if (g->adj[v][i] != 0 && !visitado[i]){
                    if (g->adj[v][i] < prioridadeFP(h, i)) {
                        diminuiprioridade(h, i, g->adj[v][i]);
                        resultado.pai[i] = v;
                        resultado.custo[i] = g->adj[v][i];
                    }
                }
            }
    }
    return resultado;
}

