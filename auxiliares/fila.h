#ifndef FILA_H
#define FILA_H

// Definição da estrutura da fila
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

// Funções da fila
P_FILA criarFila();            // Cria uma nova fila e retorna um ponteiro para ela
int filaVazia(P_FILA f);       // Verifica se a fila está vazia
void enfileira(P_FILA f, int valor); // Adiciona um elemento ao final da fila
int desenfileira(P_FILA f);    // Remove e retorna o elemento no início da fila
void destroiFila(P_FILA f);    // Libera toda a memória associada à fila

#endif

