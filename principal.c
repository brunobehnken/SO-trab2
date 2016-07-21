#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "memoria.h"
#include "segmento.h"

int main(int argc, char *argv[])
{
    int tamMemo;
    ESPACOLIVRE *MPLivre;
    SEGMENTOALOCADO *cabecaSeg;

    if (argc != 2)
    {
        comoUsar(argv[0], "tamanho_da_memoria");
    }

    sscanf(argv[1], "%d", &tamMemo);
    tamanhoDaMemoria = tamMemo;
    noCabeca = MPLivre = malloc(sizeof(ESPACOLIVRE));
    noCabeca->inicio = 0;
    noCabeca->fim = tamMemo;
    cabecaSeg = criaSegmentoAlocado(0,0);
    inicioSegAloc = cabecaSeg;
    fimSegAloc = cabecaSeg;

    menuPrincipal();

    return 0;
}