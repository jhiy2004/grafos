#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "matriz_adj.h"

int main(){
	Grafo* g = criarGrafo(9);

	inserirArestaPeso(g, 0, 1, 4);  // Aresta de 0 a 1 com peso 4
	inserirArestaPeso(g, 0, 7, 8);  // Aresta de 0 a 7 com peso 8

	inserirArestaPeso(g, 1, 0, 4);  // Aresta de 1 a 0 com peso 4
	inserirArestaPeso(g, 1, 2, 8);  // Aresta de 1 a 2 com peso 8
	inserirArestaPeso(g, 1, 7, 11); // Aresta de 1 a 7 com peso 11

	inserirArestaPeso(g, 2, 1, 8);  // Aresta de 2 a 1 com peso 8
	inserirArestaPeso(g, 2, 3, 7);  // Aresta de 2 a 3 com peso 7
	inserirArestaPeso(g, 2, 5, 4);  // Aresta de 2 a 5 com peso 4
	inserirArestaPeso(g, 2, 8, 2);  // Aresta de 2 a 8 com peso 2

	inserirArestaPeso(g, 3, 2, 7);  // Aresta de 3 a 2 com peso 7
	inserirArestaPeso(g, 3, 4, 9);  // Aresta de 3 a 4 com peso 9
	inserirArestaPeso(g, 3, 5, 14); // Aresta de 3 a 5 com peso 14

	inserirArestaPeso(g, 4, 3, 9);  // Aresta de 4 a 3 com peso 9
	inserirArestaPeso(g, 4, 5, 10); // Aresta de 4 a 5 com peso 10

	inserirArestaPeso(g, 5, 2, 4);  // Aresta de 5 a 2 com peso 4
	inserirArestaPeso(g, 5, 3, 14); // Aresta de 5 a 3 com peso 14
	inserirArestaPeso(g, 5, 4, 10); // Aresta de 5 a 4 com peso 10
	inserirArestaPeso(g, 5, 6, 2);  // Aresta de 5 a 6 com peso 2

	inserirArestaPeso(g, 6, 5, 2);  // Aresta de 6 a 5 com peso 2
	inserirArestaPeso(g, 6, 7, 1);  // Aresta de 6 a 7 com peso 1
	inserirArestaPeso(g, 6, 8, 6);  // Aresta de 6 a 8 com peso 6

	inserirArestaPeso(g, 7, 0, 8);  // Aresta de 7 a 0 com peso 8
	inserirArestaPeso(g, 7, 1, 11); // Aresta de 7 a 1 com peso 11
	inserirArestaPeso(g, 7, 6, 1);  // Aresta de 7 a 6 com peso 1
	inserirArestaPeso(g, 7, 8, 7);  // Aresta de 7 a 8 com peso 7

	inserirArestaPeso(g, 8, 2, 2);  // Aresta de 8 a 2 com peso 2
	inserirArestaPeso(g, 8, 6, 6);  // Aresta de 8 a 6 com peso 6
	inserirArestaPeso(g, 8, 7, 7);  // Aresta de 8 a 7 com peso 7

	imprimirArestas(g);

	int* pai = dijkstra(g, 0);

	printf("[");
	for(int i = 0; i < g->n; i++){
		printf("%d, ", pai[i]);
	}
	printf("]\n");

	return 0;
}
