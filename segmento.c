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

	segmento->idade = 0;
}

int desalocaSegmento(SEGMENTOALOCADO *segmento) {
	int segOut = segmento->numSeg;

	segmento->prox->ant = segmento->ant;
	segmento->ant->prox = segmento->prox;
	free(segmento);

	return segOut;
}

SEGMENTOALOCADO *buscaSegmento(int pidProcesso){
	SEGMENTOALOCADO *atual = inicioSegAloc->prox;
	while(atual){
		if(atual->pidProcesso == pidProcesso){
			return atual;
		}
		atual = atual->prox;
	}
	return NULL;	
}
