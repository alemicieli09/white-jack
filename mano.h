#ifndef MANO_H                                                  // include guard
#define MANO_H                                                  // definisce MANO_H

#include "carte.h"                                              // la mano contiene carte, quindi serve il tipo Carta

#define MAX_MANO 12                                             // massimo di carte in una mano

struct Mano {                                                   // una mano è composta da...
    struct Carta carte[MAX_MANO];                               // ...un elenco di carte
    int numero;                                                 // ...e dal numero di carte che contiene
};                                                              // fine della struct

int valore_carta(struct Carta c);                               // dichiarazione: punti di una carta
int punteggio(struct Mano m);                                   // dichiarazione: punteggio di una mano
void aggiungi_carta(struct Mano *m, struct Carta c);            // dichiarazione: aggiunge una carta alla mano
void stampa_mano(struct Mano m);                                // dichiarazione: stampa mano e punteggio

int ha_blackjack(struct Mano m);                                // dichiarazione: vero se la mano è un blackjack naturale

#endif                                                          // fine dell'include guard
