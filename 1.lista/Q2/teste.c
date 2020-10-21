#include <stdio.h>
#include <stdlib.h>


int main()
{
    char a[5] = {"a.txt"};
    FILE *arquivo = fopen(R"(a)");
    int i, x;
    i = fscanf (arquivo, "%d", &x);
    printf("%d", x);
    return 0;
}