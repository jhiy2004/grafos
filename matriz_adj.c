Grafo* criarGrafo(int n){
	int i = 0;
	int j = 0;

	Grafo* g = malloc(sizeof(Grafo));

	g->n = n;
	g->adj = malloc(n * sizeof(int*));
	for(i = 0; i < n; i++)
		g->adj[i] = malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			g->adj[i][j] = 0;
		}
	}
	return g;
}

void destruirGrafo(Grafo* g){
	int i = 0;
	for(i = 0; i < g->n; i++){
		free(g->adj[i]);
	}
	free(g->adj);
	free(g);
}

void inserirAresta(Grafo* g, int u, int v){
	g->adj[u][v] = 1;
	g->adj[v][u] = 1;
}

void inserirArestaPeso(Grafo* g, int u, int v, int peso){
	g->adj[u][v] = peso;
	g->adj[v][u] = peso;
}

void removerAresta(Grafo* g, int u, int v){
	g->adj[u][v] = 0;
	g->adj[v][u] = 0;
}

int possuiAresta(Grafo* g, int u, int v){
	return g->adj[u][v];
}

void imprimirArestas(Grafo *g){
	for(int i = 0; i < g->n; i++){
		for(int j = 0; j < g->n; j++){
			printf("%d ", g->adj[i][j]);
		}
		printf("\n");
	}
}

void buscaProfundidade(Grafo *g, int *pai, int p, int v){
	pai[v] = p;
	for(int i = 0; i < g->n; i++){
		if(g->adj[v][i] == 1 && pai[i] == -1){
			buscaProfundidade(g, pai, v, i);
		}
	}
}

int* encontraCaminhos(Grafo *g, int s){
	int i = 0;
	int *pai = (int*) malloc(g->n * sizeof(int));
	for(i = 0; i < g->n; i++){
		pai[i] = -1;
	}
	buscaProfundidade(g, pai, s, s);
	return pai;
}

int* buscaLargura(Grafo *g, int s){
	int w = 0;
	int v = 0;
	int *pai = (int*)malloc(g->n * sizeof(int));
	int *visitado = (int*)malloc(g->n * sizeof(int));

	Fila *f = criarFila();
	for(v = 0; v < g->n; v++){
		pai[v] = -1;
		visitado[v] = 0;
	}
	inserirFila(f, s);
	pai[s] = s;
	visitado[s] = 1;
	while(!estaVazia(f)){
		v = removerFila(f);
		for(w = 0; w < g->n; w++){
			if(g->adj[v][w] && !visitado[w]) {
				visitado[w] = 1;
				pai[w] = v;
				inserirFila(f, w);
			}
		}
	}
	destruirFila(f);
	free(visitado);
	return pai;
}

int* dijkstra(Grafo* g, int s) {
	int v, *pai = malloc(g->n * sizeof(int));
	int t;
	FP* h = criarFprio(g->n);
	for (v = 0; v < g->n; v++) {
		pai[v] = -1;
		insereFP(h, v, INT_MAX);
	}
	pai[s] = s;
	diminuiprioridade(h, s, 0);

	while (!vaziaFP(h)) {
		v = extraiMinimoFP(h);
		if (prioridadeFP(h, v) != INT_MAX)
			for (int i = 0; i < g->n; i++){
				if (g->adj[v][i] != 0){
					if (prioridadeFP(h, v)+g->adj[v][i] < prioridadeFP(h, i)) {
						diminuiprioridade(h, i, prioridadeFP(h,v)+g->adj[v][i]);
						pai[i] = v;
					}
				}
			}
	}
	return pai;
}

int* geradoraMinima(Grafo* g, int s) {
	int v, *pai = malloc(g->n * sizeof(int));
	int t;
	int *visitado = (int*)malloc(g->n * sizeof(int));
	
	FP* h = criarFprio(g->n);
	for (v = 0; v < g->n; v++) {
		pai[v] = -1;
		insereFP(h, v, INT_MAX);
		visitado[v] = 0;
	}
	pai[s] = s;
	diminuiprioridade(h, s, 0);
	visitado[0] = 1;

	while (!vaziaFP(h)) {
		imprimirHeap(h);
		printf("\n");
		v = extraiMinimoFP(h);
		printf("V: %d\n", v);

		visitado[v] = 1;

		if (prioridadeFP(h, v) != INT_MAX)
			for (int i = 0; i < g->n; i++){
				if (g->adj[v][i] != 0 && !visitado[i]){
					if (g->adj[v][i] < prioridadeFP(h, i)) {
						diminuiprioridade(h, i, g->adj[v][i]);
						pai[i] = v;
					}
				}
			}
	}
	return pai;
}

