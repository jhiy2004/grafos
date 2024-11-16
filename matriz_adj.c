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
