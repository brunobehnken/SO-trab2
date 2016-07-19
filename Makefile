all:PRINCIPAL
	gcc principal.c interface.o memoria.o processo.o segmento.o -o principal -Wall
PRINCIPAL:
	gcc -c interface.c -Wall
	gcc -c memoria.c -Wall
	gcc -c processo.c -Wall
	gcc -c segmento.c -Wall