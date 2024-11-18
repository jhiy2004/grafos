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
BUSCA buscaEmProfundidade(P_GRAFO g, int s){
    int v;
    P_NO t;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->num * sizeof(int));
    resultado.custo = (int *)malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_PILHA p = criarPilha();

    for(v=0; v < g->num; v++){
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    empilhar(p, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;

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

    destroiPilha(p);
    free(visitado);

    return resultado;
}

// Implementação da Busca em Largura
BUSCA buscaEmLargura(P_GRAFO g, int s){
    int v;
    P_NO t;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->num * sizeof(int));
    resultado.custo = (int *)malloc(g->num * sizeof(int));
    int *visitado = (int*) malloc(g->num * sizeof(int));

    P_FILA f = criarFila();

    for(v=0; v < g->num; v++){
        resultado.pai[v] = -1;
        resultado.custo[v] = 0;
        visitado[v] = 0;
    }

    enfileira(f, s);
    resultado.pai[s] = s;
    resultado.custo[s] = 0;
    visitado[s] = 1;

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

    destroiFila(f);
    free(visitado);

    return resultado;
}

// Implementação de Dijkstra

// Implementação da árvore geradora mínima
BUSCA arvoreGeradoraMinimaPrim(P_GRAFO g, int raiz) {
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->num * sizeof(int));
    resultado.custo = (int*) malloc(g->num * sizeof(int));
    int *visitado = (int*) calloc(g->num, sizeof(int));

    // Inicialização
    for (int i = 0; i < g->num; i++) {
        resultado.custo[i] = INT_MAX;
        resultado.pai[i] = -1;
    }
    resultado.custo[raiz] = 0;
    resultado.pai[raiz] = raiz;

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

void exibirResultadoBusca(BUSCA resultado, int numVertices) {
    printf("Resultado:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Vértice %d: Pai = %d, Custo = %d\n", i, resultado.pai[i], resultado.custo[i]);
    }
}

void menu() {
    printf("\n--------- MENU ---------\n");
    printf("1. Busca em Largura\n");
    printf("2. Busca em Profundidade\n");
    printf("3. Árvore Geradora Mínima (Prim)\n");
    printf("4. Dijkstra\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}
