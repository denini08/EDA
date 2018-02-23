#include <stdio.h>
#include <stdlib.h>
/*
int quick(int *array, int esq, int dir, int valor){
    int i, j, x,pivo;
     int aux;
    i = esq;
    j = dir;
    pivo = ((esq + dir)/2);
    x = array[pivo];
     
    while(i < j) {
        while(array[i] < x && i < dir) { 
            i++;
        }
        while(array[j] > x && j > esq) { 
            j--;
        }
        if(i < j) {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
            i++;
            j--;
        }
    }
    
    aux = array[pivo];
    array[pivo] = array[j];
    array[j] = aux;

    if(j == valor - 1 ){
        printf("\n\n%d\n\n", j );
        return array[j];
    }
    else if(j > valor -1) {
        quick(array, esq, j, valor);
    }
    else if(j < valor -1) {
        quick(array, i, dir, valor);
    }
}
*/


void trocar(int *vetor,int i, int j){
	int aux;
	
	aux = vetor[i];
    vetor[i] = vetor[j];
	vetor[j] = aux;
}


int separar(int* vetor, int esq, int dir){
    int i = esq;
	int j = dir;

	int pivo = vetor[dir];
	
	
    
    while ( i < j ){
        while ( vetor[i] < pivo  ) i++;
        
        while ( vetor[j] > pivo ) j--;
        
        if ( vetor[i] == vetor[j] )i++;   //nao sei se isso e necessario :S
        if ( i < j ) {
            trocar(vetor,i,j);
	    }
    }
    return j;
}

int quick_select(int* vetor, int esq, int dir, int posicao)
{
    if ( esq == dir ) return vetor[esq];
    int pivo = separar(vetor, esq, dir);
    int tamanho = pivo - esq + 1;
    if ( tamanho == posicao ) return vetor[pivo];
    else if ( posicao < tamanho ) return quick_select(vetor, esq, pivo - 1, posicao);  //vai para esquerda
    else  return quick_select(vetor, pivo + 1, dir, posicao - tamanho);	//vai para direita
}

int main(int argc, char *argv[]){

    int array[8] = {7,1,3,10,17,2,21,9};
	int array2[20] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10}; //20
    int n = 0;
    if(!argv[1]){
        printf("Parametro Invalido\n");
        printf("Tente :\n\t $prog 'numero'\n\n");
        return 1;
    }

    n = atoi(argv[1]);

    if (n < 1 || n > 20){
       printf("numero nao localizado no array\n");
       return 2;
    }
    printf("O %dth menor elemento: %d", n, quick_select(array2,0,19,n));

    return 0;
}

//https://ideone.com/Bkaglb
//http://www.sourcetricks.com/2011/06/quick-select.html#.Wh2hjVWnEoA