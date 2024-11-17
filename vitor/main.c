#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Busca em Largura\n");
    printf("2. Busca em Profundidade\n");
    printf("3. Árvore Geradora Mínima (Prim)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    int opcao, numVertices, origem, destino, peso, inicio;
    P_GRAFO grafo;

    // Criar o grafo
    printf("Número de vértices: ");
    scanf("%d", &numVertices);
    grafo = criarGrafo(numVertices);

    // Adicionar arestas
    printf("Adicione as arestas no formato: origem destino peso (digite -1 para encerrar):\n");
    while (1) {
        scanf("%d", &origem);
        if (origem == -1) break;
        scanf("%d %d", &destino, &peso);
        inserirAresta(grafo, origem, destino, peso);
    }

    // Menu de operações
    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Busca em Largura
                printf("Vértice inicial: ");
                scanf("%d", &inicio);
                int *resultado = buscaEmLargura(grafo, inicio);
                exibirResultadoBusca(resultado, numVertices);
                free(resultado);
                break;
            }
            case 2: { // Busca em Profundidade
                printf("Vértice inicial: ");
                scanf("%d", &inicio);
                int *resultado = buscaEmProfundidade(grafo, inicio);
                exibirResultadoBusca(resultado, numVertices);
                free(resultado);
                break;
            }
            case 3: { // Árvore Geradora Mínima (Prim)
                printf("Vértice raiz: ");
                scanf("%d", &inicio);
                int *resultado = arvoreGeradoraMinimaPrim(grafo, inicio);
                exibirResultadoBusca(resultado, numVertices);
                free(resultado);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberarGrafo(grafo);
    return 0;
}
