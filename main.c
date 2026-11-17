#include <stdio.h>                                              // printf e scanf
#include <stdlib.h>                                             // srand
#include <time.h>                                               // time
#include "carte.h"                                              // Carta, mazzo, NUM_CARTE
#include "mano.h"                                               // Mano, punteggio, aggiungi_carta
#include "grafica.h"

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
            mostra_mano("Giocatore", *giocatore, 0);            // mostra la mano aggiornata (*giocatore perché qui la mano arriva come puntatore)
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


#define FICHES_INIZIALI 100                                     // fiches con cui si comincia

void pesca_carta(struct Mano *m, struct Carta mazzo[], int *prossima) {   // prende la carta in cima al mazzo e la mette nella mano
    aggiungi_carta(m, mazzo[*prossima]);                        // aggiunge la carta alla mano
    (*prossima)++;                                              // avanza nel mazzo
}                                                               // fine di pesca_carta

int leggi_puntata(int saldo) {                                  // chiede la puntata finché non è valida; restituisce 0 se il giocatore vuole uscire
    int puntata;                                                // qui memorizza il numero scritto
    while (1) {                                                 // ciclo infinito: se ne esce con return
        printf("Fiches: %d. Quanto vuoi puntare (1-%d, 0 per uscire)? ", saldo, saldo);   // domanda
        int letti = scanf("%d", &puntata);                      // legge un intero; restituisce quanti valori ha letto
        if (letti == EOF) {                                     // se l'input è finito (es. Ctrl+D)...
            return 0;                                           // ...esce come se avesse scelto 0
        }                                                       // fine del controllo
        if (letti != 1) {                                       // se non ha scritto un numero (es. una lettera)...
            int c;                                              // carattere letto
            while ((c = getchar()) != '\n' && c != EOF) {       // ...scarta il resto della riga, un carattere alla volta
            }                                                   // il ciclo non ha altro da fare
            printf("Scrivi un numero.\n");                      // avvisa
            continue;                                           // torna all'inizio del ciclo e richiede
        }                                                       // fine del controllo
        if (puntata >= 0 && puntata <= saldo) {                 // se la puntata è tra 0 e il saldo...
            return puntata;                                     // ...è valida: la restituisce
        }                                                       // fine del controllo
        printf("Puntata non valida.\n");                        // altrimenti avvisa e ricomincia
    }                                                           // fine del ciclo
}                                                               // fine di leggi_puntata

int gioca_mano(int puntata) {                                   // gioca una mano intera; restituisce di quante fiches cambia il saldo (+ vinte, - perse)
    struct Carta mazzo[NUM_CARTE];                              // il mazzo di questa mano
    int prossima = 0;                                           // posizione della prossima carta da pescare
    crea_mazzo(mazzo);                                          // crea il mazzo in ordine
    mescola_mazzo(mazzo, NUM_CARTE);                            // lo mescola

    struct Mano giocatore;                                      // la mano del giocatore
    struct Mano banco;                                          // la mano del banco
    giocatore.numero = 0;                                       // all'inizio è vuota
    banco.numero = 0;                                           // anche questa

    pesca_carta(&giocatore, mazzo, &prossima);                  // si distribuisce come al tavolo: giocatore...
    pesca_carta(&banco, mazzo, &prossima);                      // ...banco...
    pesca_carta(&giocatore, mazzo, &prossima);                  // ...giocatore...
    pesca_carta(&banco, mazzo, &prossima);                      // ...banco

    mostra_mano("Banco", banco, 1);                             // mostra il banco con la seconda carta coperta (1 = nascondi)
    mostra_mano("Giocatore", giocatore, 0);                     // mostra il giocatore con tutte le carte scoperte (0 = non nascondere)

    int bj_giocatore = ha_blackjack(giocatore);                 // 1 se il giocatore ha un blackjack naturale, altrimenti 0
    int bj_banco = ha_blackjack(banco);                         // lo stesso per il banco
    if (bj_giocatore || bj_banco) {                             // se almeno uno ha blackjack (|| = "o")...
        mostra_mano("Banco", banco, 0);                         // si scoprono subito le carte del banco
        if (bj_giocatore && bj_banco) {                         // se ce l'hanno entrambi...
            printf("Blackjack per entrambi: pareggio.\n");      // ...pareggio
            return 0;                                           // il saldo non cambia
        }                                                       // fine del controllo
        if (bj_giocatore) {                                     // se ce l'ha solo il giocatore...
            printf("BLACKJACK! Vinci 3 a 2.\n");                // ...vince con il pagamento maggiorato
            return puntata * 3 / 2;                             // puntata x 3 / 2 (divisione tra interi: arrotonda per difetto)
        }                                                       // fine del controllo
        printf("Il banco ha blackjack.\n");                     // altrimenti ce l'ha solo il banco
        return -puntata;                                        // il giocatore perde la puntata
    }                                                           // fine del controllo

    turno_giocatore(&giocatore, mazzo, &prossima);              // gioca il giocatore (pesca o si ferma)

    if (punteggio(giocatore) > 21) {                            // se il giocatore ha sballato...
        printf("\nIl banco vince.\n");                          // ...perde, senza che il banco giochi
        return -puntata;                                        // perde la puntata
    }                                                           // fine del controllo

    turno_banco(&banco, mazzo, &prossima);                      // gioca il banco (pesca fino a 17)
    mostra_mano("Banco", banco, 0);                             // mostra la mano completa del banco

    int p_giocatore = punteggio(giocatore);                     // punteggio finale del giocatore
    int p_banco = punteggio(banco);                             // punteggio finale del banco
    if (p_banco > 21) {                                         // se il banco ha sballato...
        printf("\nIl banco sballa: hai vinto!\n");              // ...vince il giocatore
        return puntata;                                         // guadagna la puntata
    }                                                           // fine del controllo
    if (p_giocatore > p_banco) {                                // se il giocatore ha più punti...
        printf("\nHai vinto!\n");                               // ...vince
        return puntata;                                         // guadagna la puntata
    }                                                           // fine del controllo
    if (p_giocatore < p_banco) {                                // se ne ha meno...
        printf("\nIl banco vince.\n");                          // ...perde
        return -puntata;                                        // perde la puntata
    }                                                           // fine del controllo
    printf("\nPareggio.\n");                                    // altrimenti i punteggi sono uguali
    return 0;                                                   // il saldo non cambia
}                                                               // fine di gioca_mano

int main(void) {                                                // il programma parte da qui
    int fiches = FICHES_INIZIALI;                               // il saldo del giocatore

    srand((unsigned)time(NULL));                                // seme casuale basato sull'orario (una volta sola, all'avvio)
    printf("=== WHITE JACK ===\n");                             // titolo

    while (fiches > 0) {                                        // finché ci sono fiches...
        int puntata = leggi_puntata(fiches);                    // ...chiede la puntata
        if (puntata == 0) {                                     // se il giocatore vuole uscire...
            break;                                              // ...esce dal ciclo
        }                                                       // fine del controllo
        int variazione = gioca_mano(puntata);                   // gioca la mano: restituisce quante fiches si vincono (+) o si perdono (-)
        fiches += variazione;                                   // aggiorna il saldo
        if (variazione > 0) {                                   // se è positiva...
            printf(VERDE "\nHai vinto %d fiches\n\n" RESET, variazione);       // ...hai vinto: mostra quante
        } else if (variazione < 0) {                            // se è negativa...
            printf(ROSSO "\nHai perso %d fiches\n\n" RESET, -variazione);      // ...hai perso: mostra quante (il meno davanti toglie il segno)
        } else {                                                // se è zero...
            printf(GIALLO "\nLa puntata ti torna indietro\n\n" RESET);          // ...nessun cambiamento
        }                                                       // fine dei controlli
    }                                                           // fine del ciclo

    if (fiches == 0) {                                          // se il saldo è finito...
        printf("Hai finito le fiches. Fine della partita.\n");  // ...game over
    } else {                                                    // altrimenti il giocatore è uscito di sua volontà
        printf("Esci con %d fiches. Alla prossima!\n", fiches); // saluto con il saldo finale
    }                                                           // fine del controllo
    return 0;                                                   // fine, tutto ok
}                                                               // fine di main

