#include <stdio.h>                                              // printf e scanf
#include <stdlib.h>                                             // srand
#include <time.h>                                               // time
#include "carte.h"                                              // Carta, mazzo, NUM_CARTE
#include "mano.h"                                               // Mano, punteggio, aggiungi_carta


void turno_giocatore(struct Mano *giocatore, struct Carta mazzo[], int *prossima) {   // turno del giocatore: mano e posizione nel mazzo arrivano come puntatori, così la funzione può modificarle
    char scelta;                                                // qui memorizza la lettera digitata (char = un solo carattere)
    while (punteggio(*giocatore) < 21) {                        // finché il punteggio è sotto 21 (*giocatore = la mano a cui punta il puntatore)
        printf("Vuoi pescare (c) o fermarti (s)? ");            // chiede cosa fare
        if (scanf(" %c", &scelta) != 1) {                       // legge un carattere da tastiera (lo spazio prima di %c salta gli invii); se la lettura fallisce...
            break;                                              // ...esce dal ciclo
        }                                                       // fine del controllo
        if (scelta == 'c') {                                    // se ha scritto "c" (i caratteri singoli vogliono gli apici '...')...
            aggiungi_carta(giocatore, mazzo[*prossima]);        // ...mette nella mano la carta in cima al mazzo (*prossima = la posizione attuale)
            (*prossima)++;                                      // la prossima carta da pescare è quella dopo (le parentesi sono necessarie)
            printf("Hai pescato: ");                            // annuncia la carta
            stampa_carta(giocatore->carte[giocatore->numero - 1]);   // stampa l'ultima carta aggiunta (posizione numero - 1)
            printf("Punteggio: %d\n", punteggio(*giocatore));   // mostra il nuovo punteggio
        } else if (scelta == 's') {                             // altrimenti, se ha scritto "s"...
            break;                                              // ...esce dal ciclo: il giocatore si ferma
        } else {                                                // in tutti gli altri casi...
            printf("Scelta non valida.\n");                     // ...avvisa e richiede la scelta
        }                                                       // fine della scelta
    }                                                           // fine del ciclo
    if (punteggio(*giocatore) > 21) {                           // a fine turno, se il punteggio supera 21...
        printf("Hai sballato!\n");                              // ...il giocatore ha perso
    }                                                           // fine del controllo
}                                                               // fine di turno_giocatore

void turno_banco(struct Mano *banco, struct Carta mazzo[], int *prossima) {   // turno del banco: pesca da solo, senza chiedere nulla
    while (punteggio(*banco) < 17) {                            // finché ha meno di 17 punti...
        aggiungi_carta(banco, mazzo[*prossima]);                // ...pesca la carta in cima al mazzo
        (*prossima)++;                                          // avanza nel mazzo
    }                                                           // fine del ciclo: il banco si ferma a 17 o più
}                                                               // fine di turno_banco

void stampa_esito(int punti_giocatore, int punti_banco) {       // confronta i punteggi (qui arrivano due numeri normali, non puntatori)
    if (punti_banco > 21) {                                     // se il banco ha sballato...
        printf("Il banco sballa: hai vinto!\n");                // ...vince il giocatore
    } else if (punti_giocatore > punti_banco) {                 // altrimenti, se il giocatore ha più punti...
        printf("Hai vinto!\n");                                 // ...vince
    } else if (punti_giocatore < punti_banco) {                 // se ne ha meno...
        printf("Il banco vince.\n");                            // ...vince il banco
    } else {                                                    // se ne ha lo stesso numero...
        printf("Pareggio.\n");                                  // ...pareggio
    }                                                           // fine dei confronti
}                                                               // fine di stampa_esito

int main(void) {                                                // il programma parte da qui
    struct Carta mazzo[NUM_CARTE];                              // il mazzo di 52 carte
    int prossima = 0;                                           // posizione della prossima carta da pescare

    srand((unsigned)time(NULL));                                // seme casuale basato sull'orario
    crea_mazzo(mazzo);                                          // crea il mazzo in ordine
    mescola_mazzo(mazzo, NUM_CARTE);                            // lo mescola

    struct Mano giocatore;                                      // la mano del giocatore
    giocatore.numero = 0;                                       // all'inizio è vuota
    struct Mano banco;                                          // la mano del banco
    banco.numero = 0;                                           // all'inizio è vuota

    aggiungi_carta(&giocatore, mazzo[prossima]);                // pesca la prima carta (&giocatore = indirizzo della mano)
    prossima++;                                                 // la prossima carta da pescare è quella dopo
    aggiungi_carta(&giocatore, mazzo[prossima]);                // pesca la seconda carta
    prossima++;                                                 // avanza ancora

    aggiungi_carta(&banco, mazzo[prossima]);                    // prima carta del banco
    prossima++;                                                 // avanza nel mazzo
    aggiungi_carta(&banco, mazzo[prossima]);                    // seconda carta del banco
    prossima++;                                                 // avanza nel mazzo

    printf("Mano del giocatore:\n");                            // titolo
    stampa_mano(giocatore);                                     // stampa le carte e il punteggio
    printf("\nCarta scoperta del banco:\n");                    // titolo
    stampa_carta(banco.carte[0]);                               // mostra solo la prima carta, la seconda resta coperta (con . perché banco è una mano normale, non un puntatore)
    printf("\n");                                               // riga vuota

    turno_giocatore(&giocatore, mazzo, &prossima);              // fa giocare il giocatore (passa gli indirizzi di mano e posizione, così vengono aggiornati)

    printf("\nMano finale:\n");                                 // titolo (\n iniziale lascia una riga vuota)
    stampa_mano(giocatore);                                     // stampa la mano finale e il punteggio
    if (punteggio(giocatore) <= 21) {                           // se il giocatore non ha sballato...
        turno_banco(&banco, mazzo, &prossima);                  // ...gioca il banco
        printf("\nMano del banco:\n");                          // titolo
        stampa_mano(banco);                                     // mostra tutte le carte del banco e il punteggio
        stampa_esito(punteggio(giocatore), punteggio(banco));   // dice chi ha vinto
    } else {                                                    // altrimenti il giocatore ha sballato...
        printf("\nIl banco vince.\n");                          // ...vince il banco senza giocare
    }                                                           // fine del controllo

    return 0;                                                   // fine, tutto ok
}                                                               // fine di main
