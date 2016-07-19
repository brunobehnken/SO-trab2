#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "memoria.h"
#include "segmento.h"

int main(int argc, char *argv[])
{
    int tamMemo;
    ESPACOLIVRE *MPLivre;

    if (argc != 2)
    {
        comoUsar(argv[0], "tamanho_da_memoria");
    }

    sscanf(argv[1], "%d", &tamMemo);
    noCabeca = MPLivre = malloc(sizeof(ESPACOLIVRE));
    noCabeca->inicio = 0;
    noCabeca->fim = tamMemo;
    printaEspacosLivres();

    printf("Segmento de tamanho 25 entra.\n");
    alocarSegmento(25);
    printaEspacosLivres();

    printf("Segmento de tamanho 13 entra.\n");
    alocarSegmento(13);
    printaEspacosLivres();

    printf("Segmento de tamanho 7 entra.\n");
    alocarSegmento(7);
    printaEspacosLivres();

    printf("Segmento de tamanho 10 entra.\n");
    alocarSegmento(10);
    printaEspacosLivres();

    printf("Segmento de tamanho 30 entra.\n");
    alocarSegmento(30);
    printaEspacosLivres();

    printf("Segmento de base 25, tamanho 13\n");
    freeSegmento(25, 13);
    printaEspacosLivres();

    printf("Segmento de base 45, tamanho 10\n");
    freeSegmento(45, 10);
    printaEspacosLivres();

    printf("Segmento de tamanho 11 entra.\n");
    alocarSegmento(11);
    printaEspacosLivres();

    printf("Segmento de tamanho 4 entra.\n");
    alocarSegmento(4);
    printaEspacosLivres();

    return 0;
}