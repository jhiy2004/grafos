#include <stdio.h>
#include <limits.h>
#include "auxiliares.h"

void exibirResultadoBusca(BUSCA resultado, int numVertices){
    printf("\nResultado:\n\n");
    for(int i = 0; i < numVertices; i++){
        if(resultado.custo[i] == INT_MAX){
            printf("Vértice %d: Pai = %d, Custo = Infinito\n", i, resultado.pai[i]);
        }else{
            printf("Vértice %d: Pai = %d, Custo = %d\n", i, resultado.pai[i], resultado.custo[i]);
        }
    }
}

void menuTipoGrafo(){
    printf("\n--------- MENU ---------\n");
    printf("1. Grafo com Listas de Adjacência\n");
    printf("2. Grafo com Matriz de Adjacência\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void menu(){
    printf("\n--------- MENU ---------\n");
    printf("1. Busca em Largura\n");
    printf("2. Busca em Profundidade\n");
    printf("3. Árvore Geradora Mínima (Prim)\n");
    printf("4. Dijkstra\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}
