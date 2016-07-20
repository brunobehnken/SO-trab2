#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "processo.h"

void comoUsar (char* progName, char* argumentos)
{
    fprintf(stderr, "como usar: %s %s\n", progName, argumentos);
    exit(0);
}

void menuPrincipal () {
    int option = 10;

    printf("\tBem-vindo, usuario!\n");
    printf("Digite 1 para inserir um processo;\nDigite 2 para finalizar um processo;\nDigite 3 para acessar endereco real\nDigite 0 para sair;\n");
    while (option != 0) {
        scanf("%d", &option);
        switch (option) {
            case 0:
                printf("Bye-bye~\n");
                break;
            case 1:
                menuInsereProc();
                break;
            case 2:
                menuRetiraProc();
                break;
            case 3:
                // acessa um endereco real segundo uma base de segmento e um offset
                break;
            default:
                printf("Opcao invalida!\nDigite 1 para inserir um processo;\nDigite 2 para finalizar um processo;\nDigite 3 para acessar endereco real\nDigite 0 para sair;\n");
                break;
        }
    }
}

void menuInsereProc() {
    int pid, numSeg, *tamanhos, i;

    printf("Digite o PID e a quantidade de segmentos: ");
    scanf(" %d %d", &pid, &numSeg);
    while (!(pid > 0 || numSeg > 0))
    {
        printf("\t>> Valor inválido! <<\nDigite o PID e a quantidade de segmentos: ");
        scanf(" %d %d", &pid, &numSeg);
    }
    tamanhos = calloc(numSeg, sizeof(int));

    for (i = 0; i < numSeg; ++i)
    {
        printf("Digite o tamanho do segmento %d: ", i);
        scanf(" %d", &tamanhos[i]);
    }

    insereProcesso(criaProcesso(pid, numSeg, tamanhos));
    printaProcessos();
}

void menuRetiraProc() {
    int pid, i;

    printf("Digite um dos PIDs listados a seguir para finaliza-lo:\n");
    printaProcessos();
    scanf(" %d", &pid);
    while(!(pid >= 0)) {
        printf("Valor de PID invalido, escolha um valor maior que zero: ");
        scanf(" %d", &pid);
    }

    for (i = 0; i < tamListaProc; ++i)
    {
        if (listaProc[i].pid == pid)
        {
            retiraProcesso(pid);
            printf(">> Processo %d retirado com sucesso!\n", pid);
            printaProcessos();
            return;
        }
    }
    printf("Este PID ainda nao foi inserido! Voce pode inseri-lo seguindo as instrucoes da opcao 1.\n");
}

void menuAcessaSegmento() {

}

void printaProcessos() {
    int i, j;
    printf("Processos no sistema:\n");
    for (i = 0; i < tamListaProc; ++i)
    {
        printf(">> PID: %d; SEGMENTOS:\n\t", listaProc[i].pid);
        for (j = 0; j < listaProc[i].numSeg; ++j)
        {
            printf("%d ", listaProc[i].segTable[j].tamanho);
        }
        printf("\n");
    }
}

void printaEspacosLivres () {
    ESPACOLIVRE *noAtual = noCabeca;
    printf("(%d, %d)", noAtual->inicio, noAtual->fim);
    noAtual = noAtual->prox;

    while (noAtual) {
        printf("->(%d, %d)", noAtual->inicio, noAtual->fim);
        noAtual = noAtual->prox;
    }
    printf("\n");
}

void testaAlocacaoDeSegmentosNaMemoria () {
    int tamSegmento = 0, keepRunning = 1;
    char resposta;

    while (keepRunning) {
        printf("Digite um valor inteiro maior que zero para o tamanho do segmento que deseja alocar: ");
        scanf("%d", &tamSegmento);

        while (!(tamSegmento > 0)) {
            printf("\n\t>> Valor invalido!!! <<\n\nDigite um valor inteiro maior que zero para o tamanho do segmento que deseja alocar: ");
            scanf("%d", &tamSegmento);
        }

        printf("Segmento de tamanho %d entra.\n", tamSegmento);
        alocarSegmento(tamSegmento);
        printaEspacosLivres();
        printf("Deseja alocar outro segmento? (y/n) ");
        scanf(" %c", &resposta);
        if (!(resposta == 'Y' || resposta == 'y'))
        {
            printf("See ya~\n");
            keepRunning = 0;
        }
    }
}