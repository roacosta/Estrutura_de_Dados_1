#include <stdio.h>


int main(){
    int i,j,n,menor,ValorTemp;
    printf("Tamanho do Vetor: ");
    scanf("%d", &n);

    int Vetor[n];

    for(i = 0; i < n;i++)
        scanf("%d",&Vetor[i]);


    for(i = 0; i < n; i++){
        menor = i;
        for(j = i+1; j < n; j++){
            if (Vetor[j] < Vetor[menor]){
                menor = j;
            }
        }
        if (i != menor){
            ValorTemp = Vetor[i];
            Vetor[i] = Vetor[menor];
            Vetor[menor] = ValorTemp;
        }
    }
    printf("\n");
    for(i = 0; i < n;i++)
        printf("%d\n",Vetor[i]);

    return 0;
}
