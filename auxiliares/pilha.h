#ifndef PILHA_H
#define PILHA_H

typedef struct NO_PILHA {
    int valor;
    struct NO_PILHA *prox;
} NO_PILHA;

typedef NO_PILHA * P_NO_PILHA;

typedef struct PILHA {
    P_NO_PILHA topo;
} PILHA;

typedef PILHA * P_PILHA;

P_PILHA criarPilha();

int pilhaVazia(P_PILHA p);

void empilhar(P_PILHA p, int valor);

int desempilar(P_PILHA p);

void destroiPilha(P_PILHA p);

#endif

