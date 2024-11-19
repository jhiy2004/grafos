#ifndef FILA_H
#define FILA_H

typedef struct NO_FILA {
    int valor;
    struct NO_FILA *prox;
} NO_FILA;

typedef NO_FILA *P_NO_FILA;

typedef struct FILA {
    NO_FILA *inicio;
    NO_FILA *fim;
} FILA;

typedef FILA *P_FILA;

P_FILA criarFila();

int filaVazia(P_FILA f);

void enfileira(P_FILA f, int valor);

int desenfileira(P_FILA f);

void destroiFila(P_FILA f);

#endif

