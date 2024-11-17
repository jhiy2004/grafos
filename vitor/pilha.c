#include <stdlib.h>
#include "pilha.h"

// Função para criar a pilha
P_PILHA criarPilha() {
    P_PILHA p = (P_PILHA) malloc(sizeof(PILHA));

    p->capacidade = 100; // Define um tamanho inicial para a pilha
    p->itens = (int *) malloc(p->capacidade * sizeof(int));
    p->topo = -1; // Pilha vazia
    //
    return p;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(P_PILHA p) {
    return p->topo == -1;
}

// Função para empilhar um elemento
void empilhar(P_PILHA p, int item) {
    if (p->topo == p->capacidade - 1) { // Se a pilha está cheia
        p->capacidade *= 2; // Dobra o tamanho da pilha
        p->itens = (int *) realloc(p->itens, p->capacidade * sizeof(int));
    }
    p->itens[++p->topo] = item; // Adiciona o item e atualiza o topo
}

// Função para desempilhar um elemento
int desempilar(P_PILHA p) {
    return p->itens[p->topo--];
}

// Função para destruir a pilha
void destroiPilha(P_PILHA p) {
    free(p->itens);
    free(p);
}
