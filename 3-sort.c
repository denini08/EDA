/* O usuario vai passar o por parametros da main o arquivo que contem todos
os dados dos sensores, os dados terao o seguinte padrao:
primeira linha: metodo de ordenacao: [q,b,s] respectivamente-> quicksort, bubllesort, selectionsort 
depois a quantidade de dados, na proxima linhas colocar dia/mes/ano, informacao e nome do sensor
exemplo:


q 2
21/03/2017 50 sensor1
24/02/2017 19 temperatura

*/


#include <stdio.h>
#include <stdlib.h>

struct Sensor{
	int dia;
	int mes;
	int ano;
	int formula;
	int informacao;
	char nome_sensor[30];
};

void selection(struct Sensor *sensor, int repeticoes){
	int menor;
	struct Sensor cara;
	for(int i = 0; i<repeticoes;i++){
		cara = (sensor)[i];

		for (int j = i; j < repeticoes; j++){
			if(cara.formula > (sensor)[j].formula){
				cara = (sensor)[j];
				menor = j;
			}

		}
		(sensor)[menor] = (sensor)[i];
		(sensor)[i] = cara;
	}
}

void bublle(struct Sensor *sensor, int repeticoes){

	int counter = 0;
	struct Sensor aux;

	for (int i = 0; i < repeticoes; i++){
		if((sensor[i].formula > sensor[i+1].formula)){
			aux = sensor[i+1];
			sensor[i+1] = sensor[i];
			sensor[i] = aux;
			counter++;
		}
	}

	if (counter != 0){
		bublle(sensor, repeticoes);
	}
}


void trocar(struct Sensor *sensor,int i, int j){
	struct Sensor aux;
	
	aux = sensor[i];
    sensor[i] = sensor[j];
	sensor[j] = aux;
}

int separar(struct Sensor *sensor,int esq, int dir){  //assumimos que na primeira recursao esq é o pivo
	int i = esq;
	int j = dir;

	
	while(i < j){
		while(i < dir && sensor[i].formula <= sensor[esq].formula) i++;
		while(j > esq && sensor[j].formula >= sensor[esq].formula) j--;
		
		if(i < j){
			trocar(sensor,i,j);
			i++;
			j--;
		}
		
		trocar(sensor,esq,j);
	}
	return j;
}



void quick(struct Sensor *sensor, int esq, int dir){
  if(esq < dir){
	  int pivo = separar(sensor,esq,dir);
	  quick(sensor,esq, pivo -1);
	  quick(sensor, pivo +1, dir);
  }
}


int main(int argc, char *argv[]){
	int repeticoes;
	char cod;
	struct Sensor *sensor = NULL;
	FILE *arq =NULL;
	
	if(argc <= 1 ){	//caso nao tenho passado o arquivo de entrada
		printf("Faltando o arquivo");
		return -1;
	}
	
	if(arq = fopen(argv[1], "r")){ 								//abrindo o arquivo que foi passado por parametro
		fscanf(arq,"%c %d", &cod, &repeticoes );				//codigo e quantidade
		sensor = malloc(sizeof(struct Sensor) * repeticoes);  	//vetor de sensores :D
		for(int i = 0; i < repeticoes ; i++){					//pegando do arquivo
			//28/04/2017 38 temperatura
			fscanf(arq,"%d/%d/%d %d %s\n", &sensor[i].dia ,&sensor[i].mes, &sensor[i].ano, &sensor[i].informacao, &sensor[i].nome_sensor);
			sensor[i].formula = (sensor)[i].ano * 10000 + (sensor)[i].mes * 100 + (sensor)[i].dia;
		}
	}else{
		printf("Arquivo nao encontrado\n\n");
		return -2;
	}
	
	//menuzinho
	if(cod == 's'){
		selection(sensor ,repeticoes);
	}
	if(cod == 'b' ){
		bublle(sensor ,repeticoes - 1);
	}
	if(cod == 'q'){
		quick(sensor,0,repeticoes-1);
	}
	for(int i = 0; i < repeticoes; i++){
		printf("%d/%d/%d\t %d Nome do sensor: %s\n" , (sensor)[i].dia, (sensor)[i].mes, (sensor)[i].ano, (sensor)[i].informacao, (sensor)[i].nome_sensor);
	}
	
}