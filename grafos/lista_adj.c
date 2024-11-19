/*
 * lista_adj.c
 * Implementação das funções para manipulação de grafos utilizando listas de adjacência.
 * Contém a criação, liberação, inserção, remoção de arestas e algoritmos de busca e caminhos mínimos.
 */

#include <stdlib.h>
#include <limits.h>
#include "lista_adj.h"
#include "../auxiliares/fila.h"
#include "../auxiliares/pilha.h"
#include "../auxiliares/heap_bin.h"

// Criação de um grafo com listas de adjacência.
P_GRAFO criarGrafoLA(int num){
    int i;
    P_GRAFO g = (P_GRAFO) malloc(sizeof(GRAFO));
    g->num = num;
    g->adjacencia = (P_NO*) malloc(num * sizeof(P_NO));
    
    // Inicializa todas as listas de adjacência como vazias (NULL).
    for(i = 0; i < num; i++){
        g->adjacencia[i] = NULL;
    }

    return g;
}

// Libera a memória de um grafo e suas listas.
void liberarGrafoLA(P_GRAFO g){
    int i;
    for(i = 0; i < g->num; i++){
        liberarListaLA(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

// Libera a memória de uma lista de adjacência recursivamente.
void liberarListaLA(P_NO lista){
    while(lista != NULL){
        liberarListaLA(lista->prox);
        free(lista);
    }
}

// Insere uma aresta bidirecional no grafo.
void inserirArestaLA(P_GRAFO g, int u, int v, int peso){
    g->adjacencia[v] = inserirNaListaLA(g->adjacencia[v], u, peso);
    g->adjacencia[u] = inserirNaListaLA(g->adjacencia[u], v, peso);
}

// Insere um nó em uma lista de adjacência.
P_NO inserirNaListaLA(P_NO lista, int v, int peso){
    P_NO novo = (P_NO) malloc(sizeof(NO));
    novo->v = v;
    novo->peso = peso;
    novo->prox = lista;
    return novo;
}

// Remove uma aresta bidirecional do grafo.
void removerArestaLA(P_GRAFO g, int u, int v){
    g->adjacencia[u] = removerDaListaLA(g->adjacencia[u], v);
    g->adjacencia[v] = removerDaListaLA(g->adjacencia[v], u);
}

// Remove um nó de uma lista de adjacência.
P_NO removerDaListaLA(P_NO lista, int v){
    P_NO proximo;
    if(lista == NULL){
        return NULL;
    } else if(lista->v == v){
        proximo = lista->prox;
        free(lista);
        return proximo;
    } else {
        lista->prox = removerDaListaLA(lista->prox, v);
        return lista;
    }
}

// Busca em profundidade utilizando pilha para explorar os vértices.
BUSCA buscaEmProfundidadeLA(P_GRAFO g, int s){
    int v;
    P_NO t;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->num * sizeof(int));
    resultado.custo = (int *)malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_PILHA p = criarPilha();

    // Inicializa os vetores de resultado e o estado dos vértices.
    for(v = 0; v < g->num; v++){
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    // Processa o vértice inicial.
    empilhar(p, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;

    // Exploração da pilha.
    while(!pilhaVazia(p)){
        v = desempilar(p);
        visitado[v] = 1;

        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            if(!visitado[t->v]){
                resultado.pai[t->v] = v;
                resultado.custo[t->v] = resultado.custo[v] + t->peso;
                empilhar(p, t->v);
            }
        }
    }

    // Libera estruturas auxiliares.
    destroiPilha(p);
    free(visitado);

    return resultado;
}

// Busca em largura utilizando fila para explorar os vértices.
BUSCA buscaEmLarguraLA(P_GRAFO g, int s){
    int v;
    P_NO t;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->num * sizeof(int));
    resultado.custo = (int *)malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_FILA f = criarFila();

    // Inicializa os vetores de resultado e o estado dos vértices.
    for(v = 0; v < g->num; v++){
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    // Processa o vértice inicial.
    enfileira(f, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    visitado[s] = 1;

    // Exploração da fila.
    while(!filaVazia(f)){
        v = desenfileira(f);
        
        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            if(!visitado[t->v]){
                visitado[t->v] = 1;
                resultado.pai[t->v] = v;
                resultado.custo[t->v] = resultado.custo[v] + t->peso;
                enfileira(f, t->v);
            }
        }
    }

    // Libera estruturas auxiliares.
    destroiFila(f);
    free(visitado);

    return resultado;
}

// Implementação de Dijkstra
BUSCA dijkstraLA(P_GRAFO g, int s){
    int v;
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->num * sizeof(int));
    resultado.custo = (int*) malloc(g->num * sizeof(int));
    P_NO t;
    FP *h = criarFprio(g->num);

    for(v = 0; v < g->num; v++){
        resultado.pai[v] = -1;
        resultado.custo[v] = INT_MAX;
        insereFP(h, v, INT_MAX);
    }

    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    diminuiprioridade(h, s, 0);

    while(!vaziaFP(h)){
        v = extraiMinimoFP(h);
        int custoAtual = resultado.custo[v];

        if(prioridadeFP(h, v) != INT_MAX){
            for(t = g->adjacencia[v]; t != NULL; t = t->prox){
                int novoCusto = custoAtual + t->peso;
                if(prioridadeFP(h, v) + t->peso < prioridadeFP(h, t->v)){
                    resultado.custo[t->v] = novoCusto;
                    diminuiprioridade(h, t->v, prioridadeFP(h, v) + t->peso);
                    resultado.pai[t->v] = v;
                }
            }
        }
    }

    return resultado;
}

// Implementação da árvore geradora mínima
BUSCA arvoreGeradoraMinimaPrimLA(P_GRAFO g, int s) {
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->num * sizeof(int));
    resultado.custo = (int*) malloc(g->num * sizeof(int));
    int *visitado = (int*) calloc(g->num, sizeof(int));

    // Inicialização
    for (int i = 0; i < g->num; i++) {
        resultado.custo[i] = INT_MAX;
        resultado.pai[i] = -1;
    }
    resultado.custo[s] = 0;
    resultado.pai[s] = s;

    for (int i = 0; i < g->num; i++) {
        // Escolher o vértice não visitado de menor custo
        int u = -1;
        for (int v = 0; v < g->num; v++) {
            if (!visitado[v] && (u == -1 || resultado.custo[v] < resultado.custo[u])) {
                u = v;
            }
        }

        if (resultado.custo[u] == INT_MAX) {
            break; // Grafo desconectado
        }

        visitado[u] = 1;

        // Atualizar os custos dos vizinhos
        for (P_NO t = g->adjacencia[u]; t != NULL; t = t->prox) {
            if (!visitado[t->v] && t->peso < resultado.custo[t->v]) {
                resultado.custo[t->v] = t->peso;
                resultado.pai[t->v] = u;
            }
        }
    }

    free(visitado);

    return resultado;
}
