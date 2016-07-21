#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "segmento.h"
#include "processo.h"

void alocarSegmento (int tam, int pid, int numSeg) {
    int i;
    ESPACOLIVRE *noAtual = noCabeca;
    ESPACOLIVRE *noAnt = NULL;
    ESPACOLIVRE *noProx;

    ESPACOLIVRE *match = buscaEspacoLivre(tam, pid, numSeg, noAtual);
    // marcar na tabela de segmentos que o segmento foi alocado
    for (i = 0; i < tamListaProc; ++i)
    {
        if (listaProc[i].pid == pid) {
            listaProc[i].segTable[numSeg].bitPresenca = 1;
            listaProc[i].segTable[numSeg].base = match->inicio;
            listaProc[i].segTable[numSeg].tamanho = tam;

            break;
        }
    }
    match->inicio += tam;

    if (match->inicio == match->fim && match->inicio != tamanhoDaMemoria)
    {
        noAtual = noCabeca;
        noProx = noAtual->prox;
        while (noAtual) {
            if (noAtual->inicio == noAtual->fim)
            {
                free(noAtual);
                if (noAnt)
                {
                    noAnt->prox = noProx;
                } else {
                    noAtual = noCabeca = noProx;
                }
                break;
            }

            noAnt = noAtual;
            noAtual = noAtual->prox;
            if (noAtual)
            {
                noProx = noAtual->prox;
            } else {
                noProx = NULL;
            }
        }
    }
    insereSegmentoAlocado(criaSegmentoAlocado(pid, numSeg));
}

ESPACOLIVRE *buscaEspacoLivre (int tam, int pid, int numSeg, ESPACOLIVRE *noAtual) {
    int i, indice, segOut, pidVelho;
    SEGMENTOALOCADO *velho;
    if (!noAtual) //memoria cheia
    {
        // chama algoritmo de realocacao
        velho = escolheLRU();
        pidVelho = velho->pidProcesso;

        segOut = desalocaSegmento(velho); //dizendo q segmento nao ta mais na memoria. Retorna o segmento q saiu.

        for (i = 0; i < tamListaProc; ++i){
            if (listaProc[i].pid == pidVelho) {
                indice = i;
                break;
            }
        }

        freeSegmento(listaProc[indice].segTable[segOut].base , listaProc[indice].segTable[segOut].tamanho); //liberando memoria

        listaProc[indice].segTable[segOut].bitPresenca = 0;
        noAtual = noCabeca; //Comecar de novo.
        return buscaEspacoLivre(tam, pid, numSeg, noAtual);
    } else {
        if ((noAtual->fim - noAtual->inicio) >= tam) {
            return noAtual;
        } else {
            return buscaEspacoLivre(tam, pid, numSeg, noAtual->prox);
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
            if (noLiberto->fim == noAtual->inicio) // checando se ha colisao entre o fim do liberto e o inicio do atual
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
                    if (noCabeca->inicio == tamanhoDaMemoria)
                    {
                        free(noCabeca);
                        noLiberto->prox = NULL;
                    }
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
