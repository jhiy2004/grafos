#include <stdlib.h>
#include "fila.h"

P_FILA criarFila() {
    P_FILA f = (P_FILA) malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int filaVazia(P_FILA f) {
    return f->inicio == NULL;
}

void enfileira(P_FILA f, int valor) {
    P_NO_FILA novo = (P_NO_FILA) malloc(sizeof(NO_FILA));

    novo->valor = valor;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

int desenfileira(P_FILA f) {
    P_NO_FILA temp = f->inicio;
    int valor = temp->valor;

    f->inicio = temp->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return valor;
}

void destroiFila(P_FILA f) {
    while (!filaVazia(f)) {
        desenfileira(f);
    }
    free(f);
}
