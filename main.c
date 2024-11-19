#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos/lista_adj.h"
#include "grafos/matriz_adj.h"
#include "auxiliares/auxiliares.h"

int main(int argc, char* argv[]) {
    int opcao, numVertices, origem, destino, peso, inicio;
    P_GRAFO grafo;
    Grafo *g;

    //Se houver argumentos verifica se é um caso de teste
    if(argc > 1){
        if(strcmp(argv[1], "teste_matriz") == 0){
            //teste 1
            g = criarGrafoMA(5);
            inserirArestaMA(g, 0, 1);
            inserirArestaMA(g, 1, 2);
            inserirArestaMA(g, 2, 3);
            inserirArestaMA(g, 3, 4);
            inserirArestaMA(g, 4, 0);

            printf("\nGrafo com matriz de adjacência e 5 vértices\n");
            printf("Arestas do grafo: 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Busca em largura a partir do vértice 0:\n\n");
            BUSCA resultado = buscaLarguraMA(g, 0);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com matriz de adjacência e 5 vértices\n");
            printf("Arestas do grafo: 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Busca em profundidade a partir do vértice 0:\n\n");
            resultado = buscaProfundidadeMA(g, 0);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com matriz de adjacência e 5 vértices\n");
            printf("Arestas do grafo: 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Árvore geradora mínima a partir do vértice 0:\n\n");
            resultado = geradoraMinimaMA(g, 0);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com matriz de adjacência e 5 vértices\n");
            printf("Arestas do grafo: 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Dijkstra a partir do vértice 0:\n\n");
            resultado = dijkstraMA(g, 0);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            return 0;
        }
        if(strcmp(argv[1], "teste_lista") == 0){
            //teste 2
            grafo = criarGrafoLA(5);
            inserirArestaLA(grafo, 0, 1, 1);
            inserirArestaLA(grafo, 1, 2, 1);
            inserirArestaLA(grafo, 2, 3, 1);
            inserirArestaLA(grafo, 3, 4, 1);
            inserirArestaLA(grafo, 4, 0, 1);

            printf("\nGrafo com lista de adjacência e 5 vértices\n");
            printf("Arestas do grafo (todas com peso 1) : 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Busca em largura a partir do vértice 2:\n\n");
            BUSCA resultado = buscaEmLarguraLA(grafo, 2);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com lista de adjacência e 5 vértices\n");
            printf("Arestas do grafo (todas com peso 1) : 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Busca em profundidade a partir do vértice 2:\n\n");
            resultado = buscaEmProfundidadeLA(grafo, 2);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com lista de adjacência e 5 vértices\n");
            printf("Arestas do grafo (todas com peso 1) : 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Árvore geradora mínima a partir do vértice 2:\n\n");
            resultado = arvoreGeradoraMinimaPrimLA(grafo, 2);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            printf("\nGrafo com lista de adjacência e 5 vértices\n");
            printf("Arestas do grafo (todas com peso 1) : 0-1; 1-2; 2-3; 3-4; 4-0\n");
            printf("Dijkstra a partir do vértice 2:\n\n");
            resultado = dijkstraLA(grafo, 2);
            exibirResultadoBusca(resultado, 5);
            printf("\nPressione Enter para continuar...");
            getchar();
            system("clear");

            return 0;
        }
    }

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
            // Grafo com listas de adjacencia
            // Criar o grafo
            printf("Número de vértices: ");
            scanf("%d", &numVertices);
            g = criarGrafoMA(numVertices);

            // Adicionar arestas
            printf("Adicione as arestas no formato: origem destino peso (digite -1 para encerrar):\n");
            while (1) {
                scanf("%d", &origem);
                if (origem == -1) break;
                scanf("%d %d", &destino, &peso);
                inserirArestaPesoMA(g, origem, destino, peso);
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
                        BUSCA resultado = buscaLarguraMA(g, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 2: {
                        // Busca em Profundidade
                        printf("Vértice inicial: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = buscaProfundidadeMA(g, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 3: {
                        // Árvore Geradora Mínima (Prim)
                        printf("Vértice raiz: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = geradoraMinimaMA(g, inicio);
                        exibirResultadoBusca(resultado, numVertices);
                        free(resultado.pai);
                        free(resultado.custo);
                        break;
                    }
                    case 4:
                        // Dijkstra
                        printf("Vértice inicial: ");
                        scanf("%d", &inicio);
                        BUSCA resultado = dijkstraMA(g, inicio);
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

            destruirGrafoMA(g);
            break;
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
