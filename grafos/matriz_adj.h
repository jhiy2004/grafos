#ifndef MATRIZ_ADJ_H
#define MATRIZ_ADJ_H

#include "../auxiliares/auxiliares.h"

typedef struct Grafo {
	int **adj;
	int n;
} Grafo;

Grafo* criarGrafoMA(int n);
void destruirGrafoMA(Grafo *g);

void inserirArestaMA(Grafo *g, int u, int v);
void inserirArestaPesoMA(Grafo *g, int u, int v, int peso);

void removerArestaMA(Grafo *g, int u, int v);

int possuiArestaMA(Grafo *g, int u, int v);

BUSCA buscaProfundidadeMA(Grafo *g, int s);

BUSCA buscaLarguraMA(Grafo *g, int s);

BUSCA dijkstraMA(Grafo* g, int s);

BUSCA geradoraMinimaMA(Grafo* g, int s);

#endif
