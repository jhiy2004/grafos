#ifndef MATRIZ_ADJ_H
#define MATRIZ_ADJ_H

#include "fila.h"
#include "heap_bin.h"

typedef struct Grafo {
	int **adj;
	int n;
} Grafo;

Grafo* criarGrafo(int n);
void destruirGrafo(Grafo *g);

void inserirAresta(Grafo *g, int u, int v);
void inserirArestaPeso(Grafo *g, int u, int v, int peso);

void removerAresta(Grafo *g, int u, int v);

int possuiAresta(Grafo *g, int u, int v);

void imprimirArestas(Grafo *g);

void buscaProfundidade(Grafo *g, int *pai, int p, int v);
int* encontraCaminhos(Grafo *g, int s);

int* buscaLargura(Grafo *g, int s);

int* dijkstra(Grafo* g, int s);

#include "matriz_adj.c"

#endif
