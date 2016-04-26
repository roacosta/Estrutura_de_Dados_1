#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RodrigoCosta_Funcoes.h"


void inicializaConjunto(Conjunto * conjunto){ // Inicializa um conjunto novo
	conjunto->inicio = NULL;
	conjunto->fim    = NULL;
	conjunto->Prox   = NULL;
	conjunto->Prev   = NULL;
	conjunto->tamanho = 0;
	conjunto->id      = 0;
}

void inicializaLista(Lista * lista){ // Inicializa uma lista de conjuntos
	lista->inicioLista 	= NULL;
	lista->fimLista    	= NULL;
	lista->tamanhoLista = 0;
}

void ExibirConjunto(Conjunto *conjunto){
	// Exibe um conjunto, Independentemete se este pertence a uma lista de conjutos

	Elemento *Elemento_Atual;
	printf("\n %d - {", conjunto->id);

	for(Elemento_Atual= conjunto->inicio; Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->Prox){
		printf ("%d", Elemento_Atual->info);
		if (Elemento_Atual != conjunto->fim)
			printf(",");
	}
	printf("} ");
}

void ExibirLista(Lista *lista){
	// Exibe a lista com todos os conjuntos
	Conjunto * conjunto_Atual;
	printf("\n==== Conjuntos Numericos Salvos ====\n");

	for(conjunto_Atual = lista->inicioLista; conjunto_Atual!= NULL; conjunto_Atual = conjunto_Atual->Prox){
		ExibirConjunto(conjunto_Atual);
	}
}

void AdicionarElemento(Conjunto *conjunto,int info){
	// Adiciona um Elemento a um conjunto
	int JaExisteNoConjunto = 0;
	Elemento *Elemento_Novo = (Elemento*) malloc(sizeof(Elemento));

	Elemento_Novo->info = info;
	Elemento_Novo->Prox = NULL;
	Elemento_Novo->Prev = NULL;

	Elemento *Elemento_Atual;
	Elemento *Elemento_Anterior = NULL;


	// Se for vazio pode adicionar
	if (conjunto->tamanho == 0){
		conjunto->inicio = Elemento_Novo;
		conjunto->fim    = Elemento_Novo;
		conjunto->tamanho += 1;
		//ExibirConjunto(conjunto);
	}else{

		//verifica se o numero já existe no conjunto
		for(Elemento_Atual = conjunto->inicio; Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->Prox){
			if (Elemento_Atual->info == info){
				JaExisteNoConjunto = 1;
				break;
			}
		}

		if (!JaExisteNoConjunto){
			for(Elemento_Atual = conjunto->inicio;Elemento_Atual != NULL; Elemento_Atual = Elemento_Atual->Prox){

				if (info < conjunto->inicio->info){
					//Adiciona Elemento Na Primeira Posição
					conjunto->inicio = Elemento_Novo;
					Elemento_Atual->Prev = Elemento_Novo;
					Elemento_Novo->Prox  = Elemento_Atual;
					conjunto->tamanho++;
					//ExibirConjunto(conjunto);
					Elemento_Anterior = Elemento_Atual;

					break;
				}
				if (info > conjunto->fim->info){
					//Adiciona Elemento na Última Posição
					Elemento_Novo->Prev = conjunto->fim;
					conjunto->fim->Prox = Elemento_Novo;
					conjunto->fim = Elemento_Novo;

					conjunto->tamanho++;
					//ExibirConjunto(conjunto);
					Elemento_Anterior = Elemento_Atual;
					break;
				}

				if (conjunto->tamanho > 1 && Elemento_Anterior != NULL) {
					//printf(" Elemento_Anterior->info %d",Elemento_Anterior->info);

					if (info > Elemento_Anterior->info && info < Elemento_Atual->info){

						Elemento_Anterior->Prox = Elemento_Novo;
						Elemento_Novo->Prev = Elemento_Anterior;
						Elemento_Novo->Prox = Elemento_Atual;
						Elemento_Atual->Prev = Elemento_Novo;
						conjunto->tamanho++;
						Elemento_Anterior = Elemento_Atual;
						//ExibirConjunto(conjunto);
						break;
					}
				}
				Elemento_Anterior = Elemento_Atual;
			}
		}
	}
}



void AdicionarConjunto(Lista *lista,int * id){
	int info = 1;
	int idBackup = *id;
	char Opcao;

	//Adiciona Conjuntos a uma Lista

	Conjunto *conjunto = (Conjunto*) malloc(sizeof(Conjunto));
	inicializaConjunto(conjunto);

	conjunto->id = *id;

	// Termina de adicionar quando o usuário entra com Zero
	printf("Informe o conjunto a ser adicionado (Pressionando Enter para cada Elemento, 0 = Sair)\n");


	while(info != 0){
		scanf("%d", &info);
		if (info == 0){
			printf("\nAdicionar Elemento Zero? (S/N) : ");
			scanf(" %c",&Opcao);
		}else{
			Opcao= 'S';
		}
		if (toupper(Opcao) == 'S' || info != 0){
			AdicionarElemento(conjunto,info);
		}
	};

	//=== Só adiciona se não for um conjunto vazio
	if(conjunto->tamanho != 0){

		if (lista->tamanhoLista == 0){
			lista->fimLista 	= conjunto;
			lista->inicioLista 	= conjunto;
			lista->tamanhoLista++;
		}else{
			lista->fimLista->Prox = conjunto;
			conjunto->Prev 	= lista->fimLista;
			conjunto->Prox  = NULL;
			lista->fimLista	= conjunto;
			lista->tamanhoLista++;
		}

		ExibirLista(lista);

	}else{
		// Se for vazio libera a memória e retorna o sequencial
		free(conjunto);
		*id = idBackup;
	}
}



void ExcluirConjunto(Lista *lista,int opcao){
	// Elimia um conjunto da lista de conjuntos
	Conjunto * conjunto_Atual;
	Conjunto * conjunto_Anterior;

	if (lista->tamanhoLista > 0){

		if (opcao == 0){

			ExibirLista(lista);

			printf("\n\nQual dos conjuntos deseja excluir?\n");
			scanf("%d",&opcao);

		}
		for(conjunto_Atual = lista->inicioLista; conjunto_Atual != NULL; conjunto_Atual = conjunto_Atual->Prox){
			if (conjunto_Atual->id == opcao){
				if(lista->tamanhoLista == 1){
					///free(lista->inicioLista);
					free(lista->inicioLista);
					inicializaLista(lista);
					break;
				}

				if (lista->inicioLista == conjunto_Atual){
					lista->inicioLista = conjunto_Atual->Prox;
					lista->inicioLista->Prev = NULL;
					free(conjunto_Atual);
					lista->tamanhoLista--;
					ExibirLista(lista);
					break;
				}

				if(lista->fimLista == conjunto_Atual){
					lista->fimLista = conjunto_Atual->Prev;
					lista->fimLista->Prox = NULL;
					free(conjunto_Atual);
					lista->tamanhoLista--;
					ExibirLista(lista);
					break;
				}

				conjunto_Anterior->Prox = conjunto_Atual->Prox;
				conjunto_Atual->Prox->Prev = conjunto_Anterior;

				free(conjunto_Atual);
				lista->tamanhoLista--;
				ExibirLista(lista);
				break;

			}
			conjunto_Anterior = conjunto_Atual;
		}
	}else{
		printf("\n Nao ha nada para excluir! \n");
	}
}

void ExibirUniao(Lista * lista){
	Conjunto * conjunto_Atual;
	Conjunto * conjunto_Uniao;

	conjunto_Uniao =  (Conjunto*) malloc(sizeof(Conjunto));

	inicializaConjunto(conjunto_Uniao);
	Elemento * elemento_Atual;

	if(lista->tamanhoLista > 0){
		for (conjunto_Atual = lista->inicioLista; conjunto_Atual != NULL; conjunto_Atual = conjunto_Atual->Prox){
			for(elemento_Atual = conjunto_Atual->inicio;elemento_Atual != NULL; elemento_Atual = elemento_Atual->Prox){
				AdicionarElemento(conjunto_Uniao,elemento_Atual->info);
			}
		}
	}

	ExibirConjunto(conjunto_Uniao);
	free(conjunto_Uniao);
}

void ComparaDoisConjuntos(Conjunto * conjunto_A, Conjunto * conjunto_B, Conjunto * conjunto_Parcial){

	Elemento * elemento_A;
	Elemento * elemento_B;

	for(elemento_A = conjunto_A->inicio; elemento_A != NULL; elemento_A = elemento_A->Prox){
		for(elemento_B = conjunto_B->inicio;elemento_B != NULL;elemento_B = elemento_B->Prox){
			if(elemento_A->info == elemento_B->info){
				AdicionarElemento(conjunto_Parcial,elemento_B->info);
			}
		}
	}
}

void ExibirInterseccao(Lista * lista){

	Conjunto * conjunto_Parcial1     = (Conjunto *) malloc(sizeof(Conjunto));
	inicializaConjunto(conjunto_Parcial1);
	Conjunto * conjunto_A = malloc(sizeof(Conjunto));

	conjunto_A = lista->inicioLista;

	Conjunto * conjunto_B;

	switch(lista->tamanhoLista){
		case 0:
			printf("\n\n Adicione algum conjunto! \n\n");
			break;
		case 1:
			ExibirConjunto(lista->inicioLista);
			break;
		default:
			conjunto_B = lista->inicioLista->Prox;
			ComparaDoisConjuntos(conjunto_A, conjunto_B, conjunto_Parcial1);

			for(conjunto_B = conjunto_B->Prox;conjunto_B != NULL;conjunto_B = conjunto_B->Prox){
				conjunto_A = conjunto_Parcial1;
				conjunto_Parcial1 = malloc(sizeof(Conjunto));
				inicializaConjunto(conjunto_Parcial1);
				ComparaDoisConjuntos(conjunto_A,conjunto_B,conjunto_Parcial1);
				free(conjunto_A);
			}

			ExibirConjunto(conjunto_Parcial1);
			free(conjunto_Parcial1);
			break;
	}
}

void ExcluirElemento(Lista * lista,Conjunto * conjunto,int info){
	Elemento * elemento_Atual;
	Elemento * elemento_Anterior;

	if(conjunto->tamanho > 0){
		for(elemento_Atual = conjunto->inicio; elemento_Atual != NULL; elemento_Atual = elemento_Atual->Prox){
			if(elemento_Atual->info == info){
				if(elemento_Atual == conjunto->inicio){
					if (conjunto->tamanho == 1){
						ExcluirConjunto(lista,conjunto->id);
					}else{
						conjunto->inicio = elemento_Atual->Prox;
						conjunto->inicio->Prev = NULL;
						conjunto->tamanho--;
					}
					free(elemento_Atual);
					break;
				}

				if (elemento_Atual == conjunto->fim){
					conjunto->fim = elemento_Atual->Prev;
					conjunto->fim->Prox = NULL;
					free(elemento_Atual);
					conjunto->tamanho--;
					break;
				}

				elemento_Atual->Prox->Prev = elemento_Anterior;
				elemento_Anterior->Prox = elemento_Atual->Prox;
				free(elemento_Atual);
				conjunto->tamanho--;

				break;
			}
			elemento_Anterior = elemento_Atual;
		}
	}else{
		printf("Nao ha nada pra excluir!");
	}
}

void ExcluirElemento_Question(Lista * lista){
	Conjunto * conjunto_Atual;
	int id;
	int info;

	for(conjunto_Atual = lista->inicioLista;conjunto_Atual != NULL;conjunto_Atual = conjunto_Atual->Prox){
		ExibirConjunto(conjunto_Atual);
	}

	printf("\n\n Qual Conjunto deseja Excluir?\n\n");
	scanf("%d", &id);
	for(conjunto_Atual = lista->inicioLista; conjunto_Atual != NULL; conjunto_Atual = conjunto_Atual->Prox){
		if(id == conjunto_Atual->id){
			printf("\nQual elemento deseja excluir? ");
			scanf("%d",&info);
			ExcluirElemento(lista,conjunto_Atual,info);
		}
	}
}

void AlterarElemento(Lista * lista,Conjunto * conjunto,int info){
	// Essa Função altera o local de armazenamento do conjunto

	Elemento * elemento_Atual;
	Conjunto * conjunto_Auxiliar;
	Conjunto * conjunto_Anterior = conjunto->Prev;
	Conjunto * conjunto_Proximo  = conjunto->Prox;


	int NovoElemento = 0;

	for(elemento_Atual = conjunto->inicio; elemento_Atual !=NULL; elemento_Atual = elemento_Atual->Prox){
		if(info == elemento_Atual->info){
			printf("\n\nInforme o novo valor: ");
			scanf("%d",&NovoElemento);
			elemento_Atual->info = NovoElemento;
		}
	}

	conjunto_Auxiliar = malloc(sizeof(Conjunto));

	inicializaConjunto(conjunto_Auxiliar);

	conjunto_Auxiliar->id = conjunto->id;
	conjunto_Auxiliar->Prev = conjunto->Prev;
	conjunto_Auxiliar->Prox = conjunto->Prox;

	if (lista->inicioLista == conjunto){
		lista->inicioLista = conjunto_Auxiliar;
	}

	if (lista->fimLista == conjunto){
		lista->fimLista = conjunto_Auxiliar;
	}

	if (lista->inicioLista != conjunto_Auxiliar){
		conjunto_Anterior->Prox = conjunto_Auxiliar;
	}
	if (lista->fimLista != conjunto_Auxiliar){
		conjunto_Proximo->Prev = conjunto_Auxiliar;
	}

	for(elemento_Atual = conjunto->inicio; elemento_Atual !=NULL; elemento_Atual = elemento_Atual->Prox){
		AdicionarElemento(conjunto_Auxiliar,elemento_Atual->info);
	}
	ExibirConjunto(conjunto_Auxiliar);
	free(conjunto);
	conjunto = conjunto_Auxiliar;
}

void AlterarElemento_Question(Lista * lista){
	Conjunto * conjunto_Atual;
	int id;
	int info;

	if(lista->tamanhoLista > 0){

		ExibirLista(lista);

		if(lista->tamanhoLista > 1){

			printf("\n\n Qual Conjunto deseja Alterar?\n\n");
			scanf("%d", &id);
		}else{
			id = lista->inicioLista->id;
		}

		for(conjunto_Atual = lista->inicioLista; conjunto_Atual != NULL; conjunto_Atual = conjunto_Atual->Prox){
			if(id == conjunto_Atual->id){
				printf("\nQual elemento deseja Alterar? ");
				scanf("%d",&info);
				AlterarElemento(lista,conjunto_Atual,info);
			}
		}
	}
}

void ExibirDiferenca(Lista * lista){
    int Contador = 0;
	Elemento * elemento_Atual;
	Elemento * elemento_Teste;
	Conjunto * conjunto_Atual;
	Conjunto * conjunto_Teste;
	Conjunto * conjunto_Diferenca = (Conjunto *) malloc(sizeof(Conjunto));
	inicializaConjunto(conjunto_Diferenca);



	for(conjunto_Atual = lista->inicioLista; conjunto_Atual != NULL; conjunto_Atual = conjunto_Atual->Prox){
		for(elemento_Atual = conjunto_Atual->inicio; elemento_Atual != NULL; elemento_Atual = elemento_Atual->Prox){
			Contador = 0;
			for(conjunto_Teste = lista->inicioLista; conjunto_Teste != NULL; conjunto_Teste = conjunto_Teste->Prox){
				for(elemento_Teste = conjunto_Teste->inicio; elemento_Teste != NULL; elemento_Teste = elemento_Teste->Prox){
					if (elemento_Atual != elemento_Teste){
						if (elemento_Atual->info == elemento_Teste->info){
							Contador = Contador + 1;
						}
					}
				}
			}
			if (Contador == 0){
				AdicionarElemento(conjunto_Diferenca,elemento_Atual->info);
			}
		}
	}
	printf("\n\n Diferenca: \n\n");
	ExibirConjunto(conjunto_Diferenca);
	printf("\n\n\n");
	free(conjunto_Diferenca);
}

int main(){
	Lista * lista = malloc(sizeof(Lista));
	inicializaLista(lista);
	int id = 0;
	int opcao = 0;

	do{
		printf("\n======== Gerenciador de Conjuntos Numericos ========\n");

		printf("1 - Adicionar conjunto\n");
		printf("2 - Excluir conjunto\n"); // pensar uma forma de exibir o conjunto e excluir
		printf("3 - Excluir Elemento\n"); //Alterar conjunto (inserir ou remover elementos em um conjunto). 2 pt
		printf("4 - Alterar Elemento\n");
		printf("5 - Exibir Interseccao\n");//Exibir Intersecção 2 pt
		printf("6 - Exibir Uniao\n");
		printf("7 - Exibir Diferenca\n\n");

		printf("0 - Sair\n\nDigite a opcao desejada: ");

		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				id ++;
				AdicionarConjunto(lista,&id);
				break;
			case 2:
				ExcluirConjunto(lista,0);
				break;
			case 3:
				ExcluirElemento_Question(lista);
				break;
			case 4:
				AlterarElemento_Question(lista);
				break;
			case 5:
				ExibirInterseccao(lista);
				break;
			case 6:
				ExibirUniao(lista);
				break;
			case 7:
				ExibirDiferenca(lista);
				break;
			case 8:
				ExibirLista(lista);
				break;
		}
	} while (opcao!= 0);

	free(lista); //limpa a memória

	return 0;
}
