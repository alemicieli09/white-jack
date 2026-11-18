#include <stdio.h>                                              // printf (serve a stampa_carta)
#include <stdlib.h>                                             // rand (serve a mescola_mazzo)
#include "carte.h"                                              // tipi Carta e Seme e le dichiarazioni di queste funzioni

static const char *nomi_semi[] = { "Cuori", "Quadri", "Fiori", "Picche" };            // testi dei semi
static const char *nomi_valori[] = { "", "Asso", "2", "3", "4", "5", "6", "7",        // testi dei valori (posizione 0 vuota)
                              "8", "9", "10", "Fante", "Donna", "Re" };        // il valore 1 corrisponde ad "Asso"

void stampa_carta(struct Carta c) {                             // stampa una carta
    printf("%s di %s\n", nomi_valori[c.valore], nomi_semi[c.seme]);   // es.: "Re di Cuori"
}                                                               // fine di stampa_carta

void crea_mazzo(struct Carta mazzo[]) {                         // riempie il mazzo con le 52 carte in ordine
    int n = 0;                                                  // posizione della prossima carta
    for (int seme = CUORI; seme <= PICCHE; seme++) {            // per ognuno dei 4 semi...
        for (int valore = 1; valore <= 13; valore++) {          // ...e per ogni valore da 1 a 13
            mazzo[n].valore = valore;                           // scrive il valore
            mazzo[n].seme = (enum Seme)seme;                    // scrive il seme
            n++;                                                // passa alla posizione successiva
        }                                                       // fine del ciclo dei valori
    }                                                           // fine del ciclo dei semi
}                                                               // fine di crea_mazzo

void mescola_mazzo(struct Carta mazzo[], int n) {               // mescola le prime n carte del mazzo
    for (int i = n - 1; i > 0; i--) {                           // parte dall'ultima carta e scende
        int j = rand() % (i + 1);                               // sceglie una posizione casuale tra 0 e i
        struct Carta tmp = mazzo[i];                            // salva da parte la carta in posizione i
        mazzo[i] = mazzo[j];                                    // mette al suo posto la carta in posizione j
        mazzo[j] = tmp;                                         // mette la carta salvata in posizione j
    }                                                           // fine del ciclo
}                                                               // fine di mescola_mazzo

void scarpa_rimescola(struct Scarpa *s) {                       // riempie la scarpa con 6 mazzi completi e la mescola (s è un puntatore: la scarpa originale)
    for (int k = 0; k < NUM_MAZZI; k++) {                       // per ognuno dei 6 mazzi...
        crea_mazzo(&s->carte[k * NUM_CARTE]);                   // ...crea 52 carte a partire dalla posizione k x 52 (& prende l'indirizzo di quella posizione)
    }                                                           // fine del ciclo dei mazzi
    mescola_mazzo(s->carte, CARTE_SCARPA);                      // mescola tutte le 312 carte insieme
    s->prossima = 0;                                            // si riparte dalla prima carta
}                                                               // fine di scarpa_rimescola

struct Carta scarpa_pesca(struct Scarpa *s) {                   // restituisce la carta in cima alla scarpa e passa alla successiva
    if (s->prossima >= CARTE_SCARPA) {                          // sicurezza: se le carte sono finite del tutto...
        scarpa_rimescola(s);                                    // ...ricrea la scarpa (non dovrebbe mai succedere)
    }                                                           // fine del controllo
    struct Carta c = s->carte[s->prossima];                     // prende la carta in cima
    s->prossima++;                                              // la prossima volta si pesca quella dopo
    return c;                                                   // restituisce la carta pescata
}                                                               // fine di scarpa_pesca

int scarpa_da_rimescolare(const struct Scarpa *s) {             // dice se restano poche carte (const: la funzione legge soltanto)
    return CARTE_SCARPA - s->prossima < SOGLIA_RIMESCOLA;       // carte rimaste = totale - già pescate; vero se sono meno della soglia
}                                                               // fine di scarpa_da_rimescolare
