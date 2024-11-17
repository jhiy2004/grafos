#ifndef PILHA_H
#define PILHA_H

typedef struct PILHA {
    int *itens;   // Vetor para armazenar os elementos da pilha
    int topo;     // Índice do topo da pilha
    int capacidade; // Tamanho máximo da pilha
} PILHA;

typedef PILHA * P_PILHA;

P_PILHA criarPilha();

int pilhaVazia(P_PILHA p);

void empilhar(P_PILHA p, int item);

int desempilar(P_PILHA p);

void destroiPilha(P_PILHA p);

#endif
