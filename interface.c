#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void comoUsar (char* progName, char* argumentos)
{
    fprintf(stderr, "como usar: %s %s\n", progName, argumentos);
    exit(0);
}

void menuPrincipal () {
    
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

void testaAlocacaoDeSegmentosNaMemoria () {
    int tamSegmento = 0, keepRunning = 1;
    char resposta;

    while (keepRunning) {
        printf("Digite um valor inteiro maior que zero para o tamanho do segmento que deseja alocar: ");
        scanf("%d", &tamSegmento);

        while (!(tamSegmento > 0)) {
            printf("\n\t>> Valor invalido!!! <<\n\nDigite um valor inteiro maior que zero para o tamanho do segmento que deseja alocar: ");
            scanf("%d", &tamSegmento);
        }

        printf("Segmento de tamanho %d entra.\n", tamSegmento);
        alocarSegmento(tamSegmento);
        printaEspacosLivres();
        printf("Deseja alocar outro segmento? (y/n) \n");
        scanf(" %c", &resposta);
        if (!(resposta == 'Y' || resposta == 'y'))
        {
            printf("See ya~\n");
            keepRunning = 0;
        }
    }
}