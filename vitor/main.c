#include <stdio.h>
#include "grafo.h"

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Busca em Largura\n");
    printf("2. Busca em Profundidade\n");
    printf("3. Dijkstra\n");
    printf("4. Árvore Geradora Mínima\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    int opcao, numVertices, origem, destino, peso, inicio;
    Grafo *grafo;

    printf("Número de vértices: ");
    scanf("%d", &numVertices);
    grafo = criarGrafo(numVertices, false);

    printf("Adicione as arestas no formato: origem destino peso (digite -1 para encerrar):\n");
    while (1) {
        scanf("%d", &origem);
        if (origem == -1) break;
        scanf("%d %d", &destino, &peso);
        adicionarAresta(grafo, origem, destino, peso);
    }

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Vértice inicial: ");
                scanf("%d", &inicio);
                printf("Busca em Largura a partir do vértice %d:\n", inicio);
                buscaEmLargura(grafo, inicio);
                break;

            case 2:
                printf("Vértice inicial: ");
                scanf("%d", &inicio);
                printf("Busca em Profundidade a partir do vértice %d:\n", inicio);
                buscaEmProfundidade(grafo, inicio);
                break;

            case 3:
                printf("Vértice inicial: ");
                scanf("%d", &inicio);
                dijkstra(grafo, inicio);
                break;

            case 4:
                arvoreGeradoraMinima(grafo);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    liberarGrafo(grafo);
    return 0;
}
