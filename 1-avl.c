#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct No{
	char nome[30];
	int numero;
	int balance;
	struct No* fesq;
	struct No* fdir;	
};

int altura(struct No *raiz){
	int ld = 0;
	int le = 0;
	if (!raiz){
		return 0;	
	}
	if(raiz->fesq){
		le = altura(raiz->fesq);
	}
	if(raiz->fdir){
		ld = altura(raiz->fdir);
	}
	if(le > ld){
		return le + 1;
	}else{
		return ld + 1;
	}
}

void balance_E(struct No **raiz){
	struct No **b = (struct No**)malloc(sizeof(struct No));
	(*b) = (*raiz)->fesq;

	(*raiz)->fesq = (*b)->fdir;
	(*b)->fdir = (*raiz);
	(*raiz) = (*b);
	free(b);
}

void balance_ED(struct No **raiz){
	struct No **b = (struct No**)malloc(sizeof(struct No));
	struct No **c = (struct No**)malloc(sizeof(struct No));
	(*b) = (*raiz)->fesq;
	(*c) = (*raiz)->fesq->fdir;

	(*raiz)->fesq = (*c)->fdir;
	(*b)->fdir = (*c)->fesq;
	(*c)->fesq = (*b);
	(*c)->fdir = (*raiz);
	(*raiz) = (*c); 
	free(b);
	free(c);
}

void balance_D(struct No **raiz){
	struct No **b = (struct No**)malloc(sizeof(struct No));
	(*b) = (*raiz)->fdir;

	(*raiz)->fdir = (*b)->fesq;
	(*b)->fesq = (*raiz);
	(*raiz) = (*b);
	free(b);
}

void balance_DE(struct No **raiz){
	struct No **b = (struct No**)malloc(sizeof(struct No));
	struct No **c = (struct No**)malloc(sizeof(struct No));
	(*b) = (*raiz)->fdir;
	(*c) = (*raiz)->fdir->fesq;

	(*raiz)->fdir = (*c)->fesq;
	(*b)->fesq = (*c)->fdir;
	(*c)->fdir = (*b);
	(*c)->fesq = (*raiz);
	(*raiz) = (*c); 
	free(b);
	free(c);
}

void calc_balance(struct No **raiz){

	if ((*raiz)){

		calc_balance(&(*raiz)->fesq);
		calc_balance(&(*raiz)->fdir);

		(*raiz)->balance = altura((*raiz)->fdir) - altura((*raiz)->fesq);
	}
}

void balance(struct No **raiz){

	if (((*raiz)->balance < -1)){

		if ((*raiz)->fesq->balance > 0){
			printf("Balanciar Esquerdo Direito\n");
			balance_ED(&(*raiz));
			calc_balance(&(*raiz));
		}else{
			printf("Balanciar Esquerdo\n");
			balance_E(&(*raiz));
			calc_balance(&(*raiz));
		}
	}

	if (((*raiz)->balance) > 1){
		if(((*raiz)->fdir->balance) < 0){
			printf("Balanciar Direito Esquerdo\n");
			balance_DE(&(*raiz));
			calc_balance(&(*raiz));
		}else{
			printf("Balanciar Direito\n");
			balance_D(&(*raiz));
			calc_balance(&(*raiz));
		}
	}

}


void inserir(struct No **raiz,int telefone,char *novonome){ // inserir
	
	if((*raiz) != NULL){ //teste de folha
		
		if(strcmp((*raiz)->nome,novonome) > 0 ){ //saber se o futuro filho será dir ou esq e chama recursivamente [inserir()]
			inserir(&(*raiz)->fesq,telefone,novonome);
		}else{
			inserir(&(*raiz)->fdir,telefone,novonome);
		}
	}else{ //adc novo no na arvore
		(*raiz) = (struct No*)malloc(sizeof(struct No));
		strcpy((*raiz)->nome, novonome);
		(*raiz)->numero = telefone;
		(*raiz)->fesq = NULL;
		(*raiz)->fdir = NULL;
	}

	(*raiz)->balance = altura((*raiz)->fdir) - altura((*raiz)->fesq); 
	
	balance(&(*raiz));
}

void print(struct No *raiz){

	if(((raiz)) != NULL){
		print(raiz->fesq);
		printf("Contato \n \t Nome : %s\n", (raiz)->nome);
		printf("\t Numero : %d\n\n",(raiz)->numero);
		print((raiz)->fdir);
	}

}

struct No *busca(struct No *raiz, char *novonome){

	if ((raiz)){
		if(strcmp((raiz)->nome,novonome) == 0) return (raiz);

		if (strcmp((raiz)->nome,novonome) > 0){
			busca(raiz->fesq,novonome);
		}else{
			busca(raiz->fdir,novonome);
		}
	}else{
		return NULL;
	}
}

void remover_aux(struct No **temp){

	struct No *aux = (struct No*)malloc(sizeof(struct No));
	struct No *pai = NULL;

		if ((*temp)->fesq !=NULL){ // teste filho esquerdo
			
			aux = (*temp)->fesq;

			while(aux->fdir != NULL){

				pai = aux;
				aux = aux->fdir;
			}
			if (((pai))){
				pai->fdir = aux->fesq;
				aux->fesq = (*temp)->fesq;
			}

			aux->fdir = (*temp)->fdir;


			(*temp) = aux;

		}else if ((*temp)->fdir != NULL){ //teste direito se esquerdo falhou
			
			(*temp) = (*temp)->fdir; 
		}else{

			(*temp) = NULL;
		}
}

struct No *remover(struct No **raiz, char *novonome){

	if ((!(*raiz))){
		return NULL;
	}

	if(strcmp((*raiz)->nome,novonome) == 0){ //Encontrou

		remover_aux(raiz); //Retornou Raiz pronta
		return (*raiz);

	}else if(strcmp((*raiz)->nome,novonome) > 0){

		(*raiz)->fesq = remover(&(*raiz)->fesq,novonome);

	}else{

		(*raiz)->fdir = remover(&(*raiz)->fdir,novonome);
	}

	return (*raiz);
}

void inserirContato(struct No **raiz,int telefone,char *novonome){

	if(busca(*raiz, novonome) == NULL){

		inserir(raiz, telefone, novonome);
		printf("+Inserido Contato \n+ \t Nome : %s\n", novonome);
		printf("+\t Numero : %d\n\n",telefone);
	}else{

		printf("x O contato %s nao pode ser adicionado\nx \t contato ja existente \n", novonome);
	}
}

void excluirContato(struct No **raiz, char *novonome){

	if(busca(*raiz,novonome) == NULL){
        printf("\n\n------------Contato nao encontrado: %s \n", novonome);
        printf("-------------------------------------------\n\n");
    }else{

        remover((raiz),novonome);
        printf("\n\n------------Contato Excluido: %s \n", novonome);
        printf("-------------------------------------------\n\n");
    }
} 

void buscarContato(struct No *raiz, char *novonome){
	struct No *aux = NULL;
	
	aux = busca(raiz, novonome);

	if (aux){
		printf("\n\n~~~~~~~~~~~~~~Encontrado~~~~~~~~~~~~~\n~~~~\n");	
		printf("~~~~ %s\t%d\n~~~~\n",aux->nome, aux->numero);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	}else{
		printf("\n\n~~~~~~~~~~~~Nao Encontrado~~~~~~~~~~~\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	}

}

void mostrarAgenda(struct No *raiz){
	struct No *aux = NULL;

	printf("\n\n____________Lista de Contatos___________\n");
	print(raiz);
	printf("________________________________________\n\n");
}

int main(int argc, char const *argv[]){
	
	struct No* raiz = NULL;

	inserirContato(&raiz,981563341,"denini");
	inserirContato(&raiz,997372597,"geovanne");
	inserirContato(&raiz,999876543,"breno");
	inserirContato(&raiz,997867545,"alberto");
	inserirContato(&raiz,929394952,"zezin");
	inserirContato(&raiz,981457812,"douglas");
	inserirContato(&raiz,974258719,"daubio");
	inserirContato(&raiz,929394952,"thiago");
	inserirContato(&raiz,919192923,"douglas");

	buscarContato(raiz, "douglas");
	excluirContato(&raiz, "douglas");
	mostrarAgenda(raiz);

	return 0;
}