Fila* criarFila(){
	Fila* novo = (Fila*) malloc(sizeof(Fila));

	novo->inicio = NULL;
	novo->fim = NULL;

	return novo;
}

void inserirFila(Fila *f, int valor){
	noFila* novo = (noFila*) malloc(sizeof(noFila));

	novo-> valor = valor;
	novo->prox = NULL;

	if(f->inicio == NULL && f->fim == NULL){
		f->inicio = novo;
		f->fim = novo;
		return;
	}

	f->fim->prox = novo;
	f->fim = novo;
}

int removerFila(Fila *f){
	int valor = 0;

	if(f->inicio == f->fim){
		valor = f->inicio->valor;
		free(f->inicio);

		f->inicio = NULL;
		f->fim = NULL;

		return valor;
	}

	noFila* temp = f->inicio;
	valor = temp->valor;

	f->inicio = temp->prox;
	free(temp);

	return valor;
}

int estaVazia(Fila *f){
	if(f->inicio == NULL && f->fim == NULL){
		return 1;
	}
	return 0;
}

int destruirFila(Fila* f){
	while(!estaVazia(f)){
		removerFila(f);
	}
	free(f);
}
