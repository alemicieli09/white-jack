#include <stdio.h>                                              // printf
#include "grafica.h"                                            // dichiarazioni e colori di questo modulo

static const char *simboli[] = { "♥", "♦", "♣", "♠" };          // i simboli dei semi, nello stesso ordine dell'enum Seme
static const char *etichette[] = { "", "A", "2", "3", "4", "5", "6", "7",     // le scritte sull'angolo della carta (posizione 0 vuota)
                                   "8", "9", "10", "J", "Q", "K" };           // il valore 1 corrisponde ad "A" (Asso)

static const char *colore_seme(enum Seme s) {                   // restituisce il codice colore giusto per un seme (static: usata solo qui)
    if (s == CUORI || s == QUADRI) {                            // cuori e quadri...
        return ROSSO;                                           // ...sono rossi
    }                                                           // fine del controllo
    return RESET;                                               // fiori e picche restano del colore normale
}                                                               // fine di colore_seme

static void stampa_riga_carta(struct Carta c, int riga, int coperta) {   // stampa UNA riga (0-4) di UNA carta, senza andare a capo
    if (coperta) {                                              // se la carta è coperta...
        if (riga == 0) {                                        // ...la riga in alto...
            printf("┌─────┐");                                  // ...è il bordo superiore
        } else if (riga == 4) {                                 // ...la riga in basso...
            printf("└─────┘");                                  // ...è il bordo inferiore
        } else {                                                // ...le righe in mezzo...
            printf("│░░░░░│");                                  // ...sono il retro della carta
        }                                                       // fine delle righe della carta coperta
        return;                                                 // finito: esce dalla funzione
    }                                                           // fine del caso "coperta"
    const char *col = colore_seme(c.seme);                      // il colore di questa carta
    switch (riga) {                                             // sceglie cosa stampare in base al numero di riga
        case 0:                                                 // riga 0...
            printf("┌─────┐");                                  // ...bordo superiore
            break;                                              // break: esce dallo switch (senza, continuerebbe col caso dopo)
        case 1:                                                 // riga 1...
            printf("│%s%-2s%s   │", col, etichette[c.valore], RESET);   // ...valore in alto a sinistra (%-2s: allineato a sinistra su 2 spazi)
            break;                                              // fine del caso
        case 2:                                                 // riga 2...
            printf("│  %s%s%s  │", col, simboli[c.seme], RESET);        // ...simbolo del seme al centro
            break;                                              // fine del caso
        case 3:                                                 // riga 3...
            printf("│   %s%2s%s│", col, etichette[c.valore], RESET);    // ...valore in basso a destra (%2s: allineato a destra su 2 spazi)
            break;                                              // fine del caso
        default:                                                // qualsiasi altra riga (la 4)...
            printf("└─────┘");                                  // ...bordo inferiore
            break;                                              // fine del caso
    }                                                           // fine dello switch
}                                                               // fine di stampa_riga_carta

void mostra_mano(const char *titolo, struct Mano m, int nascondi_seconda) {   // disegna tutta la mano con le carte affiancate
    printf("\n%s%s%s\n", GIALLO, titolo, RESET);                // titolo in giallo (\n iniziale lascia una riga vuota)
    for (int riga = 0; riga < 5; riga++) {                      // ogni carta è alta 5 righe: le disegniamo riga per riga...
        for (int i = 0; i < m.numero; i++) {                    // ...e per ogni riga passiamo tutte le carte, così restano affiancate
            int coperta = (nascondi_seconda && i == 1);         // la carta è coperta solo se richiesto E se è la seconda (posizione 1)
            stampa_riga_carta(m.carte[i], riga, coperta);       // stampa la riga di questa carta
            printf(" ");                                        // uno spazio tra una carta e l'altra
        }                                                       // fine del ciclo delle carte
        printf("\n");                                           // a capo: finita questa riga di tutte le carte
    }                                                           // fine del ciclo delle righe
    if (nascondi_seconda) {                                     // se una carta è coperta...
        printf("Punteggio: ?\n");                               // ...il punteggio non si può sapere
    } else {                                                    // altrimenti...
        printf("Punteggio: %d\n", punteggio(m));                // ...mostra il punteggio vero
    }                                                           // fine del controllo
}                                                               // fine di mostra_mano
