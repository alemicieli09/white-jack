#ifndef STATS_H                                                 // include guard
#define STATS_H                                                 // definisce STATS_H

struct Statistiche {                                            // i numeri di una sessione di gioco
    int mani;                                                   // mani giocate
    int vinte;                                                  // mani vinte
    int perse;                                                  // mani perse
    int pareggi;                                                // mani pareggiate
    int blackjack;                                              // blackjack naturali ottenuti
    int record;                                                 // il massimo di fiches raggiunto
    int serie;                                                  // vittorie consecutive in corso
    int serie_max;                                              // la serie di vittorie consecutive più lunga
};                                                              // fine della struct

void stats_init(struct Statistiche *s, int fiches);             // azzera le statistiche all'inizio della sessione
void stats_registra(struct Statistiche *s, int variazione, int fiches, int blackjack);   // aggiorna le statistiche dopo una mano (blackjack = 1 se il giocatore ha fatto blackjack)
void stats_mostra(const struct Statistiche *s, int fiches);     // mostra il riepilogo della sessione

#endif                                                          // fine dell'include guard
