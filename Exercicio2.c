#include <stdlib.h>
#include <stdio.h>

// Rodrigo Almeida Costa

int* uniao(int *v1, int n1, int *v2, int n2){
	
	int i = 0,j = 0;
	int * v3 = (int*) calloc(n1 + n2, sizeof(int)) ;
	
	for(i = 0;i<= n1;i++){
		v3[j] = v1[i];
		j++;
	}
	j--;
	for(i = 0;i<(n2);i++){
		v3[j] = v2[i];
		j++;
	}
	return v3;
}

int main(){
	int n1,n2,i;
	printf("Tamanho do primeiro vetor: ");
	scanf("%d",&n1 );
	printf("Tamanho do segundo  vetor: ");
	scanf("%d",&n2 );
	
	int v1[n1], v2[n2];
	
	for(i = 0;i< n1;i++){
		scanf("%d",&v1[i]);
	}
	
	printf("\n inicio do segundo vetor\n");
	
	for(i = 0;i< n2;i++){
		scanf("%d",&v2[i]);
	}
	
	int *v3 =  uniao(v1,n1,v2,n2);
	
	for(i = 0;i<(n1+n2);i++){
		printf(" %d, ", v3[i]);
	}
	free(v3);
	v3 = NULL;	
	return 0;
}
