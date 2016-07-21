#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "processo.h"
#include "segmento.h"

void comoUsar (char* progName, char* argumentos)
{
    fprintf(stderr, "como usar: %s %s\n", progName, argumentos);
    exit(0);
}

void menuPrincipal () {
    int option = 10;

    printf("\tBem-vindo, usuario!\n");
    printf("Digite 1 para inserir um processo;\nDigite 2 para finalizar um processo;\nDigite 3 para acessar endereco real\nDigite 4 para ver os intervalos de espaco livre na memoria principal;\nDigite 5 para ver os Processos e seus segmentos;\nDigite 6 para ver as idades dos segmentos presentes na memoria;\nDigite 0 para sair;\n");
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
                menuAcessaSegmento();
                break;
            case 4:
                printaEspacosLivres();
                break;
            case 5:
                printaProcessos();
                break;
            case 6:
                printaIdadeSegmentos();
                break;
            default:
                printf("Opcao invalida!\nDigite 1 para inserir um processo;\nDigite 2 para finalizar um processo;\nDigite 3 para acessar endereco real;\nDigite 4 para ver os intervalos de espaco livre na memoria principal;\nDigite 5 para ver os Processos e seus segmentos;\nDigite 6 para ver as idades dos segmentos presentes na memoria;\nDigite 0 para sair;\n");
                break;
        }
    }
}

void menuInsereProc() {
    int pid, numSeg, *tamanhos, i, tempTamanho, ok;

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
		ok = 1;
        //scanf(" %d", &tamanhos[i]);
        while(ok){
			printf("Digite o tamanho do segmento %d: ", i);
			scanf(" %d", &tempTamanho);
			if(tempTamanho > tamanhoDaMemoria){
				printf("Tamanho dado eh maior que a Memoria Principal! Insira outro, por favor.\n");
			}
			else if(tempTamanho <= 0){
				printf("Tamanho dado eh menor ou igual a zero! Insira outro, por favor.\n");
			}
			else{
				ok = 0;
				tamanhos[i] = tempTamanho;
			}
		}
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
    int i, pid, segmento, indice, offset, teste = 0;

    printf("Escolha um dos PIDs listados a seguir:\n");
    printaProcessos();
    scanf(" %d", &pid);
    while(!(pid >= 0)) {
        printf("Valor de PID invalido, escolha um valor maior que zero: ");
        scanf(" %d", &pid);
    }

    while(1) {
        for (i = 0; i < tamListaProc; ++i)
        {
            if (listaProc[i].pid == pid)
            {
                teste = 1;
                break;
            }
        }
        if (teste)
        { // soh para sair do while se achar o pid
            break;
        }
        printf("Valor de PID invalido, escolha um dos valores listados:");
        printaProcessos();
        scanf(" %d", &pid);
    }

    printf("Escolha um segmento dentre os listados abaixo:\n");
    indice = printaSegmentos(pid);
    scanf(" %d", &segmento);
    while(!(segmento < listaProc[indice].numSeg)) {
        printf("Valor de segmento invalido, escolha um dos valores listados:");
        printaSegmentos(pid);
        scanf(" %d", &segmento);
    }

    printf("Digite o offset desejado [0, %d]: ", listaProc[indice].segTable[segmento].tamanho - 1);
    scanf(" %d", &offset);
    while(offset >= listaProc[indice].segTable[segmento].tamanho || offset < 0) {
        printf("\t>> Valor inválido! <<\nEscolha um offset dentro do intervalo [0, %d]: ", listaProc[indice].segTable[segmento].tamanho - 1);
        scanf(" %d", &offset);
    }

    // Aqui temos PID, segmento e offset definidos.
    switch(listaProc[indice].segTable[segmento].bitPresenca) {
        case 0:
            alocarSegmento(listaProc[indice].segTable[segmento].tamanho, pid, segmento);
        case 1:
            somaLRU(buscaSegmento(pid, segmento));
            break;
        default:
            printf("Valor de bit de presenca nao esperado! O gerenciador de memoria vai cometer suicidio!\n");
            exit(-1);
    }
    printf("Segmento %d do processo de PID %d em memoria;\nSeu endereco real eh: %d\nO endereco real da instrucao eh: %d\n", segmento, pid, listaProc[indice].segTable[segmento].base, listaProc[indice].segTable[segmento].base + offset);
}

int printaSegmentos(int pid) {
    int i, indice;

    for (i = 0; i < tamListaProc; ++i)
    {
        if (listaProc[i].pid == pid) {
            indice = i;
            break;
        }
    }

    for (i = 0; i < listaProc[indice].numSeg; ++i)
    {
        printf("Segmento %d: %d\n", i, listaProc[indice].segTable[i].tamanho);
    }
    return indice;
}

void printaIdadeSegmentos() {
    SEGMENTOALOCADO *segmentos = inicioSegAloc->prox;
    printf(">> Numero do segmento; PID; idade:\n");
    while(segmentos) {
        printf("\t%d; %d; %d\n", segmentos->numSeg, segmentos->pidProcesso, segmentos->idade);
        segmentos = segmentos->prox;
    }
}

void printaProcessos() {
    int i, j;
    printf("Processos no sistema:\n");
    for (i = 0; i < tamListaProc; ++i)
    {
        printf(">> PID: %d; SEGMENTOS (bit de presenca: tamanho):\n\t", listaProc[i].pid);
        for (j = 0; j < listaProc[i].numSeg; ++j)
        {
            printf("%d:%d ", listaProc[i].segTable[j].bitPresenca, listaProc[i].segTable[j].tamanho);
        }
        printf("\n");
    }
}

void printaEspacosLivres () {
    ESPACOLIVRE *noAtual = noCabeca;
    
    //Teste de print especial para "memoria cheia"
    if(noAtual->inicio == tamanhoDaMemoria){
		printf("Espacos livres: Memoria Cheia\n");
		return;
	}
    
    printf("Espacos livres: (%d, %d)", noAtual->inicio, noAtual->fim);
    noAtual = noAtual->prox;

    while (noAtual) {
        printf("->(%d, %d)", noAtual->inicio, noAtual->fim);
        noAtual = noAtual->prox;
    }
    printf("\n");
}
