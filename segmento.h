#ifndef SEGMENTO_H
#define SEGMENTO_H

typedef struct _SEGMENTOALOCADO 
{
	int pidProcesso;
	int numSeg;
	int idade;
    struct _SEGMENTOALOCADO *prox;
} SEGMENTOALOCADO;

SEGMENTOALOCADO *listaSegAloc;

int tamListaSeg;

SEGMENTOALOCADO* criaSegmentoAlocado(int pidProcesso, int numSeg);
void insereSegmentoAlocado(SEGMENTOALOCADO *segmento);

#endif