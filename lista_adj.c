#include <stdlib.h>
#include <limits.h>
#include "lista_adj.h"
#include "fila.h"
#include "pilha.h"
#include "heap_bin.h"

// Criação do grafo
P_GRAFO criarGrafoLA(int num){
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
void liberarGrafoLA(P_GRAFO g){
    int i;
    for(i=0; i < g->num; i++){
        liberarListaLA(g->adjacencia[i]);
    }
    free(g->adjacencia);
    free(g);
}

// Liberar as listas do grafo
void liberarListaLA(P_NO lista){
    while(lista != NULL){
        liberarListaLA(lista->prox);
        free(lista);
    }
}

// Adicionar aresta ao grafo
void inserirArestaLA(P_GRAFO g, int u, int v, int peso){
    g->adjacencia[v] = inserirNaListaLA(g->adjacencia[v], u, peso);
    g->adjacencia[u] = inserirNaListaLA(g->adjacencia[u], v, peso);
}

P_NO inserirNaListaLA(P_NO lista, int v, int peso){
    P_NO novo = (P_NO) malloc(sizeof(NO));
    novo->v = v;
    novo->peso = peso;
    novo->prox = lista;
    return novo;
}

// Remover aresta do grafo
void removerArestaLA(P_GRAFO g, int u, int v){
    g->adjacencia[u] = removerDaListaLA(g->adjacencia[u], v);
    g->adjacencia[v] = removerDaListaLA(g->adjacencia[v], u);
}

P_NO removerDaListaLA(P_NO lista, int v){
    P_NO proximo;
    if(lista == NULL){
        return NULL;
    }else if(lista->v == v){
        proximo = lista->prox;
        free(lista);
        return proximo;
    }else{
        lista->prox = removerDaListaLA(lista->prox, v);
        return lista;
    }
}

// Implementação da Busca em Profundidade
BUSCA buscaEmProfundidadeLA(P_GRAFO g, int s){
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
BUSCA buscaEmLarguraLA(P_GRAFO g, int s){
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
