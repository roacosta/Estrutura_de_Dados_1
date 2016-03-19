#include <stdlib.h>
#include <stdio.h>

//Rodrigo Almeida Costa


int main(){
	int * Vetor = (int*) malloc(sizeof(int)*5);
	int controle = 0,numero,cont1 = 0,cont2 = 0,i;
	
	//cont1 é utilizado para verificar se o usuario digitou 5 numeros e zerar
	//cont2 é uttilizado para saber a posição do vetor e o tamanho total do vetor.
	
	do{
	
		controle = scanf("%d",&numero);	
		
		if (cont1 > 4){
			cont1 = 0;
			printf("Realocou %d\n", cont2 + 5);
			int * Vetor = (int *) realloc (Vetor,(cont2 + 5)* sizeof(int));
		}
		if (controle != 0){
			Vetor[cont2] = numero;
		}
		cont2++;
		cont1++;
		
	}while (controle != 0);
	
	printf("Vetor alocado no endereco: %p com os valores: \n ", Vetor);
	
	for(i = 0; i<cont2 - 1;i++){
		printf("%d ", Vetor[i]);
	}
	
	
	
	return 0;
}
