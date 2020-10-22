#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Viagens
{
    char linha;
    char texto[26];
} Viagens;

int main()
{
    int n = 2, sair = 0;
    int i;
    Viagens *arqViagens[n];

    char *nomesArq[n]; //vetor de nomes dos arquivos

    *(nomesArq + 0) = "g.txt";
    *(nomesArq + 1) = "f.txt";

    for (i = 0; i < n; i++)
    {
        FILE *arquivo;
        arquivo = fopen(nomesArq[i], "r");

        if (arquivo != NULL)
        {

            printf("\nAbri arquivo %s!!!\n\n", nomesArq[i]);

            fseek(arquivo, 0, SEEK_END); //move cursor pro fim do arquivo
            int qtdBytes = ftell(arquivo);
            int qtd = qtdBytes / sizeof(Viagens);

            arqViagens[i] = (Viagens *)malloc((qtd + 1) * sizeof(Viagens)); //alocando memória para o vetor de viagens
            if (arqViagens[i] == NULL)
                exit(-1);

            rewind(arquivo);
            int k = 0, qtdViagens = 0;
            char c, cadeia[2], texto[25], linhas[20]; //anda por cada caractere do arquivo
            //usar str cat pra pegar a primeira posição do array dps (se precisar)
            while ((c = fgetc(arquivo)) != EOF)
            {
                if (k % 28 == 0)
                { //quer dizer que eu cheguei em uma nova viagem! é 28 porque conta o os \n + os 25 caracteres do texto
                    linhas[qtdViagens] = c;
                    qtdViagens++; //sempre aumentando depois que chega uma nova linha
                }
                k++;// ta indo pelos caracteres, conta quantos tem
            }
            rewind(arquivo);
            qtdViagens = 0;
            while ((c = fgetc(arquivo)) != EOF){
                if(c == '\n')
                {
                    fread(texto, sizeof(char), 26, arquivo);
                    strcpy(arqViagens[i][qtdViagens].texto, texto);
                    qtdViagens++;
                }
            }
            k = 0;
            for(k = 0; k < qtdViagens; k++){
                arqViagens[i][k].linha = linhas[k];
                printf("%c\n", arqViagens[i][k].linha);
                printf("%s", arqViagens[i][k].texto);
            }
        }
        fclose(arquivo);
    }

    for (i = 0; i < n; i++)
    {
        free(arqViagens[i]);
    }

    return 0;
}
