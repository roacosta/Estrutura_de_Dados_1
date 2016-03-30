#include <stdlib.h>
#include <stdio.h>
#include "listadupla_functions.h"

//Desenvolvido por Rodrigo Almeida Costa


void inicializa(Lista * lista){
	lista->inicio 	= NULL;
	lista->fim 		= NULL;
	lista->tamanho 	= 0;
}

void adiciona(Lista *lista,int Numero){
	Elemento * Elemento_Novo;
	
	Elemento_Novo 			= (Elemento*) malloc(sizeof(Elemento));
	Elemento_Novo->num 		= Numero;
	
	Elemento_Novo->proximo 	= NULL;
	Elemento_Novo->anterior = NULL;
	
	
	//Verifica se a lista está vazia e adiciona 
	if (lista->tamanho == 0){	

		lista->inicio = Elemento_Novo;
		lista->fim    = Elemento_Novo;
		lista->tamanho= 1;
		
	}else{
		
		Elemento * Elemento_Anterior;
		Elemento * Elemento_Atual;
		
		Elemento_Anterior 	= NULL;	
		Elemento_Atual 		= lista->inicio;
		
		
		for(Elemento_Atual 	= lista->inicio; Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->proximo){
			
			if(Elemento_Atual->num >= Elemento_Novo->num ){
				
				//==== Verifica se é o primeiro elemento da lista: Ex: adicionar 1 na lista{2,3,4,5}
				if(Elemento_Atual == lista->inicio){
					
					Elemento_Atual->anterior = Elemento_Novo;
					Elemento_Novo->proximo   = Elemento_Atual;
					
					lista->inicio 	= Elemento_Novo;
					lista->tamanho++;					
					break;										
				}
				
				//==== Verifica se está no meio da lista: Ex: adicionar 3 na lista{1,2,4,5}
				if(Elemento_Atual != lista->inicio && Elemento_Atual != lista->fim){
					
					Elemento_Atual->anterior	= Elemento_Novo;
					Elemento_Novo->proximo      = Elemento_Atual;
					
					Elemento_Anterior->proximo 	= Elemento_Novo;
					Elemento_Novo->anterior     = Elemento_Anterior;
					
					lista->tamanho++;
					break;
				}
				//==== Vericica se está no fim da lista: Ex: adicionar 4 na lista{1,2,3,5}
				if(Elemento_Atual == lista->fim){
					
					Elemento_Atual->anterior 	= Elemento_Novo;
					Elemento_Novo->proximo 		= Elemento_Atual;
					
					Elemento_Anterior->proximo  = Elemento_Novo;					
					Elemento_Novo->anterior 	= Elemento_Anterior;
					
					lista->tamanho++;
					break;
				}				
			}
			//==== Verifica se deve adicionar no último elemento da lista: Ex: adicionar 6 na lista{1,2,3,4,5}
			if(lista->fim == Elemento_Atual){
				Elemento_Atual->proximo = Elemento_Novo;
				Elemento_Novo->anterior = Elemento_Atual;
				lista->fim = Elemento_Novo;
				lista->tamanho++;
				break;
			}
			Elemento_Anterior = Elemento_Atual;
		}
	}	
}

void remover(Lista *lista,int sequencial){ //Remove um elemento da lista, é necessário saber o sequencial a ser removido
	if(lista->tamanho > 0){
		Elemento *Elemento_Atual;
		//Elemento_Atual 		= (Elemento*) malloc(sizeof(Elemento));
		Elemento *Elemento_Anterior;
		//Elemento_Anterior	= (Elemento*) malloc(sizeof(Elemento));
		Elemento_Atual 		= lista->inicio;
		
		int i;

		for(i = 1;i <= (lista->tamanho); i++){

			if(i == sequencial){
				//Verifica se é o primeiro
				if(i == 1){
					lista->inicio= Elemento_Atual->proximo;
					lista->inicio->anterior = NULL;
					free(Elemento_Atual);
				}
				else
				//Verifica se está no meio;
				{
					if(i != lista->tamanho){
						Elemento_Anterior->proximo = Elemento_Atual->proximo;
						Elemento_Atual->proximo->anterior = Elemento_Anterior;
						free(Elemento_Atual);
										
					}else{
						//Verifica se é o último
						if(i == lista->tamanho){
							lista->fim = Elemento_Atual->anterior;
							Elemento_Anterior->proximo = NULL;
							free(Elemento_Atual);
						}
					}
				}

				lista->tamanho--;
				break;
			}
			Elemento_Anterior = Elemento_Atual;
			Elemento_Atual = Elemento_Atual->proximo;
		}
	}
}

void exibe_crescente(Lista *lista){
		
	Elemento * Elemento_Atual;
	
	printf("\n== Imprimindo crescentemente ==");
	
	for(Elemento_Atual = lista->inicio;Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->proximo){
		printf("\n%d",Elemento_Atual->num);
	}
	
	printf("\n");
}

void exibe_decrescente(Lista *lista){

	Elemento * Elemento_Atual;
	
	printf("\n== Imprimindo decrescentemente ==");
	
	for(Elemento_Atual = lista->fim;Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->anterior){
		printf("\n%d",Elemento_Atual->num);
	}	
	
	printf("\n");
}

int main(){
	Lista *lista;
	lista = (Lista*) malloc(sizeof(Lista));
	
	inicializa(lista);
	
	adiciona(lista,6);
	adiciona(lista,3);
	adiciona(lista,2);
	adiciona(lista,5);
	adiciona(lista,4);
	adiciona(lista,2);
	adiciona(lista,1);
	
	remover(lista,7);
	
	adiciona(lista,2);
	
	exibe_crescente(lista);
	exibe_decrescente(lista);
	
	return 0;
}


