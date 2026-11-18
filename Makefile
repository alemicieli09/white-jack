# Compilatore da usare
CC = clang

# Opzioni di compilazione: tutti gli avvisi attivi
CFLAGS = -Wall -Wextra

# Elenco dei file oggetto che compongono il programma
OBJ = main.o carte.o mano.o grafica.o menu.o stats.o obiettivi.o

# Obiettivo principale: il programma si costruisce unendo i file .o (il linker)
whitejack: $(OBJ)
	$(CC) -o whitejack $(OBJ)

# main.o dipende da main.c e dagli header che include: se uno cambia, viene ricompilato
main.o: main.c carte.h mano.h grafica.h menu.h stats.h obiettivi.h
	$(CC) $(CFLAGS) -c main.c

# carte.o dipende da carte.c e dal suo header
carte.o: carte.c carte.h
	$(CC) $(CFLAGS) -c carte.c

# mano.o dipende da mano.c e dagli header che usa
mano.o: mano.c mano.h carte.h
	$(CC) $(CFLAGS) -c mano.c

# grafica.o dipende da grafica.c e dagli header che usa
grafica.o: grafica.c grafica.h mano.h carte.h
	$(CC) $(CFLAGS) -c grafica.c

# menu.o dipende da menu.c e dagli header che usa
menu.o: menu.c menu.h grafica.h mano.h carte.h
	$(CC) $(CFLAGS) -c menu.c

# stats.o dipende da stats.c e dagli header che usa
stats.o: stats.c stats.h grafica.h mano.h carte.h
	$(CC) $(CFLAGS) -c stats.c

# obiettivi.o dipende da obiettivi.c e dagli header che usa
obiettivi.o: obiettivi.c obiettivi.h stats.h grafica.h
	$(CC) $(CFLAGS) -c obiettivi.c

# Obiettivo di pulizia: cancella i file generati (-f: nessun errore se non esistono)
clean:
	rm -f $(OBJ) whitejack

# clean non è un file ma un comando
.PHONY: clean
