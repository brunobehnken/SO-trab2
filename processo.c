#include <stdlib.h>
#include <stdio.h>
#include "processo.h"

PROCESSO* criaProcesso(int pid, int numSeg, int* tamanhos) {
    int i;

    PROCESSO *temp;
    if (!(temp = malloc(sizeof(PROCESSO))))
    {
        printf("funcao criaProcesso: Erro ao alocar memoria do temp com malloc\n");
        exit(-1);
    }
    temp->pid = pid;
    temp->numSeg = numSeg;
    if (!(temp->segTable = calloc(numSeg,sizeof(LINHA))))
    {
        printf("funcao criaProcesso: Erro ao alocar memoria do temp->segTable com calloc\n");
        exit(-1);
    }
    for (i = 0; i < numSeg; ++i)
    {
        temp->segTable[i].tamanho = tamanhos[i];
    }
    return temp;
}
