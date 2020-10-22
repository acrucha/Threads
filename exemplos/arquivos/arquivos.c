#include <stdio.h>
#include <stdlib.h>

void testeArq(FILE ***arq , int i){
    if (*(*(arq+i)) == NULL)
    {
        printf("Problemas na abertura do arquivo %d\n", i+1);
    }else printf("Abri arquivo %d\n", i+1);
}

int main(){
    FILE **arq;

    int i = 0;
    //primeiro arquivo
    *(arq+i) = fopen("a.txt", "rt");
    //testeArq(&arq, i);
    if (*(arq+i) == NULL)
    {
        printf("Problemas na abertura do arquivo %d\n", i+1);
    }else printf("Abri arquivo %d\n", i+1);
    i++;
    //segundo arquivo
    *(arq+i) = fopen("b.txt", "rt");
    if (*(arq+i) == NULL)
    {
        printf("Problemas na abertura do arquivo %d\n", i+1);
    }else printf("Abri arquivo %d\n", i+1);

    return 0;
}