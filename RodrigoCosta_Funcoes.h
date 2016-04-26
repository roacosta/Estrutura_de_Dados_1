#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento{ //Estrutura para cada elemento do conjunto {1,2,3...}
	int info;
	struct Elemento * Prox;
	struct Elemento * Prev;
}Elemento;

typedef struct Conjunto{ //Estrutura para cada Conjunto 1{n1,n2,3...} 2{n1,n2,n3...}
	int tamanho;
	int id;
	struct Elemento * inicio;
	struct Elemento * fim;
	struct Conjunto * Prox;
	struct Conjunto * Prev;
}Conjunto;

typedef struct ListaDeConjunto{ //Estrutura para a Lista de Conjuntos
	int tamanhoLista;
	struct Conjunto * inicioLista;
	struct Conjunto * fimLista;
}Lista;

void inicializaConjunto		(Conjunto * conjunto); 	// Inicializa um conjunto novo
void inicializaLista		(Lista * lista); 			// Inicializa uma lista de conjuntos
void ExibirConjunto			(Conjunto *conjunto);
void ExibirLista			(Lista *lista);
void AdicionarElemento		(Conjunto *conjunto,int info);
void AdicionarConjunto		(Lista *lista,int * id);
void ExcluirConjunto		(Lista *lista,int opcao);
void ExibirUniao			(Lista * lista);
void ComparaDoisConjuntos	(Conjunto * conjunto_A,	Conjunto * conjunto_B, 	Conjunto * conjunto_Parcial);
void ExibirInterseccao		(Lista * lista);
void ExcluirElemento		(Lista * lista,	Conjunto * conjunto,int info);
void ExcluirElemento_Question(Lista * lista);
void AlterarElemento		(Lista * lista,	Conjunto * conjunto,int info);
void AlterarElemento_Question(Lista * lista);
void ExibirDiferenca		(Lista * lista);
int toupper(int c);

