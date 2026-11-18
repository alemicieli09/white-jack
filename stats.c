#include <stdio.h>                                              // printf
#include "grafica.h"                                            // i colori (GIALLO, RESET)
#include "stats.h"                                              // la struct e le dichiarazioni di questo modulo

void stats_init(struct Statistiche *s, int fiches) {            // azzera le statistiche (s è un puntatore: la struttura originale)
    s->mani = 0;                                                // nessuna mano giocata
    s->vinte = 0;                                               // nessuna vittoria
    s->perse = 0;                                               // nessuna sconfitta
    s->pareggi = 0;                                             // nessun pareggio
    s->blackjack = 0;                                           // nessun blackjack
    s->record = fiches;                                         // il record parte dal saldo iniziale
    s->serie = 0;                                               // nessuna serie in corso
    s->serie_max = 0;                                           // nessuna serie registrata
}                                                               // fine di stats_init

void stats_registra(struct Statistiche *s, int variazione, int fiches, int blackjack) {   // aggiorna i numeri dopo una mano (fiches = saldo già aggiornato)
    s->mani++;                                                  // una mano in più
    if (variazione > 0) {                                       // se la mano è stata vinta...
        s->vinte++;                                             // ...una vittoria in più
        s->serie++;                                             // ...la serie in corso cresce
        if (s->serie > s->serie_max) {                          // se supera la serie più lunga...
            s->serie_max = s->serie;                            // ...diventa la nuova serie più lunga
        }                                                       // fine del controllo
    } else if (variazione < 0) {                                // se la mano è stata persa...
        s->perse++;                                             // ...una sconfitta in più
        s->serie = 0;                                           // ...la serie si interrompe
    } else {                                                    // se è un pareggio...
        s->pareggi++;                                           // ...un pareggio in più (la serie non cambia)
    }                                                           // fine dei controlli
    if (blackjack) {                                            // se il giocatore ha fatto blackjack...
        s->blackjack++;                                         // ...ne conta uno in più
    }                                                           // fine del controllo
    if (fiches > s->record) {                                   // se il saldo supera il record...
        s->record = fiches;                                     // ...è il nuovo record
    }                                                           // fine del controllo
}                                                               // fine di stats_registra

void stats_mostra(const struct Statistiche *s, int fiches) {    // mostra il riepilogo (const: la funzione legge soltanto, non modifica)
    if (s->mani == 0) {                                         // se non si è giocata nessuna mano...
        return;                                                 // ...non c'è niente da mostrare
    }                                                           // fine del controllo
    printf(GIALLO "Statistiche della sessione" RESET "\n");     // titolo in giallo
    printf("  Mani giocate:           %d\n", s->mani);          // quante mani
    printf("  Vinte / perse / pari:   %d / %d / %d\n", s->vinte, s->perse, s->pareggi);   // l'esito delle mani
    printf("  Serie di vittorie max:  %d\n", s->serie_max);     // la serie più lunga
    printf("  Blackjack:              %d\n", s->blackjack);       // quanti blackjack naturali
    printf("  Record di fiches:       %d\n", s->record);        // il massimo raggiunto
    printf("  Fiches finali:          %d\n\n", fiches);         // il saldo di fine sessione
}                                                               // fine di stats_mostra
