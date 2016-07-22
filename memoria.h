#ifndef MEMORIA_H
#define MEMORIA_H

typedef struct _ESPACOLIVRE
{
    int inicio, fim;
    struct _ESPACOLIVRE *prox;
} ESPACOLIVRE;

ESPACOLIVRE *noCabeca;
int tamanhoDaMemoria;

void alocarSegmento (int tam, int pid, int numSeg);
ESPACOLIVRE *buscaEspacoLivre (int tam, int pid, int numSeg, ESPACOLIVRE *noAtual);
void freeSegmento (int base, int tam);
void liberaMemoria (ESPACOLIVRE *noLiberto);

#endif
