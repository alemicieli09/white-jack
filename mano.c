#include <stdio.h>                                              // printf (serve a stampa_mano)
#include "mano.h"                                               // tipi Mano e Carta e le dichiarazioni di queste funzioni

int valore_carta(struct Carta c) {                              // dice quanti punti vale una carta nel blackjack
    if (c.valore == 1) {                                        // se è un Asso...
        return 11;                                              // ...per ora lo contiamo 11
    }                                                           // fine del controllo
    if (c.valore >= 10) {                                       // se è 10, Fante, Donna o Re...
        return 10;                                              // ...vale 10
    }                                                           // fine del controllo
    return c.valore;                                            // altrimenti vale il suo numero
}                                                               // fine di valore_carta

int punteggio(struct Mano m) {                                  // calcola il punteggio di una mano
    int totale = 0;                                             // somma dei punti
    int assi = 0;                                               // quanti Assi ci sono nella mano
    for (int i = 0; i < m.numero; i++) {                        // per ogni carta della mano...
        totale += valore_carta(m.carte[i]);                     // ...aggiunge i suoi punti (+= significa "aggiungi a")
        if (m.carte[i].valore == 1) {                           // se la carta è un Asso...
            assi++;                                             // ...aumenta il conteggio degli Assi
        }                                                       // fine del controllo
    }                                                           // fine del ciclo
    while (totale > 21 && assi > 0) {                           // finché si sfora 21 e c'è un Asso contato 11...
        totale -= 10;                                           // ...lo trasforma in 1 (11 - 10)
        assi--;                                                 // ...e passa all'eventuale Asso successivo
    }                                                           // fine del ciclo
    return totale;                                              // restituisce il punteggio finale
}                                                               // fine di punteggio

void aggiungi_carta(struct Mano *m, struct Carta c) {           // aggiunge una carta alla mano (m è un puntatore: la mano originale)
    m->carte[m->numero] = c;                                    // mette la carta nella prima posizione libera (-> accede a un campo tramite puntatore)
    m->numero++;                                                // ora la mano ha una carta in più
}                                                               // fine di aggiungi_carta

void stampa_mano(struct Mano m) {                               // stampa tutte le carte della mano e il punteggio
    for (int i = 0; i < m.numero; i++) {                        // per ogni carta della mano...
        stampa_carta(m.carte[i]);                               // ...la stampa
    }                                                           // fine del ciclo
    printf("Punteggio: %d\n", punteggio(m));                    // stampa il punteggio
}                                                               // fine di stampa_mano

int ha_blackjack(struct Mano m) {                               // dice se la mano è un blackjack naturale: 21 con le prime due carte
    return m.numero == 2 && punteggio(m) == 21;                 // vero (1) se ci sono esattamente 2 carte E il punteggio è 21 (&& = "e")
}                                                               // fine di ha_blackjack
