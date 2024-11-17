#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "grafo.h"

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
void inserirAresta(P_GRAFO g, int u, int v){
    g->adjacencia[v] = inserirNaLista(g->adjacencia[v], u);
    g->adjacencia[u] = inserirNaLista(g->adjacencia[u], v);
}

P_NO inserirNaLista(P_NO lista, int v){
    P_NO novo = (P_NO) malloc(sizeof(NO));
    novo->v = v;
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
int * encontraComponentes(P_GRAFO g){
    int s, c = 0, *componentes = (int*) malloc(g->num * sizeof(int));

    for(s=0; s < g->num; s++){
        componentes[s] = -1;
    }for(s=0; s < g->num; s++){
        if(componentes[s] == -1){
            visitaRec(g, componentes, c, s);
            c++;
        }
    }

    return componentes;
}

void visitaRec(P_GRAFO g, int *componentes, int comp, int v){
    P_NO t;

    componentes[v] = comp;
    for(t=g->adjacencia[v]; t != NULL; t = t->prox){
        if(componentes[t->v] == -1){
            visitaRec(g, componentes, comp, t->v);
        }
    }
}

// Implementação da Busca em Largura
void buscaLargura(P_GRAFO g, int *componentes, int comp, int inicio){
    int *fila = (int*) malloc(g->num * sizeof(int));
    int frente = 0, tras = 0;

    // Enfileira o vértice inicial
    fila[tras++] = inicio;
    componentes[inicio] = comp;

    while (frente < tras) {
        int v = fila[frente++]; // Desenfileira o próximo vértice
        P_NO t = g->adjacencia[v];

        while (t != NULL) {
            if (componentes[t->v] == -1) { // Vértice ainda não visitado
                componentes[t->v] = comp;
                fila[tras++] = t->v; // Enfileira o vértice
            }
            t = t->prox;
        }
    }

    free(fila);
}

int *encontraComponentesBFS(P_GRAFO g) {
    int s, c = 0;
    int *componentes = (int *) malloc(g->num * sizeof(int));

    for (s = 0; s < g->num; s++) {
        componentes[s] = -1; // Inicializa como não visitado
    }

    for (s = 0; s < g->num; s++) {
        if (componentes[s] == -1) { // Novo componente encontrado
            buscaLargura(g, componentes, c, s);
            c++;
        }
    }

    return componentes;
}

// Implementação de Dijkstra
