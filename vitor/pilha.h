#ifndef PILHA_H
#define PILHA_H

// Definição da estrutura do nó da pilha
typedef struct NO_PILHA {
    int valor;
    struct NO_PILHA *prox;
} NO_PILHA;

typedef NO_PILHA * P_NO_PILHA;

// Definição da estrutura da pilha
typedef struct PILHA {
    P_NO_PILHA topo; // Ponteiro para o topo da pilha
} PILHA;

typedef PILHA * P_PILHA;

// Funções da pilha
P_PILHA criarPilha();           // Cria uma nova pilha e retorna um ponteiro para ela
int pilhaVazia(P_PILHA p);      // Verifica se a pilha está vazia
void empilhar(P_PILHA p, int valor); // Empilha um novo valor na pilha
int desempilar(P_PILHA p);      // Desempilha e retorna o valor do topo da pilha
void destroiPilha(P_PILHA p);   // Libera toda a memória associada à pilha

#endif

