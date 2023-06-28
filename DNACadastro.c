#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct No {
	char dados;
	struct No* proximo;
}No;

typedef struct Fila {
	No* inicio;
	No* fim;
}Fila;

typedef struct Pilha {
	No* topo;
}Pilha;

No* criarNo(char dados){
	No* novoNo = (No*)malloc(sizeof(No));
	novoNo->dados = dados;
	novoNo->proximo = NULL;
	return novoNo;
}

void enfileirar(Fila* fila, char dados) {
	No* novoNo = criarNo(dados);
	if(fila->inicio == NULL){
		fila->inicio = novoNo;
		fila->fim = novoNo;
	}else{
		fila->fim->proximo = novoNo;
		fila->fim = novoNo;
	}
}

char desenfileirar(Fila* fila) {
	if(fila->inicio == NULL){
		return '\0';
	}
	char dados = fila->inicio->dados;
	No* temp = fila->inicio;
	fila->inicio = fila->inicio->proximo;
	if(fila->inicio == NULL){
		fila->fim = NULL;
	}
	free(temp);
	return dados;
}

void push(Pilha* pilha, char dados) {
	No* novoNo = criarNo(dados);
	novoNo->proximo = pilha->topo;
	pilha->topo = novoNo;
}

char pop(Pilha* pilha){
	if(pilha->topo == NULL){
		return '\0';
	}
	char dados = pilha->topo->dados;
	No* temp = pilha->topo;
	pilha->topo = pilha->topo->proximo;
	free(temp);
	return dados;
}

void impFila(Fila* fila){
	No* atual = fila->inicio;
	while (atual != NULL){
		printf("%c ", atual->dados);
		atual = atual->proximo;
	}
	printf("\n");
}

void impPilha (Pilha* pilha) {
	No* atual = pilha->topo;
	while(atual != NULL){
		printf("%c ", atual->dados);
		atual = atual->proximo;
	}
	printf("\n");
}

int main (){
	setlocale(LC_ALL, "Portuguese");
	Fila dnaFila;
	Pilha dnaPilha;
	dnaFila.inicio = NULL;
	dnaFila.fim = NULL;
	dnaPilha.topo = NULL;
	
	char dnaSequencia[100];
	printf("Digite a sequência de DNA: ");
	scanf("%s", dnaSequencia);
	
	int i;
	int tamSequencia = strlen(dnaSequencia);
	for(i = 0; i < tamSequencia; i++){
		enfileirar(&dnaFila, dnaSequencia[i]);
	}
	system ("cls");
	
	printf("Sequência de DNA original: ");
	impFila(&dnaFila);
	
	while (dnaFila.inicio != NULL){
		char nucleotideo = desenfileirar(&dnaFila);
		switch(nucleotideo){
			case 'A':
				push(&dnaPilha, 'T');
				break;
			case 'T':
				push(&dnaPilha, 'A');
				break;
			case 'C':
				push(&dnaPilha, 'G');
				break;
			case 'G':
				push(&dnaPilha, 'C');
				break;
			default:
				printf("Nucleotídeos invalidos: %c\n", nucleotideo);
				break;
		}
	}
	
	printf("Sequência de DNA complementar: ");
	impPilha(&dnaPilha);
	
	system ("pause");
	return 0;
}
