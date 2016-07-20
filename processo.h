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

PROCESSO *listaProc;

PROCESSO* criaProcesso(int pid, int numSeg, int* tamanhos);
void insereProcesso(PROCESSO *processo);
void retiraProcesso(int pid);
int tamanhoListaProc(PROCESSO* vetor);

#endif