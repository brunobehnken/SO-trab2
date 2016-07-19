#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void comoUsar (char* progName, char* argumentos)
{
    fprintf(stderr, "como usar: %s %s\n", progName, argumentos);
    exit(0);
}

void printaEspacosLivres () {
    ESPACOLIVRE *noAtual = noCabeca;
    printf("(%d, %d)", noAtual->inicio, noAtual->fim);
    noAtual = noAtual->prox;

    while (noAtual) {
        printf("->(%d, %d)", noAtual->inicio, noAtual->fim);
        noAtual = noAtual->prox;
    }
    printf("\n");
}