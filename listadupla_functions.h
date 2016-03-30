#include <stdio.h>
#include <stdlib.h>


typedef struct Elemento{
	int num;
	struct Elemento * proximo;
	struct Elemento * anterior;	
}Elemento;

typedef struct Lista{
	int tamanho;
	struct Elemento * inicio;
	struct Elemento * fim;
}Lista;



void inicializa(Lista * lista);                 // Necess�ria para indicar o in�cio e o fim da Lista, e tamanho zero;

void adiciona(Lista *lista,int Numero);         // Adiciona um elemento na lista, deve se passar o n�mero que a fun��o define onde o elemento ser� adicionado

void remover(Lista *lista,int sequencial);      // Remove da lista, deve-se saber o sequencial do elemento

void exibe_crescente(Lista *lista);				// Exibe crescentemente Elemento_Atual = Proximo at� apontar NULL

void exibe_decrescente(Lista *lista);           // Exibe decrescentemente Elemento_Atual = Anterior at� apontar NULL

