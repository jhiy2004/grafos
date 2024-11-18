#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "fila.h"
#include "matriz_adj.h"
#include "heap_bin.h"

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

void buscaProfundidadeMA(Grafo *g, int *pai, int p, int v){
	pai[v] = p;
	for(int i = 0; i < g->n; i++){
		if(g->adj[v][i] == 1 && pai[i] == -1){
			buscaProfundidadeMA(g, pai, v, i);
		}
	}
}

int* encontraCaminhosMA(Grafo *g, int s){
	int i = 0;
	int *pai = (int*) malloc(g->n * sizeof(int));
	for(i = 0; i < g->n; i++){
		pai[i] = -1;
	}
	buscaProfundidadeMA(g, pai, s, s);
	return pai;
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
	pai[s] = s;
	visitado[s] = 1;
	while(!filaVazia(f)){
		v = desenfileira(f);
		for(w = 0; w < g->n; w++){
			if(g->adj[v][w] && !visitado[w]) {
				visitado[w] = 1;
				pai[w] = v;
				enfileira(f, w);
			}
		}
	}
	destroiFila(f);
	free(visitado);
	return pai;
}

BUSCA dijkstraMA(Grafo* g, int s) {
	int v, *pai = malloc(g->n * sizeof(int));
	int t;
	FP* h = criarFprio(g->n);
	for (v = 0; v < g->n; v++) {
		pai[v] = -1;
		insereFP(h, v, INT_MAX);
	}
	pai[s] = s;
	diminuiprioridade(h, s, 0);

	while (!vaziaFP(h)) {
		v = extraiMinimoFP(h);
		if (prioridadeFP(h, v) != INT_MAX)
			for (int i = 0; i < g->n; i++){
				if (g->adj[v][i] != 0){
					if (prioridadeFP(h, v)+g->adj[v][i] < prioridadeFP(h, i)) {
						diminuiprioridade(h, i, prioridadeFP(h,v)+g->adj[v][i]);
						pai[i] = v;
					}
				}
			}
	}
	return pai;
}

BUSCA geradoraMinimaMA(Grafo* g, int s) {
	int v, *pai = malloc(g->n * sizeof(int));
	int t;
	int *visitado = (int*)malloc(g->n * sizeof(int));
	
	FP* h = criarFprio(g->n);
	for (v = 0; v < g->n; v++) {
		pai[v] = -1;
		insereFP(h, v, INT_MAX);
		visitado[v] = 0;
	}
	pai[s] = s;
	diminuiprioridade(h, s, 0);
	visitado[0] = 1;

	while (!vaziaFP(h)) {
		imprimirHeap(h);
		printf("\n");
		v = extraiMinimoFP(h);
		printf("V: %d\n", v);

		visitado[v] = 1;

		if (prioridadeFP(h, v) != INT_MAX)
			for (int i = 0; i < g->n; i++){
				if (g->adj[v][i] != 0 && !visitado[i]){
					if (g->adj[v][i] < prioridadeFP(h, i)) {
						diminuiprioridade(h, i, g->adj[v][i]);
						pai[i] = v;
					}
				}
			}
	}
	return pai;
}

