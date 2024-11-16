#ifndef FILA_H
#define FILA_H

typedef struct noFila{
	int valor;
	struct noFila* prox;
} noFila;

typedef struct Fila {
	noFila* inicio;
	noFila* fim;
} Fila;

Fila* criarFila();
void inserirFila(Fila* f, int valor);
int removerFila(Fila* f);
int estaVazia(Fila* f);
int destruirFila(Fila* f);

#include "fila.c"

#endif
