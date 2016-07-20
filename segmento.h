#ifndef SEGMENTO_H
#define SEGMENTO_H

typedef struct _SEGMENTOALOCADO 
{
	int pidProcesso;
	int numSeg;
	int idade;
} SEGMENTOALOCADO;

SEGMENTOALOCADO *listaSegAloc;

#endif