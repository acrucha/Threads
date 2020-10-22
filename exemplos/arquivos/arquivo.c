#include <stdio.h>
#include <stdlib.h>

// void testeArq(FILE ***arq , int i){
//     if (*(*(arq+i)) == NULL)
//     {
//         printf("Problemas na abertura do arquivo %d\n", i+1);
//     }else printf("Abri arquivo %d\n", i+1);
// }

int main(){
    int n=1;
    FILE arq[0]=fopen("a.txt", "rt");
    //FILE *aux=fopen("b.txt", "rt");
    int i = 0;
    //primeiro arquivo
    //*(arq+i) = fopen("a.txt", "rt");
    //testeArq(&arq, i);
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo %d\n", i+1);
    }else printf("Abri arquivo %d\n", i+1);
    //i++;
    //segundo arquivo
    //*(arq+i) = fopen("b.txt", "rt");
    if (aux == NULL)
    {
        printf("Problemas na abertura do arquivo %d\n", i+1);
    }else printf("Abri arquivo %d\n", i+1);
    //testeArq(&arq, i);

    return 0;

}