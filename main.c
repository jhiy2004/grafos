#include <stdio.h>
#include <stdlib.h>
#include "lista_adj.h"
#include "matriz_adj.h"
#include "auxiliares.h"

int main() {
    int opcao, numVertices, origem, destino, peso, inicio;
    P_GRAFO grafo;

    menuTipoGrafo();
    scanf("%d", &opcao);

    switch(opcao){
        case 1: {
            // Grafo com listas de adjacencia
            // Criar o grafo
            printf("Número de vértices: ");
            scanf("%d", &numVertices);
            grafo = criarGrafoLA(numVertices);

            // Adicionar arestas
            printf("Adicione as arestas no formato: origem destino peso (digite -1 para encerrar):\n");
            while (1) {
                scanf("%d", &origem);
                if (origem == -1) break;
                scanf("%d %d", &destino, &peso);
                inserirArestaLA(grafo, origem, destino, peso);
            }

            // Menu de operações
            do{
                menu();
                scanf("%d", &opcao);

                switch(opcao) {
                    case 1: {
                        // Busca em Largura
                        printf("Vértice inicial: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = buscaEmLarguraLA(grafo, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 2: {
                        // Busca em Profundidade
                        printf("Vértice inicial: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = buscaEmProfundidadeLA(grafo, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 3: {
                        // Árvore Geradora Mínima (Prim)
                        printf("Vértice raiz: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = arvoreGeradoraMinimaPrimLA(grafo, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 4:
                        // Dijkstra
                        printf("Vértice inicial: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = dijkstraLA(grafo, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    case 0:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                getchar();
                system("clear");
            } while (opcao != 0);

            liberarGrafoLA(grafo);
            break;
        }
        case 2: {
            // Grafo com matriz de adjacencia
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}
