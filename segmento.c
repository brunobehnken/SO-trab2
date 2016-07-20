#include <stdlib.h>
#include <stdio.h>
#include "segmento.h"

SEGMENTOALOCADO* criaSegmentoAlocado(int pidProcesso, int numSeg){
	SEGMENTOALOCADO *temp;
	if (!(temp = malloc(sizeof(SEGMENTOALOCADO))))
    {
        printf("funcao criaSegmentoAlocado: Erro ao alocar memoria do temp com malloc\n");
        exit(-1);
    }

    temp->pidProcesso = pidProcesso;
    temp->numSeg = numSeg;
    temp->idade = 0;
    temp->prox = NULL;
    return temp;
}

void insereSegmentoAlocado(SEGMENTOALOCADO *segmento) {
    // int tamAntigo = tamListaSeg;
    // printf("%d\n", tamListaSeg);
    listaSegAloc = realloc(listaSegAloc, ++tamListaSeg * sizeof(PROCESSO));
    if (!listaSegAloc)
    {
        printf("funcao insereSegmentoAlocado: Erro ao alocar memoria do listaSegAloc com realloc\n");
        exit(-1);
    }
    // listaSegAloc[tamAntigo] = *segmento;
}

void desalocaSegmento(SEGMENTOALOCADO *segmento) {

}