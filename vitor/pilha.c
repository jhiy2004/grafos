#include <stdlib.h>
#include "pilha.h"

// Função para criar a pilha
P_PILHA criarPilha() {
    P_PILHA p = (P_PILHA) malloc(sizeof(PILHA));
    p->topo = NULL; // Pilha vazia

    return p;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(P_PILHA p) {
    return p->topo == NULL;
}

// Função para empilhar um elemento
void empilhar(P_PILHA p, int valor) {
    P_NO_PILHA novo = (P_NO_PILHA) malloc(sizeof(NO_PILHA));
    novo->valor = valor;
    novo->prox = p->topo; // O próximo do novo nó é o topo atual
    p->topo = novo; // Atualiza o topo para o novo nó
}

// Função para desempilhar um elemento
int desempilar(P_PILHA p) {
    P_NO_PILHA temp = p->topo; // Guarda o nó do topo
    int valor = temp->valor;    // Guarda o valor que será retornado
    p->topo = temp->prox;       // Atualiza o topo da pilha
    free(temp);                 // Libera a memória do nó desempilhado
    return valor;
}

// Função para destruir a pilha
void destroiPilha(P_PILHA p) {
    while (!pilhaVazia(p)) {
        desempilar(p); // Desempilha todos os elementos
    }
    free(p); // Libera a memória da pilha
}

