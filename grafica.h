#ifndef GRAFICA_H                                               // include guard
#define GRAFICA_H                                               // definisce GRAFICA_H

#include "mano.h"                                               // serve il tipo Mano (che include a sua volta Carta)

#define ROSSO  "\033[31m"                                       // codice ANSI: da qui in poi il testo è rosso
#define VERDE  "\033[32m"                                       // codice ANSI: testo verde
#define GIALLO "\033[33m"                                       // codice ANSI: testo giallo
#define RESET  "\033[0m"                                        // codice ANSI: torna ai colori normali

void mostra_mano(const char *titolo, struct Mano m, int nascondi_seconda);   // disegna una mano; se nascondi_seconda è 1 la seconda carta resta coperta

#endif                                                          // fine dell'include guard
