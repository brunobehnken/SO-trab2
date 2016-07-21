#ifndef SEGMENTO_H
#define SEGMENTO_H

typedef struct _SEGMENTOALOCADO 
{
	int pidProcesso;
	int numSeg;
	int idade;
    struct _SEGMENTOALOCADO *ant;
    struct _SEGMENTOALOCADO *prox;
} SEGMENTOALOCADO;

SEGMENTOALOCADO *inicioSegAloc;
SEGMENTOALOCADO *fimSegAloc;

SEGMENTOALOCADO* criaSegmentoAlocado(int pidProcesso, int numSeg);
void insereSegmentoAlocado(SEGMENTOALOCADO *segmento);
SEGMENTOALOCADO *escolheLRU();
void somaLRU(SEGMENTOALOCADO *segmento);
void desalocaSegmento(SEGMENTOALOCADO *segmento);

#endif