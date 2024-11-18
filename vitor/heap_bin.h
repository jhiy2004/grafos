#ifndef HEAP_BIN_H
#define HEAP_BIN_H

typedef struct {
	int prioridade;
	int vertice;
} Item;

typedef struct {
	Item *v;
	int *indice;
	int n, tamanho;
} FP;


FP* criarFprio(int n);

int paiFP(int i);
int leftFP(int i);
int rightFP(int i);

int vaziaFP(FP* fp);
int prioridadeFP(FP* fp, int v);

void insereFP(FP* fp, int v, int prioridade);

void diminuiprioridade(FP* fp, int v, int prioridade);

void minHeapify(FP* fp, int i);

int extraiMinimoFP(FP* fp);
void imprimirHeap(FP* fp);

#include "heap_bin.c"

#endif
