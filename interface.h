#ifndef INTERFACE_H
#define INTERFACE_H

#include "memoria.h"

void comoUsar (char* progName, char* argumentos);
void menuPrincipal ();
void menuInsereProc();
void menuRetiraProc();
void printaProcessos();
void printaEspacosLivres ();
void testaAlocacaoDeSegmentosNaMemoria ();

#endif