#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "fila.h"
#include "pilha.h"

// Criação do grafo
P_GRAFO criarGrafo(int num){
    int i;
    P_GRAFO g = (P_GRAFO) malloc(sizeof(GRAFO));
    g->num = num;
    g->adjacencia = (P_NO*) malloc(num * sizeof(P_NO));
    
    for(i=0; i < num; i++){
        g->adjacencia[i] = NULL;
    }

    return g;
}

// Liberação do grafo
void liberarGrafo(P_GRAFO g){
    int i;
    for(i=0; i < g->num; i++){
        liberarLista(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

// Liberar as listas do grafo
void liberarLista(P_NO lista){
    while(lista != NULL){
        liberarLista(lista->prox);
        free(lista);
    }
}

// Adicionar aresta ao grafo
void inserirAresta(P_GRAFO g, int u, int v, int peso){
    g->adjacencia[v] = inserirNaLista(g->adjacencia[v], u, peso);
    g->adjacencia[u] = inserirNaLista(g->adjacencia[u], v, peso);
}

P_NO inserirNaLista(P_NO lista, int v, int peso){
    P_NO novo = (P_NO) malloc(sizeof(NO));
    novo->v = v;
    novo->peso = peso;
    novo->prox = lista;
    return novo;
}

// Remover aresta do grafo
void removerAresta(P_GRAFO g, int u, int v){
    g->adjacencia[u] = removerDaLista(g->adjacencia[u], v);
    g->adjacencia[v] = removerDaLista(g->adjacencia[v], u);
}

P_NO removerDaLista(P_NO lista, int v){
    P_NO proximo;
    if(lista == NULL){
        return NULL;
    }else if(lista->v == v){
        proximo = lista->prox;
        free(lista);
        return proximo;
    }else{
        lista->prox = removerDaLista(lista->prox, v);
        return lista;
    }
}

// Implementação da Busca em Profundidade
int * buscaEmProfundidade(P_GRAFO g, int s){
    int v;
    P_NO t;
    int *pai = (int*) malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_PILHA p = criarPilha();

    for(v=0; v < g->num; v++){
        pai[v] = -1;
        visitado[v] = 0;
    }

    empilhar(p, s);
    pai[s] = s;

    while(!pilhaVazia(p)){
        v = desempilar(p);
        visitado[v] = 1;

        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            if(!visitado[t->v]){
                pai[t->v] = v;
                empilhar(p, t->v);
            }
        }
    }

    destroiPilha(p);
    free(visitado);

    return pai;
}

// Implementação da Busca em Largura
int * buscaEmLargura(P_GRAFO g, int s){
    int v;
    P_NO t;
    int *pai = (int*) malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_FILA f = criarFila();

    for(v=0; v < g->num; v++){
        pai[v] = -1;
        visitado[v] = 0;
    }

    enfileira(f, s);
    pai[s] = s;
    visitado[s] = 1;

    while(!filaVazia(f)){
        v = desenfileira(f);
        
        for(t = g->adjacencia[v]; t != NULL; t = t->prox){
            if(!visitado[t->v]){
                visitado[t->v] = 1;
                pai[t->v] = v;
                enfileira(f, t->v);
            }
        }
    }

    destroiFila(f);
    free(visitado);

    return pai;
}

// Implementação de Dijkstra

// Implementação da árvore geradora mínima
int * arvoreGeradoraMinimaPrim(P_GRAFO g, int raiz) {
    int *pai = (int*) malloc(g->num * sizeof(int));
    int *custo = (int*) malloc(g->num * sizeof(int));
    int *visitado = (int*) calloc(g->num, sizeof(int));

    // Inicialização
    for (int i = 0; i < g->num; i++) {
        custo[i] = INT_MAX;
        pai[i] = -1;
    }
    custo[raiz] = 0;
    pai[raiz] = raiz;

    for (int i = 0; i < g->num; i++) {
        // Escolher o vértice não visitado de menor custo
        int u = -1;
        for (int v = 0; v < g->num; v++) {
            if (!visitado[v] && (u == -1 || custo[v] < custo[u])) {
                u = v;
            }
        }

        if (custo[u] == INT_MAX) {
            break; // Grafo desconectado
        }

        visitado[u] = 1;

        // Atualizar os custos dos vizinhos
        for (P_NO t = g->adjacencia[u]; t != NULL; t = t->prox) {
            if (!visitado[t->v] && t->peso < custo[t->v]) {
                custo[t->v] = t->peso;
                pai[t->v] = u;
            }
        }
    }

    free(custo);
    free(visitado);

    return pai;
}

void exibirResultadoBusca(int *resultado, int numVertices) {
    printf("Resultado:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Vértice %d: Pai = %d\n", i, resultado[i]);
    }
}
