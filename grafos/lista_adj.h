/**
 * @file lista_adj.h
 * @brief Definição de estruturas e funções para manipulação de grafos representados por listas de adjacência.
 *
 * Este arquivo contém a definição das estruturas de dados e as funções necessárias
 * para criar, manipular e liberar grafos representados por listas de adjacência. 
 * Também inclui algoritmos de busca e cálculo de menor caminho.
 */

#ifndef LISTA_ADJ_H
#define LISTA_ADJ_H

#include "../auxiliares/auxiliares.h"

/**
 * @brief Estrutura de um nó na lista de adjacência.
 *
 * Cada nó representa uma aresta no grafo, contendo o vértice de destino,
 * o peso da aresta e um ponteiro para o próximo nó.
 */
typedef struct NO {
    int v;             /**< Vértice de destino. */
    int peso;          /**< Peso da aresta. */
    struct NO *prox;   /**< Ponteiro para o próximo nó. */
} NO;

typedef NO * P_NO; /**< Ponteiro para um nó na lista de adjacência. */

/**
 * @brief Estrutura para representar um grafo.
 *
 * O grafo é representado por um array de listas de adjacência, onde cada entrada
 * do array corresponde a um vértice do grafo e aponta para uma lista encadeada de nós.
 */
typedef struct GRAFO {
    P_NO *adjacencia; /**< Array de listas de adjacência. */
    int num;          /**< Número de vértices no grafo. */
} GRAFO;

typedef GRAFO * P_GRAFO; /**< Ponteiro para uma estrutura de grafo. */

/**
 * @brief Cria um grafo utilizando listas de adjacência.
 *
 * @param num Número de vértices do grafo.
 * @return Ponteiro para o grafo criado.
 */
P_GRAFO criarGrafoLA(int num);

/**
 * @brief Libera a memória alocada para o grafo.
 *
 * @param g Ponteiro para o grafo a ser liberado.
 */
void liberarGrafoLA(P_GRAFO g);

/**
 * @brief Libera a memória alocada para uma lista de adjacência.
 *
 * @param lista Ponteiro para a lista de adjacência a ser liberada.
 */
void liberarListaLA(P_NO lista);

/**
 * @brief Remove uma aresta do grafo.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 */
void removerArestaLA(P_GRAFO g, int u, int v);

/**
 * @brief Remove um nó da lista de adjacência.
 *
 * @param lista Ponteiro para a lista de adjacência.
 * @param v Vértice a ser removido.
 * @return Ponteiro para a lista atualizada.
 */
P_NO removerDaListaLA(P_NO lista, int v);

/**
 * @brief Insere uma aresta no grafo.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 * @param peso Peso da aresta.
 */
void inserirArestaLA(P_GRAFO g, int u, int v, int peso);

/**
 * @brief Insere um nó em uma lista de adjacência.
 *
 * @param lista Ponteiro para a lista de adjacência.
 * @param v Vértice de destino.
 * @param peso Peso da aresta.
 * @return Ponteiro para a lista atualizada.
 */
P_NO inserirNaListaLA(P_NO lista, int v, int peso);

/**
 * @brief Executa a busca em largura no grafo.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice inicial para a busca.
 * @return Resultado da busca em largura.
 */
BUSCA buscaEmLarguraLA(P_GRAFO g, int s);

/**
 * @brief Executa a busca em profundidade no grafo.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice inicial para a busca.
 * @return Resultado da busca em profundidade.
 */
BUSCA buscaEmProfundidadeLA(P_GRAFO g, int s);

/**
 * @brief Executa o algoritmo de Dijkstra no grafo.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice inicial para o cálculo do menor caminho.
 * @return Resultado do algoritmo de Dijkstra.
 */
BUSCA dijkstraLA(P_GRAFO g, int s);

/**
 * @brief Calcula a árvore geradora mínima usando o algoritmo de Prim.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice inicial.
 * @return Resultado do algoritmo de Prim.
 */
BUSCA arvoreGeradoraMinimaPrimLA(P_GRAFO g, int s);

#endif

