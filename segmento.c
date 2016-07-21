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
    temp->ant = NULL;
    return temp;
}

void insereSegmentoAlocado(SEGMENTOALOCADO *segmento) {
	segmento->ant = fimSegAloc;
	fimSegAloc->prox = segmento;
	fimSegAloc = fimSegAloc->prox;
}

SEGMENTOALOCADO *escolheLRU() {
	int maxIdade = 0;
	SEGMENTOALOCADO *atual;
	SEGMENTOALOCADO *ptrRet;

	atual = inicioSegAloc->prox;
	ptrRet = atual;

	while (atual) {
		if (atual->idade > maxIdade) {
			maxIdade = atual->idade;
			ptrRet = atual;
		}
		atual = atual->prox;
	}
	return ptrRet;
}

void somaLRU(SEGMENTOALOCADO *segmento) {
	SEGMENTOALOCADO *atual;

	atual = inicioSegAloc->prox;

	while (atual) {
		atual->idade++;
		atual = atual->prox;
	}

	atual = inicioSegAloc->prox;
	segmento->idade = 0;
}

void desalocaSegmento(SEGMENTOALOCADO *segmento) {
	segmento->prox->ant = segmento->ant;
	segmento->ant->prox = segmento->prox;
	free(segmento);
}