#include <stdlib.h>
#include "pilha.h"

P_PILHA criarPilha() {
    P_PILHA p = (P_PILHA) malloc(sizeof(PILHA));
    p->topo = NULL;

    return p;
}

int pilhaVazia(P_PILHA p) {
    return p->topo == NULL;
}

void empilhar(P_PILHA p, int valor) {
    P_NO_PILHA novo = (P_NO_PILHA) malloc(sizeof(NO_PILHA));
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

int desempilar(P_PILHA p) {
    P_NO_PILHA temp = p->topo;
    int valor = temp->valor;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

void destroiPilha(P_PILHA p) {
    while (!pilhaVazia(p)) {
        desempilar(p);
    }
    free(p);
}

