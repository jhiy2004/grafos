#include <stdio.h>
#include <stdlib.h>
#include "matriz_adj.h"

int main(){
	Grafo* g = criarGrafo(16);

	inserirAresta(g, 0, 1);
	inserirAresta(g, 1, 0);

	inserirAresta(g, 0, 4);
	inserirAresta(g, 4, 0);

	inserirAresta(g, 1, 4);
	inserirAresta(g, 4, 1);

	inserirAresta(g, 1, 2);
	inserirAresta(g, 2, 1);

	inserirAresta(g, 2, 3);
	inserirAresta(g, 3, 2);

	inserirAresta(g, 2, 6);
	inserirAresta(g, 6, 2);

	inserirAresta(g, 3, 7);
	inserirAresta(g, 7, 3);

	inserirAresta(g, 7, 6);
	inserirAresta(g, 6, 7);

	inserirAresta(g, 6, 11);
	inserirAresta(g, 11, 6);

	inserirAresta(g, 7, 11);
	inserirAresta(g, 11, 7);

	inserirAresta(g, 4, 8);
	inserirAresta(g, 8, 4);

	inserirAresta(g, 8, 9);
	inserirAresta(g, 9, 8);

	inserirAresta(g, 8, 12);
	inserirAresta(g, 12, 8);

	inserirAresta(g, 8, 13);
	inserirAresta(g, 13, 8);

	inserirAresta(g, 9, 5);
	inserirAresta(g, 5, 9);

	inserirAresta(g, 9, 10);
	inserirAresta(g, 10, 9);

	inserirAresta(g, 9, 12);
	inserirAresta(g, 12, 9);

	inserirAresta(g, 5, 10);
	inserirAresta(g, 10, 5);

	inserirAresta(g, 10, 13);
	inserirAresta(g, 13, 10);

	inserirAresta(g, 10, 14);
	inserirAresta(g, 14, 10);

	inserirAresta(g, 13, 12);
	inserirAresta(g, 12, 13);
	
	inserirAresta(g, 13, 14);
	inserirAresta(g, 14, 13);

	inserirAresta(g, 14, 15);
	inserirAresta(g, 15, 14);

	imprimirArestas(g);

	int* pai = buscaLargura(g, 0);

	printf("[");
	for(int i = 0; i < g->n; i++){
		printf("%d, ", pai[i]);
	}
	printf("]\n");
	return 0;
}
