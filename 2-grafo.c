#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********Leia me**********/
/**************************/
// Para buscar:           //
//                        //
//			$ prog "nome" //
////////////////////////////
// Para Mostrar o grafo e //
//  para Mostrar o array: //
//                        //
//			$ prog print  //
////////////////////////////

void err(int erro){

	switch(erro){

		case -1:
			printf("\n\npessoa nao existe\n\n");
		break;

		case -2:
			printf("\n\nnao tem amigos\n\n");
		break;

		case -3:
			printf("\n\n Falta um parametro de entrada \n\n");
			printf("\tTente: $ prog 'nome'\n\tou   : $ prog print\n");
		break;
	}
}

int busca(char *nome, int tam, const char referencia[6][30]){

	for (int i = 0; i < tam; ++i){	

		if (strcmp(nome,referencia[i]) == 0){
			return i;
		}
	}

	return -1;
}


void amigos(const int matriz[6][6],const char referencia[6][30],int id, int tam){

	int j = 0;

	for (int i = 0; i < tam ; ++i){

		if(matriz[id][i] == 1){
			printf("%s	", referencia[i]);
		}else{
			++j;
		}

		if (j == tam){
			err(-2);
		}
	}
}


void localizarAmigos(const int matriz[6][6], const char referencia[6][30], char *nome, int tam){

	int id = busca(nome, tam, referencia);
	
	if(id == -1){
		err(id);
		return;
	}

	printf("Os amigos de %s sao :\n\t", nome);
	amigos(matriz,referencia,id,tam);
}

void mostrarGrafo(const int matriz[6][6], const char referencia[6][30], int tam){

	int vetor[(tam*tam)+(tam*2)];
	int l = 0;

	printf("\n\n=================== Rede Social - Grafo ===================\n");
	for (int k = 0; k < tam; ++k){
		printf("	%s",referencia[k]);
	}
	printf("\n");
	for (int i = 0; i < tam; ++i){
		printf("%s", referencia[i]);
		vetor[l++] = i; //////////////////////////////////// <<< Vetor
		for (int j = 0; j < tam; ++j){
			printf("	%d    ",matriz[i][j]);
			(matriz[i][j] == 1)? vetor[l++] = j: 0; //////// <<< Vetor
		}
		printf("\n");
		vetor[l++] = -1;
	}
	vetor[l++] = -2;

	printf("\n\n=================== Rede Social - Array ===================\n");

	for (int l = 0; vetor[l] != -2; ++l){
		printf("|%d|",vetor[l]);
	}

	printf("\n");

}

int main(int argc, char *argv[]){
	
	// inicialização da rede social
	int tam = 6;
	char referencia[6][30] = {"denini","Jorge","Romulo","Zezin","Breno","Neymar"};
	int matriz[6][6] = 	   {0,1,0,0,0,0,
					  		1,0,1,1,0,0,
					  		0,1,0,1,1,0,
					 		0,1,1,0,1,1,
					 		0,0,1,1,0,1,
					   		0,0,0,1,1,0};
	if(!argv[1]){
		err(-3);
	}else if (strcmp(argv[1],"print") == 0){
		mostrarGrafo(matriz,referencia,tam);

	}else{

		localizarAmigos(matriz,referencia,argv[1],tam);
	}
	
	return 0;
}