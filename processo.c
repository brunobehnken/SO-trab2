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
    if (!(temp->segTable = calloc(numSeg, sizeof(LINHA))))
    {
        printf("funcao criaProcesso: Erro ao alocar memoria do temp->segTable com calloc\n");
        exit(-1);
    }
    for (i = 0; i < numSeg; ++i)
    {
        temp->segTable[i].tamanho = tamanhos[i];
        temp->segTable[i].bitPresenca = 0;
    }
    return temp;
}

void insereProcesso(PROCESSO *processo) {
    int tamAntigo = tamListaProc;
    printf("%d\n", tamListaProc);
    listaProc = realloc(listaProc, ++tamListaProc * sizeof(PROCESSO));
    if (!listaProc)
    {
        printf("funcao criaProcesso: Erro ao alocar memoria do temp->segTable com calloc\n");
        exit(-1);
    }
    listaProc[tamAntigo] = *processo;
}

void retiraProcesso(int pid){
    int i;
    for (i = 0; i < tamListaProc; ++i)
    {
        if (listaProc[i].pid == pid){
            free(listaProc[i].segTable);
            free(&listaProc[i]);
            tamListaProc--;
            return;
        }
    }
    printf("Funcao retiraProcesso: PID %d nao encontrado\n", pid);
}