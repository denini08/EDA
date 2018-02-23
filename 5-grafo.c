#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct No{
	int n;
	struct No *prox;
};


// largura
void adcfila(struct No **fila, int number){

	if (!(*fila) ){
		(*fila) = (struct No*)malloc(sizeof(struct No));
		(*fila)->prox = NULL;
		(*fila)->n = number;
	}else{

		struct No *aux = (struct No*)malloc(sizeof(struct No));
		aux->n = number;
		aux->prox = (*fila);
		(*fila) = aux;
	}

}

int iniciofila(struct No *fila){

	while((fila)->prox){
		(fila) = (fila)->prox;
	}

	return (fila)->n;
}

int procurarfila(struct No *fila, int number){

	while((fila)){

		if ((fila)->n == number){
			return 1;
		}

		fila = fila->prox;
	}
	return 0;
}


void remfila(struct No **fila){

	struct No *cabeca = (*fila);
	struct No *aux = NULL;

	while((*fila)->prox){
		aux = (*fila);
		(*fila) = (*fila)->prox;
	}

	if ((*fila) == cabeca){
		(*fila) = NULL;

	}else{
		aux->prox = NULL;
		(*fila) = cabeca;
	}

}
struct No *largura(const int matriz[13][13], int tam,int inicial){

	//inicialização
	struct No *fila = NULL;
	struct No *jafoi = NULL;

	//leitura
	adcfila(&fila,inicial);
	adcfila(&jafoi,inicial);

	for(int j = 0; fila; ++j){
		int lugar = iniciofila(fila);

		for(int i = 0; i < tam; ++i){

			if(matriz[lugar][i] == 1 && procurarfila(jafoi, i) == 0){ // varer o grafo em busca de novos membros
				adcfila(&fila,i);
				adcfila(&jafoi,i);
			}
		}

		remfila(&fila);
	}

	//Fim

	return jafoi;
}

void printfila(struct No *fila, const char referencia[13]){

	if (fila == NULL){
		return;
	}

	if (fila->prox){
		printfila(fila->prox,referencia);
	}

	printf("%c ", referencia[fila->n]);
}

//Fim largura






// profundidade

void empilhar(struct No **pilha, int number){

	if (!(*pilha)){
		
		(*pilha) = (struct No*)malloc(sizeof(struct No));
		(*pilha)->prox = NULL;
		(*pilha)->n = number;
	}else{

		struct No *aux = (struct No*)malloc(sizeof(struct No));
		aux->n = number;
		aux->prox = (*pilha);
		(*pilha) = aux;
	}
}

int iniciopilha(struct No *pilha){

	if (pilha){

		return pilha->n;
	}
}

int procurarPilha(struct No *pilha, int number){

	while(pilha){

		if (pilha->n == number){
			return 1;
		}

		pilha = pilha->prox;
	}

	return 0;
}


void desempilhar(struct No **pilha){

	if((*pilha)->prox){
		(*pilha) = (*pilha)->prox;
	}else{

		(*pilha) = NULL;
	}

}
struct No *profundidade(int matriz[13][13], int tam, int inicial){

	//inicialização
	struct No *pilha = NULL;
	struct No *jafoi = NULL;

	//leitura
	empilhar(&pilha,inicial);
	empilhar(&jafoi,inicial);

	for(int j = 0; pilha; ++j){

		int lugar = iniciopilha(pilha);
		desempilhar(&pilha);

		for(int i = 0; i < tam; ++i){

			if(matriz[lugar][i] == 1 && procurarPilha(jafoi, i) == 0){ // varer o grafo em busca de novos membros
				empilhar(&pilha,i);
				empilhar(&jafoi,i);
			}
		}
	}

	// Fim

	return jafoi;
}


void printpilha(struct No *pilha,const char referencia[13]){

	if (pilha == NULL){
		return;
	}

	if (pilha->prox){
		printpilha(pilha->prox,referencia);
	}

	printf("%c ", referencia[pilha->n]);
}


int main(int argc, char *argv[]){

	int inicial = 0;
	// inicialização do Grafo
	int tam = 13;
	char referencia[13] = {'a','b','c','d','e','f','g','h','i','j','k','l','m'};
							  //a b c d e f g h i j k l m
	int matriz[13][13] = 	   {0,1,1,1,0,0,0,0,0,0,0,0,0, //a
					  			1,0,1,0,0,0,0,0,0,0,0,0,0, //b
					  			1,1,0,0,1,1,0,0,0,0,0,0,0, //c
					  			1,0,0,0,0,0,0,1,0,0,0,0,0, //d
					  			0,0,1,0,0,1,0,0,0,0,0,0,0, //e
					  			0,0,1,0,1,0,1,0,0,0,0,0,0, //f
					  			0,0,0,0,0,1,0,1,1,0,0,0,0, //g
					  			0,0,0,1,0,0,1,0,1,0,0,0,0, //h
					  			0,0,0,0,0,0,1,1,0,1,0,0,1, //i
					  			0,0,0,0,0,0,0,0,1,0,1,0,1, //j
					  			0,0,0,0,0,0,0,0,0,1,0,1,0, //k
					  			0,0,0,0,0,0,0,0,0,0,1,0,1, //l
					  			0,0,0,0,0,0,0,0,1,1,0,1,0};//m

	if(!argv[1]) printf("Parametro nao reconhecido\n");

	else if(strcmp(argv[1],"largura") == 0) printfila(largura(matriz,tam,inicial), referencia);

	else if(strcmp(argv[1],"profundidade") == 0) printpilha(profundidade(matriz,tam,inicial),referencia);
	
	return 0;
}