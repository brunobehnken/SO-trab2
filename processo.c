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

int tamanhoListaProc(PROCESSO* vetor) {
    int d = sizeof(vetor)/sizeof(PROCESSO);
    printf("%d\n", d);
    return d;
}

void insereProcesso(PROCESSO *processo) {
    int tamAntigo = tamanhoListaProc(listaProc);
    listaProc = realloc(listaProc, (tamAntigo + 1) * sizeof(PROCESSO));
    if (!listaProc)
    {
        printf("funcao criaProcesso: Erro ao alocar memoria do temp->segTable com calloc\n");
        exit(-1);
    }
    listaProc[tamAntigo] = *processo;
}

void retiraProcesso(int pid){
    int i;
    for (i = 0; i < tamanhoListaProc(listaProc); ++i)
    {
        if (listaProc[i].pid == pid){
            free(listaProc[i].segTable);
            free(&listaProc[i]);
            return;
        }
    }
    printf("Funcao retiraProcesso: PID %d nao encontrado\n", pid);
}