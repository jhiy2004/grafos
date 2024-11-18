#ifndef AUXILIARES_H
#define AUXILIARES_H

typedef struct busca {
    int *pai;
    int *custo;
} BUSCA;

void exibirResultadoBusca(BUSCA resultado, int numVertices);

void menuTipoGrafo();

void menu();

#endif
