#include <limits.h>
#include <stdlib.h>
#include "../auxiliares/fila.h"
#include "../auxiliares/pilha.h"
#include "../auxiliares/heap_bin.h"
#include "matriz_adj.h"

Grafo* criarGrafoMA(int n){
	int i = 0;
	int j = 0;

	Grafo* g = malloc(sizeof(Grafo));

	g->n = n;
	g->adj = malloc(n * sizeof(int*));
	for(i = 0; i < n; i++)
		g->adj[i] = malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			g->adj[i][j] = 0;
		}
	}
	return g;
}

void destruirGrafoMA(Grafo* g){
	int i = 0;
	for(i = 0; i < g->n; i++){
		free(g->adj[i]);
	}
	free(g->adj);
	free(g);
}

void inserirArestaMA(Grafo* g, int u, int v){
	g->adj[u][v] = 1;
	g->adj[v][u] = 1;
}

void inserirArestaPesoMA(Grafo* g, int u, int v, int peso){
	g->adj[u][v] = peso;
	g->adj[v][u] = peso;
}

void removerArestaMA(Grafo* g, int u, int v){
	g->adj[u][v] = 0;
	g->adj[v][u] = 0;
}

int possuiArestaMA(Grafo* g, int u, int v){
	return g->adj[u][v];
}

BUSCA buscaProfundidadeMA(Grafo *g, int s){
    int v;
    BUSCA resultado;
    resultado.pai = (int *)malloc(g->n * sizeof(int));
    resultado.custo = (int *)malloc(g->n * sizeof(int));
    int *visitado = (int*) malloc(g->n * sizeof(int));

    P_PILHA p = criarPilha();

    for(v=0; v < g->n; v++){
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

        for(int i=0; i < g->n; i++){
			if (g->adj[v][i] != 0){
				if(!visitado[i]){
					resultado.pai[i] = v;
					resultado.custo[i] = resultado.custo[v] + g->adj[v][i];
					empilhar(p, i);
				}
			}
        }
    }

    destroiPilha(p);
    free(visitado);

    return resultado;
}

BUSCA buscaLarguraMA(Grafo *g, int s){
	int w = 0;
	int v = 0;
	BUSCA resultado;
	resultado.pai = (int*)malloc(g->n * sizeof(int));
	resultado.custo = (int*)malloc(g->n * sizeof(int));
	int *visitado = (int*)malloc(g->n * sizeof(int));

	P_FILA f = criarFila();
	for(v = 0; v < g->n; v++){
        resultado.custo[v] = 0;
		resultado.pai[v] = -1;
		visitado[v] = 0;
	}
	enfileira(f, s);
	resultado.pai[s] = s;
    resultado.custo[s] = s;
	visitado[s] = 1;
	while(!filaVazia(f)){
		v = desenfileira(f);
		for(w = 0; w < g->n; w++){
			if(g->adj[v][w] && !visitado[w]) {
				visitado[w] = 1;
				resultado.pai[w] = v;
                resultado.custo[w] = resultado.custo[v] + g->adj[v][w];
				enfileira(f, w);
			}
		}
	}
	destroiFila(f);
	free(visitado);
	return resultado;
}

BUSCA dijkstraMA(Grafo* g, int s) {
	int v;
    BUSCA resultado;
    resultado.pai = (int*) malloc(g->n * sizeof(int));
    resultado.custo = (int*) malloc(g->n * sizeof(int));
	FP* h = criarFprio(g->n);
	for (v = 0; v < g->n; v++) {
		resultado.pai[v] = -1;
        resultado.custo[v] = INT_MAX;
		insereFP(h, v, INT_MAX);
	}
	resultado.pai[s] = s;
    resultado.custo[s] = 0;
	diminuiprioridade(h, s, 0);

	while (!vaziaFP(h)) {
		v = extraiMinimoFP(h);
        int custoAtual = resultado.custo[v];

		if (prioridadeFP(h, v) != INT_MAX)
			for (int i = 0; i < g->n; i++){
                int novoCusto = custoAtual + g->adj[v][i];
				if (g->adj[v][i] != 0){
					if (prioridadeFP(h, v)+g->adj[v][i] < prioridadeFP(h, i)) {
                        resultado.custo[i] = novoCusto;
						diminuiprioridade(h, i, prioridadeFP(h,v)+g->adj[v][i]);
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
