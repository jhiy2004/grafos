FP* criarFprio(int n){
	FP* novo = (FP*) malloc(sizeof(FP));

	novo->v = (Item*) malloc(sizeof(Item)*n);
	novo->n = n;
	novo->tamanho = 0;
	novo->indice = (int*) malloc(sizeof(int)*n);

	return novo;
}

int paiFP(int i){
	return (i-1)/2;
}

int leftFP(int i){
	return 2*i + 1;
}

int rightFP(int i){
	return 2*i + 2;
}

int vaziaFP(FP* fp){
	if(fp->tamanho == 0)
		return 1;
	return 0;
}

int prioridadeFP(FP* fp, int v){
	Item* elementos = fp->v;

	return elementos[v].prioridade;
}


void insereFP(FP* fp, int v, int prioridade){
	if(fp->n == fp->tamanho){ // Se o tamanho do heap for igual a capacidade
		return;
	}

	fp->tamanho++;
	int i = fp->tamanho - 1;

	Item* elementos = fp->v;

    elementos[i].vertice = v;
	elementos[i].prioridade = prioridade;

	fp->indice[i] = i;

	// Fix the min heap property if it is violated
	while (i != 0 && elementos[fp->indice[paiFP(i)]].prioridade > elementos[fp->indice[i]].prioridade){
		int temp = fp->indice[i];

		fp->indice[i] = fp->indice[paiFP(i)];
		fp->indice[paiFP(i)] = temp;

		i = paiFP(i);
    }
}

void diminuiprioridade(FP* fp, int v, int prioridade){
	int i=0;
	Item* elementos = fp->v;

	elementos[v].prioridade = prioridade;
	for(i = 0; i < fp->tamanho; i++){
		if(fp->indice[i] == v)
			break;
	}
	while (i != 0 && elementos[fp->indice[paiFP(i)]].prioridade > elementos[fp->indice[i]].prioridade){
		int temp = fp->indice[i];

		fp->indice[i] = fp->indice[paiFP(i)];
		fp->indice[paiFP(i)] = temp;

		i = paiFP(i);
	}
}

void minHeapify(FP* fp, int i){
	int l = leftFP(i);
	int r = rightFP(i);
	int menor = i;
	Item* elementos = fp->v;

	if (l < fp->tamanho && elementos[fp->indice[l]].prioridade < elementos[fp->indice[i]].prioridade)
		menor = l;
	if (r < fp->tamanho && elementos[fp->indice[r]].prioridade < elementos[fp->indice[menor]].prioridade)
		menor = r;
	if (menor != i){
		int temp = fp->indice[i];

		fp->indice[i] = fp->indice[menor];
		fp->indice[menor] = temp;

		minHeapify(fp, menor);
	}
}

int extraiMinimoFP(FP* fp){
	Item* elementos = fp->v;

	if (fp->tamanho <= 0)
		return INT_MAX;
	if (fp->tamanho == 1){
		fp->tamanho--;
		return elementos[fp->indice[0]].vertice;
	}

	int root = elementos[fp->indice[0]].vertice;

	fp->indice[0] = fp->indice[fp->tamanho-1];
	fp->tamanho--;
	
	minHeapify(fp, 0);

	return root;
}

void imprimirHeap(FP* fp){
	printf("HEAP(Vetor) = [");
	for(int i=0; i < fp->tamanho; i++){
		printf("(%d;%d), ", (fp->v)[i].vertice, (fp->v)[i].prioridade);
	}
	printf("]\n");

	printf("HEAP(Real) = [");
	for(int i=0; i < fp->tamanho; i++){
		printf("(%d;%d), ", (fp->v)[fp->indice[i]].vertice, (fp->v)[fp->indice[i]].prioridade);
	}
	printf("]\n");
}
