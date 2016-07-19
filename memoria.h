#ifndef MEMORIA_H
#define MEMORIA_H

typedef struct _ESPACOLIVRE
{
    int inicio, fim;
    struct _ESPACOLIVRE *prox;
} ESPACOLIVRE;

ESPACOLIVRE *noCabeca;

void alocarSegmento (int tam);
ESPACOLIVRE *buscaEspacoLivre (int tam, ESPACOLIVRE *noAtual);
void freeSegmento (int base, int tam);
void liberaMemoria (ESPACOLIVRE *noLiberto);

#endif