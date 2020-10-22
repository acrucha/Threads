#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char cidades[146][12] = {
    "Abreu e Lima",
    "Afranio",
    "Agrestina",
    "Agua Preta",
    "Aguas Belas",
    "Alagoinha",
    "Alianca",
    "Altinho",
    "Amaraji",
    "Angelim",
    "Araçoiaba",
    "Araripina",
    "Arcoverde",
    "Barreiros",
    "Belo Jardim",
    "Betania",
    "Bezerros",
    "Bodoco",
    "Bom Conselho",
    "Bom Jardim",
    "Bonito",
    "Brejao",
    "Brejinho",
    "Buenos Aires",
    "Buique",
    "Cabrobo",
    "Cachoeirinha",
    "Caetes",
    "Calcado",
    "Calumbi",
    "Camaragibe",
    "Camutanga",
    "Canhotinho",
    "Capoeiras",
    "Carnaiba",
    "Carpina",
    "Caruaru",
    "Casinhas",
    "Catende",
    "Cedro",
    "Cha Grande",
    "Condado",
    "Correntes",
    "Cortes",
    "Cumaru",
    "Cupira",
    "Custodia",
    "Dormentes",
    "Escada",
    "Exu",
    "Feira Nova",
    "Ferreiros",
    "Flores",
    "Floresta",
    "Gameleira",
    "Garanhuns",
    "Goiana",
    "Granito",
    "Gravata",
    "Iati",
    "Ibimirim",
    "Ibirajuba",
    "Igarassu",
    "Iguaraci",
    "Inaja",
    "Ingazeira",
    "Ipojuca",
    "Ipubi",
    "Itacuruba",
    "Itaiba",
    "Itamaraca",
    "Itambe",
    "Itapetim",
    "Itapissuma",
    "Itaquitinga",
    "Jaqueira",
    "Jatauba",
    "Jatoba",
    "Joao Alfredo",
    "Jucati",
    "Jupi",
    "Jurema",
    "Lagoa Grande",
    "Lajedo",
    "Limoeiro",
    "Macaparana",
    "Machados",
    "Manari",
    "Maraial",
    "Mirandiba",
    "Moreilandia",
    "Moreno",
    "Olinda",
    "Orobo",
    "Oroco",
    "Ouricuri",
    "Palmares",
    "Palmeirina",
    "Panelas",
    "Paranatama",
    "Parnamirim",
    "Passira",
    "Paudalho",
    "Paulista",
    "Pedra",
    "Pesqueira",
    "Petrolandia",
    "Petrolina",
    "Pocao",
    "Pombos",
    "Primavera",
    "Quipapa",
    "Quixaba",
    "Recife",
    "Ribeirao",
    "Rio Formoso",
    "Saire",
    "Salgadinho",
    "Salgueiro",
    "Saloa",
    "Sanharo",
    "Santa Cruz",
    "Sao Caitano",
    "Sao Joao",
    "Serrita",
    "Sertania",
    "Sirinhaem",
    "Solidao",
    "Surubim",
    "Tabira",
    "Tacaimbo",
    "Tacaratu",
    "Tamandare",
    "Terezinha",
    "Terra Nova",
    "Timbauba",
    "Toritama",
    "Tracunhaem",
    "Trindade",
    "Triunfo",
    "Tupanatinga",
    "Tuparetama",
    "Venturosa",
    "Verdejante",
    "Vertentes",
    "Vicencia"
};

int main(){

    srand(time(NULL));
    int i = 0, randHora = 6;
    int letras[3];
    for (i = 0; i < 20; i++)
    {
        printf("%d\n", rand() % 10); //gera linha
        if(i % 3 == 0) randHora++;
        int hora, minuto;
        hora = randHora + rand() % randHora;
        minuto = (rand() % 50);
        while(minuto % 5 != 0){
            minuto = (rand() % 50);
        } 
        int code = 100 + (rand() % 899); //gera codigo

        for(int j = 0; j < 3; j++) {  //gera letras
            letras[j] = 65 + (rand() % 25);
            printf("%c", letras[j]);
        }

        int city = rand() % 145;     //gera cidades
        printf("%d %s", code, cidades[city]);
        int space;
        space = 12 - strlen(cidades[city]);
        
        for(int j = 0; j < space; j++){
            printf(" ");
        }
        if(hora < 10 && minuto < 10) {
            printf(" 0%d:", hora);
            printf("0%d\n", minuto);
        }else if(minuto < 10 || hora < 10){
            if(minuto < 10)
                printf(" %d:0%d\n", minuto);
            else
                printf(" 0%d:%d\n", hora, minuto);
        }else{
            printf(" %d:%d\n", hora, minuto);
        }
    }

    return 0;
}