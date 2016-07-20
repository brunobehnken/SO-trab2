#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct _LINHA 
{
	int bitPresenca;
	int base;
	int tamanho;
} LINHA;


typedef struct _PROCESSO
{
	int pid;
	int numSeg;
	LINHA *segTable;
} PROCESSO;

void criaProcesso(int pid, int numSeg);
	
#endif