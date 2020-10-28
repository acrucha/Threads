#include <stdio.h>
#include <stdlib.h>

// int main()
// {
//     //isso aqui é só um exemplo de teste:
//     system("clear");
//     for (int i = 0; i < 8; i++)
//     {
//         printf("\033[%d;0H", i);
//         int b = 40+i;
//         //if (b > 8) b = b-i;
//         printf("\033[22;%dm", b);
//         printf ("BLA BLA BLA\n");
//     }
//     sleep(4);
//     for (int i = 0; i < 8; i++)
//     {
//         printf("\033[%d;0H", i);
//         int b = 40+i;
//         //if (b > 8) b = b-i;
//         printf("\033[22;%dm", b);
//         printf ("BLU BLU BLU\n");
//     }
    
    // vc tem q botar \033 no printf
    //
    // 1. pra escolher a linha:
    //     1.1 [x;yH --> sendo x a linha e y a coluna no terminal
    //     1.2 pra nao ficar esquisito, antes de começar os prints é bom dar um system("clear") pra tela ficar limpa
    // 2. pra escolher a cor da letra:
    //     2.1 [Y;Xm --> sendo x um número entre 30 e 37 ou de 90 a 97, pra resetar pra configuração original X = 0
    //     2.2 Y é o modo, depende do tipo de letra, se for o normalzinho é 22
    //         Black:[Y;30m
    //         Red:[Y;31m
    //         Green:[Y;32m
    //         Yellow:[Y;33m
    //         Blue:[Y;34m
    //         Magenta:[Y;35m
    //         Cyan:[Y;36m
    //         White:[Y;37m
    //         Reset:[Y;0m
    // 3. pra escolher a cor do fundo:
    //     mesma coisa da letra, sendo que X está entre 40 e 47 ou 100 e 107

    // achei esse codigo na internet ele mostra tudo e ainda mostra letra em negrito, italico etc
 
    void table(const char *title, const char *mode)
    {
        int f, b;
        printf("\n\033[1m%s\033[m\n bg\t fg\n", title);
        for (b = 40; b <= 107; b++) {
            if (b == 48) b = 100;
            printf("%3d\t\033[%s%dm", b, mode, b);
            for (f = 30; f <= 97; f++) {
                if (f == 38) f = 90;
                printf("\033[%dm%3d ", f, f);
            }
            puts("\033[m");
        }
    }
    
    int main(void)
    {
        int fg, bg, blink, inverse;
    
        table("normal ( ESC[22m or ESC[m )", "22;");
        table("bold ( ESC[1m )", "1;");
        table("faint ( ESC[2m ), not well supported", "2;");
        table("italic ( ESC[3m ), not well supported", "3;");
        table("underline ( ESC[4m ), support varies", "4;");
        table("blink ( ESC[5m )", "5;");
        table("inverted ( ESC[7m )", "7;");
        return 0;
    }


//     return 0;
// }
