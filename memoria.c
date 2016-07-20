#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "segmento.h"

void alocarSegmento (int tam) {
    ESPACOLIVRE *match = buscaEspacoLivre(tam, noCabeca);
    match->inicio += tam;
    // marcar na tabela de segmentos que o segmento foi alocado
}

ESPACOLIVRE *buscaEspacoLivre (int tam, ESPACOLIVRE *noAtual) {
    if (!noAtual) //memoria cheia
    {
        // chama algoritmo de realocacao

        return NULL;
    } else {
        if ((noAtual->fim - noAtual->inicio) >= tam) {
            return noAtual;
        } else {
            return buscaEspacoLivre(tam, noAtual->prox);
        }
    }
}

void freeSegmento (int base, int tam) {
    ESPACOLIVRE *noLiberto;
    if (!(noLiberto = calloc(tam, sizeof(ESPACOLIVRE))))
    {
        printf("funcao freeSegmento: Erro ao alocar memoria do noLiberto com calloc\n");
        exit(-1);
    }
    noLiberto->inicio = base;
    noLiberto->fim = base + tam;
    liberaMemoria(noLiberto);
}

void liberaMemoria (ESPACOLIVRE *noLiberto) {
    ESPACOLIVRE *noAnterior = NULL;
    ESPACOLIVRE *noAtual = noCabeca;
    ESPACOLIVRE *noProx;

    while (noAtual) {
        noProx = noAtual->prox; // atualizando o noProx
        if (noAtual->inicio > noLiberto->inicio) // checando se noLiberto estah a esquerda do noAtual
        {
            if (noLiberto->fim == noAtual->inicio) // checando se ha colisao entre o fim do liberto e o incio do atual
            {
                // mergeando nohs
                noAtual->inicio = noLiberto->inicio;
                free(noLiberto);
                break;
            } else { // naum ha colisao
                // adiciona noLiberto como novo noh na lista encadeada de espacos livres
                noLiberto->prox = noAtual;
                if (noAnterior)
                {
                    noAnterior->prox = noLiberto;
                    break;
                } else {
                    noCabeca = noLiberto;
                    break;
                }
            }
        } else { // noLiberto estah a direita de noAtual
            if (noLiberto->inicio == noAtual->fim) // checando colisao entre o fim do atual e o inicio do liberto
            {
                // mergeando nohs
                noAtual->fim = noLiberto->fim;
                free(noLiberto);
                if (noProx && noAtual->fim == noProx->inicio) // checando se ha colisao entre fim de noLiberto e inicio de noProx
                {
                    // mergeando o noAtual ao no Liberto e ao noProx nessa ordem
                    noAtual->fim = noProx->fim;
                    noAtual->prox = noProx->prox;
                    free(noProx);
                }
                break;
            } else { // noLiberto estah a direita do noAtual sem colisao
                if (noProx) // checando se existe um proximo no para continuar iteracao
                {
                    noAnterior = noAtual;
                    noAtual = noProx;
                } else { // acabou a lista, noliberto eh o ultimo no. Atualiza ponteiros e termina iteracao
                    noLiberto->prox = NULL;
                    noAtual->prox = noLiberto;
                    break;
                }
            }
        }
    }
}