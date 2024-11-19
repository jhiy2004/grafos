/**
 * @file matriz_adj.h
 * @brief Definição de estruturas e funções para manipulação de grafos representados por matrizes de adjacência.
 *
 * Este arquivo contém a definição das estruturas de dados e as funções necessárias
 * para criar, manipular e liberar grafos representados por matrizes de adjacência. 
 * Também inclui algoritmos de busca e cálculo de menor caminho.
 */

#ifndef MATRIZ_ADJ_H
#define MATRIZ_ADJ_H

#include "../auxiliares/auxiliares.h"

/**
 * @brief Estrutura de um grafo representado por uma matriz de adjacência.
 *
 * A matriz de adjacência é uma matriz quadrada, onde o elemento adj[i][j]
 * representa a presença (ou ausência) de uma aresta entre os vértices i e j.
 * Em grafos ponderados, o valor armazenado em adj[i][j] é o peso da aresta.
 * Caso o grafo não possua aresta entre os vértices i e j, o valor armazenado
 * em adj[i][j] pode ser 0 ou um valor indicativo da ausência de aresta.
 */
typedef struct Grafo {
    int **adj;   /**< Matriz de adjacência que armazena os pesos das arestas entre os vértices. */
    int n;       /**< Número de vértices no grafo. */
} Grafo;

/**
 * @brief Cria um grafo representado por uma matriz de adjacência.
 *
 * Esta função aloca memória para um grafo com um número específico de vértices
 * e inicializa a matriz de adjacência com valores padrão (geralmente 0 ou algum valor de inexistência de aresta).
 *
 * @param n O número de vértices do grafo.
 * 
 * @return Ponteiro para o grafo criado.
 */
Grafo* criarGrafoMA(int n);

/**
 * @brief Libera a memória alocada para um grafo.
 *
 * Esta função desaloca a memória utilizada pela matriz de adjacência e pela estrutura
 * do grafo, liberando todos os recursos alocados.
 *
 * @param g Ponteiro para o grafo a ser destruído.
 */
void destruirGrafoMA(Grafo *g);

/**
 * @brief Insere uma aresta entre dois vértices no grafo, com peso 1.
 *
 * Esta função insere uma aresta entre os vértices u e v. Em grafos não direcionados,
 * a aresta é inserida nas duas direções (u -> v e v -> u).
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 */
void inserirArestaMA(Grafo *g, int u, int v);

/**
 * @brief Insere uma aresta ponderada entre dois vértices no grafo.
 *
 * Esta função insere uma aresta entre os vértices u e v com um peso específico.
 * Em grafos não direcionados, a aresta é inserida nas duas direções (u -> v e v -> u).
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 * @param peso O peso da aresta.
 */
void inserirArestaPesoMA(Grafo *g, int u, int v, int peso);

/**
 * @brief Remove uma aresta entre dois vértices no grafo.
 *
 * Esta função remove a aresta entre os vértices u e v. Em grafos não direcionados,
 * a aresta é removida nas duas direções (u -> v e v -> u).
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 */
void removerArestaMA(Grafo *g, int u, int v);

/**
 * @brief Verifica se uma aresta existe entre dois vértices no grafo.
 *
 * Esta função verifica se há uma aresta entre os vértices u e v.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem da aresta.
 * @param v Vértice de destino da aresta.
 * 
 * @return Retorna 1 se a aresta existir, e 0 caso contrário.
 */
int possuiArestaMA(Grafo *g, int u, int v);

/**
 * @brief Realiza uma busca em profundidade (DFS) no grafo a partir de um vértice.
 *
 * A busca em profundidade explora os vértices mais profundos primeiro,
 * utilizando uma pilha para gerenciar os vértices a serem visitados.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice de origem da busca.
 * 
 * @return Retorna uma estrutura de busca contendo os resultados da exploração.
 */
BUSCA buscaProfundidadeMA(Grafo *g, int s);

/**
 * @brief Realiza uma busca em largura (BFS) no grafo a partir de um vértice.
 *
 * A busca em largura explora os vértices mais próximos primeiro,
 * utilizando uma fila para gerenciar os vértices a serem visitados.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice de origem da busca.
 * 
 * @return Retorna uma estrutura de busca contendo os resultados da exploração.
 */
BUSCA buscaLarguraMA(Grafo *g, int s);

/**
 * @brief Calcula o menor caminho de um vértice para todos os outros vértices utilizando o algoritmo de Dijkstra.
 *
 * O algoritmo de Dijkstra encontra o caminho de custo mínimo a partir de um vértice de origem
 * até todos os outros vértices do grafo, considerando arestas ponderadas.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice de origem do cálculo.
 * 
 * @return Retorna uma estrutura de busca contendo os resultados do algoritmo de Dijkstra.
 */
BUSCA dijkstraMA(Grafo* g, int s);

/**
 * @brief Calcula a árvore geradora mínima de um grafo a partir de um vértice utilizando o algoritmo de Prim.
 *
 * O algoritmo de Prim encontra a árvore geradora mínima de um grafo ponderado, ou seja, um subconjunto
 * de arestas que conecta todos os vértices do grafo com o menor custo possível.
 *
 * @param g Ponteiro para o grafo.
 * @param s Vértice de origem da árvore geradora mínima.
 * 
 * @return Retorna uma estrutura de busca contendo os resultados do algoritmo de Prim.
 */
BUSCA geradoraMinimaMA(Grafo* g, int s);

#endif
