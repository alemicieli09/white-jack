#include <stdio.h>                                              // printf e scanf
#include <stdlib.h>                                             // srand
#include <time.h>                                               // time
#include "carte.h"                                              // Carta, Scarpa, NUM_CARTE
#include "mano.h"                                               // Mano, punteggio, aggiungi_carta
#include "grafica.h"                                            // mostra_mano e i colori
#include "menu.h"                                               // logo e menu
#include "stats.h"                                              // statistiche di sessione
#include "obiettivi.h"                                          // obiettivi da sbloccare

enum Azione { FERMATO, RADDOPPIATO, DIVISO };                   // come finisce il turno del giocatore: si è fermato, ha raddoppiato o vuole dividere

enum Azione turno_giocatore(const char *titolo, struct Mano *giocatore, struct Scarpa *scarpa, int puo_raddoppiare, int puo_dividere) {   // turno del giocatore: restituisce l'azione scelta
    enum Azione azione = FERMATO;                               // se non succede altro, il turno finisce con "fermato"
    char scelta;                                                // qui memorizza la lettera digitata (char = un solo carattere)
    while (punteggio(*giocatore) < 21) {                        // finché il punteggio è sotto 21 (*giocatore = la mano a cui punta il puntatore)
        printf("Vuoi pescare (c) o fermarti (s)");              // inizio della domanda (senza andare a capo)
        if (puo_raddoppiare) {                                  // se il raddoppio è possibile...
            printf(", raddoppiare (d)");                        // ...lo propone
        }                                                       // fine del controllo
        if (puo_dividere) {                                     // se la divisione è possibile...
            printf(", dividere (p)");                           // ...la propone
        }                                                       // fine del controllo
        printf("? ");                                           // fine della domanda
        if (scanf(" %c", &scelta) != 1) {                       // legge un carattere da tastiera (lo spazio prima di %c salta gli invii); se la lettura fallisce...
            break;                                              // ...esce dal ciclo
        }                                                       // fine del controllo
        if (scelta == 'c') {                                    // se ha scritto "c" (i caratteri singoli vogliono gli apici '...')...
            aggiungi_carta(giocatore, scarpa_pesca(scarpa));    // ...mette nella mano la carta in cima alla scarpa
            mostra_mano(titolo, *giocatore, 0);                 // mostra la mano aggiornata (*giocatore perché qui la mano arriva come puntatore)
            puo_raddoppiare = 0;                                // dopo aver pescato non si può più raddoppiare...
            puo_dividere = 0;                                   // ...né dividere
        } else if (scelta == 's') {                             // altrimenti, se ha scritto "s"...
            break;                                              // ...esce dal ciclo: il giocatore si ferma
        } else if (scelta == 'd' && puo_raddoppiare) {          // altrimenti, se ha scritto "d" ed è permesso...
            printf(GIALLO "Raddoppio: la puntata raddoppia e prendi una sola carta.\n" RESET);   // ...lo annuncia...
            aggiungi_carta(giocatore, scarpa_pesca(scarpa));    // ...prende UNA sola carta...
            mostra_mano(titolo, *giocatore, 0);                 // ...la mostra...
            azione = RADDOPPIATO;                               // ...segnala il raddoppio (la puntata la raddoppia gioca_mano)...
            break;                                              // ...e il turno finisce
        } else if (scelta == 'p' && puo_dividere) {             // altrimenti, se ha scritto "p" ed è permesso...
            azione = DIVISO;                                    // ...segnala la divisione (la fa gioca_mano)...
            break;                                              // ...e il turno finisce
        } else {                                                // in tutti gli altri casi (lettera sbagliata o azione non permessa)...
            printf("Scelta non valida.\n");                     // ...avvisa e richiede la scelta
        }                                                       // fine della scelta
    }                                                           // fine del ciclo
    if (punteggio(*giocatore) > 21) {                           // a fine turno, se il punteggio supera 21...
        printf(ROSSO "Hai sballato!\n" RESET);                  // ...il giocatore ha perso
    }                                                           // fine del controllo
    return azione;                                              // restituisce come è finito il turno
}                                                               // fine di turno_giocatore

void turno_banco(struct Mano *banco, struct Scarpa *scarpa) {   // turno del banco: pesca da solo, senza chiedere nulla
    while (punteggio(*banco) < 17) {                            // finché ha meno di 17 punti...
        aggiungi_carta(banco, scarpa_pesca(scarpa));            // ...pesca la carta in cima alla scarpa
    }                                                           // fine del ciclo: il banco si ferma a 17 o più
}                                                               // fine di turno_banco

#define FICHES_INIZIALI 100                                     // fiches con cui si comincia

void pesca_carta(struct Mano *m, struct Scarpa *scarpa) {       // prende la carta in cima alla scarpa e la mette nella mano
    aggiungi_carta(m, scarpa_pesca(scarpa));                    // pesca e aggiunge
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

static int risolvi_mano(int p_giocatore, int p_banco, int puntata, const char *etichetta) {   // confronta una mano con il banco, stampa l'esito e restituisce la variazione di fiches
    if (p_giocatore > 21) {                                     // se il giocatore ha sballato...
        printf(ROSSO "\n%sIl banco vince.\n" RESET, etichetta);   // ...vince il banco (%s inserisce l'etichetta, vuota se la mano è una sola)
        return -puntata;                                        // perde la puntata
    }                                                           // fine del controllo
    if (p_banco > 21) {                                         // se il banco ha sballato...
        printf(VERDE "\n%sIl banco sballa: hai vinto!\n" RESET, etichetta);   // ...vince il giocatore
        return puntata;                                         // guadagna la puntata
    }                                                           // fine del controllo
    if (p_giocatore > p_banco) {                                // se il giocatore ha più punti...
        printf(VERDE "\n%sHai vinto!\n" RESET, etichetta);      // ...vince
        return puntata;                                         // guadagna la puntata
    }                                                           // fine del controllo
    if (p_giocatore < p_banco) {                                // se ne ha meno...
        printf(ROSSO "\n%sIl banco vince.\n" RESET, etichetta); // ...perde
        return -puntata;                                        // perde la puntata
    }                                                           // fine del controllo
    printf(GIALLO "\n%sPareggio.\n" RESET, etichetta);          // altrimenti i punteggi sono uguali
    return 0;                                                   // il saldo non cambia
}                                                               // fine di risolvi_mano

int gioca_mano(int puntata, int saldo, struct Scarpa *scarpa, int *blackjack) {   // gioca una mano intera; restituisce di quante fiches cambia il saldo (+ vinte, - perse)
    struct Mano giocatore;                                      // la mano del giocatore
    struct Mano banco;                                          // la mano del banco
    giocatore.numero = 0;                                       // all'inizio è vuota
    banco.numero = 0;                                           // anche questa
    *blackjack = 0;                                             // per ora niente blackjack (*blackjack = la variabile di chi ha chiamato la funzione)

    pesca_carta(&giocatore, scarpa);                            // si distribuisce come al tavolo: giocatore...
    pesca_carta(&banco, scarpa);                                // ...banco...
    pesca_carta(&giocatore, scarpa);                            // ...giocatore...
    pesca_carta(&banco, scarpa);                                // ...banco

    mostra_mano("Banco", banco, 1);                             // mostra il banco con la seconda carta coperta (1 = nascondi)
    mostra_mano("Giocatore", giocatore, 0);                     // mostra il giocatore con tutte le carte scoperte (0 = non nascondere)

    int bj_giocatore = ha_blackjack(giocatore);                 // 1 se il giocatore ha un blackjack naturale, altrimenti 0
    int bj_banco = ha_blackjack(banco);                         // lo stesso per il banco
    if (bj_giocatore || bj_banco) {                             // se almeno uno ha blackjack (|| = "o")...
        mostra_mano("Banco", banco, 0);                         // ...si scoprono subito le carte del banco
        if (bj_giocatore && bj_banco) {                         // se ce l'hanno entrambi...
            printf(GIALLO "Blackjack per entrambi: pareggio.\n" RESET);      // ...pareggio
            return 0;                                           // il saldo non cambia
        }                                                       // fine del controllo
        if (bj_giocatore) {                                     // se ce l'ha solo il giocatore...
            printf(VERDE "BLACKJACK! Vinci 3 a 2.\n" RESET);    // ...vince con il pagamento maggiorato
            *blackjack = 1;                                     // segnala a chi ha chiamato che c'è stato un blackjack
            return puntata * 3 / 2;                             // puntata x 3 / 2 (divisione tra interi: arrotonda per difetto)
        }                                                       // fine del controllo
        printf(ROSSO "Il banco ha blackjack.\n" RESET);         // altrimenti ce l'ha solo il banco
        return -puntata;                                        // il giocatore perde la puntata
    }                                                           // fine del controllo

    struct Mano mani[2];                                        // le mani del giocatore: una sola, oppure due dopo la divisione
    int puntate[2];                                             // la puntata di ogni mano
    int num_mani = 1;                                           // all'inizio il giocatore ha una mano sola
    mani[0] = giocatore;                                        // la prima mano è quella appena distribuita (la struct viene copiata)
    puntate[0] = puntata;                                       // con la puntata iniziale

    int puo_raddoppiare = (saldo >= 2 * puntata);               // si può raddoppiare solo se restano fiches per coprire la seconda puntata
    int puo_dividere = puo_raddoppiare && giocatore.carte[0].valore == giocatore.carte[1].valore;   // si può dividere con due carte uguali e fiches sufficienti
    enum Azione azione = turno_giocatore("Giocatore", &mani[0], scarpa, puo_raddoppiare, puo_dividere);   // gioca il giocatore e dice come è finito il turno

    if (azione == RADDOPPIATO) {                                // se ha raddoppiato...
        puntate[0] = puntata * 2;                               // ...la puntata raddoppia
    } else if (azione == DIVISO) {                              // se ha diviso...
        num_mani = 2;                                           // ...adesso le mani sono due
        mani[1].numero = 0;                                     // la seconda mano parte vuota...
        aggiungi_carta(&mani[1], mani[0].carte[1]);             // ...e riceve la seconda carta della prima mano
        mani[0].numero = 1;                                     // la prima mano resta con una carta sola
        puntate[1] = puntata;                                   // la seconda mano ha la stessa puntata della prima
        pesca_carta(&mani[0], scarpa);                          // ogni mano riceve una nuova carta
        pesca_carta(&mani[1], scarpa);                          // anche la seconda
        for (int i = 0; i < 2; i++) {                           // si gioca prima una mano, poi l'altra
            const char *titolo = (i == 0) ? "Prima mano" : "Seconda mano";   // il titolo da mostrare (condizione ? se_vero : se_falso)
            mostra_mano(titolo, mani[i], 0);                    // mostra la mano
            turno_giocatore(titolo, &mani[i], scarpa, 0, 0);    // la gioca (0, 0: dopo la divisione niente raddoppio né nuova divisione)
        }                                                       // fine del ciclo delle mani
    }                                                           // fine dei controlli

    int qualcuna_in_gioco = 0;                                  // 1 se almeno una mano non ha sballato
    for (int i = 0; i < num_mani; i++) {                        // per ogni mano...
        if (punteggio(mani[i]) <= 21) {                         // ...se non ha sballato...
            qualcuna_in_gioco = 1;                              // ...il banco dovrà giocare
        }                                                       // fine del controllo
    }                                                           // fine del ciclo
    if (qualcuna_in_gioco) {                                    // se c'è almeno una mano in gioco...
        turno_banco(&banco, scarpa);                            // ...gioca il banco (pesca fino a 17)
        mostra_mano("Banco", banco, 0);                         // ...e mostra la sua mano completa
    }                                                           // fine del controllo

    int p_banco = punteggio(banco);                             // punteggio finale del banco
    int totale = 0;                                             // somma delle variazioni di tutte le mani
    for (int i = 0; i < num_mani; i++) {                        // per ogni mano del giocatore...
        const char *etichetta = "";                             // con una mano sola non serve nessuna etichetta
        if (num_mani == 2) {                                    // dopo la divisione...
            etichetta = (i == 0) ? "Prima mano: " : "Seconda mano: ";   // ...si indica di quale mano si parla
        }                                                       // fine del controllo
        totale += risolvi_mano(punteggio(mani[i]), p_banco, puntate[i], etichetta);   // confronta con il banco e somma il risultato
    }                                                           // fine del ciclo
    return totale;                                              // restituisce quanto cambia il saldo
}                                                               // fine di gioca_mano

void gioca_sessione(struct Obiettivi *obiettivi) {              // una sessione di gioco: si gioca finché ci sono fiches o si esce
    int fiches = FICHES_INIZIALI;                               // il saldo del giocatore
    struct Statistiche stats;                                   // le statistiche di questa sessione
    stats_init(&stats, fiches);                                 // le azzera (&stats = indirizzo della struttura)
    struct Scarpa scarpa;                                       // la scarpa con i 6 mazzi
    scarpa_rimescola(&scarpa);                                  // la riempie e la mescola

    while (fiches > 0) {                                        // finché ci sono fiches...
        int puntata = leggi_puntata(fiches);                    // ...chiede la puntata
        if (puntata == 0) {                                     // se il giocatore vuole uscire...
            break;                                              // ...esce dal ciclo
        }                                                       // fine del controllo
        if (scarpa_da_rimescolare(&scarpa)) {                   // se restano poche carte nella scarpa...
            scarpa_rimescola(&scarpa);                          // ...la rimescola...
            printf(GIALLO "\nIl mazzo viene rimescolato.\n" RESET);   // ...e lo comunica
        }                                                       // fine del controllo
        int blackjack = 0;                                      // gioca_mano ci scriverà 1 se il giocatore fa blackjack
        int variazione = gioca_mano(puntata, fiches, &scarpa, &blackjack);   // gioca la mano: restituisce quante fiches si vincono (+) o si perdono (-)
        fiches += variazione;                                   // aggiorna il saldo
        stats_registra(&stats, variazione, fiches, blackjack);  // aggiorna le statistiche con il risultato della mano
        if (variazione > 0) {                                   // se è positiva...
            printf(VERDE "\nHai vinto %d fiches\n\n" RESET, variazione);       // ...hai vinto: mostra quante
        } else if (variazione < 0) {                            // se è negativa...
            printf(ROSSO "\nHai perso %d fiches\n\n" RESET, -variazione);      // ...hai perso: mostra quante
        } else {                                                // se è zero...
            printf(GIALLO "\nLa puntata ti torna indietro\n\n" RESET);          // ...nessun cambiamento
        }                                                       // fine dei controlli
        obiettivi_controlla(obiettivi, &stats);                 // controlla se la mano ha sbloccato qualche obiettivo
    }                                                           // fine del ciclo

    if (fiches == 0) {                                          // se il saldo è finito...
        printf("Hai finito le fiches. Fine della partita.\n\n");  // ...game over
    } else {                                                    // altrimenti il giocatore è uscito di sua volontà
        printf("Esci dalla partita con %d fiches.\n\n", fiches); // saluto con il saldo finale
    }                                                           // fine del controllo
    stats_mostra(&stats, fiches);                               // a fine sessione mostra il riepilogo
}                                                               // fine di gioca_sessione

int main(void) {                                                // il programma parte da qui
    srand((unsigned)time(NULL));                                // seme casuale basato sull'orario (una volta sola, all'avvio)
    struct Obiettivi obiettivi;                                 // gli obiettivi restano sbloccati finché il programma è aperto
    obiettivi_init(&obiettivi);                                 // all'inizio sono tutti bloccati
    mostra_logo();                                              // mostra il logo all'avvio

    int scelta = menu_principale();                             // mostra il menu e legge la scelta
    while (scelta != 4) {                                       // finché non sceglie "Esci"...
        if (scelta == 1) {                                      // se ha scelto "Gioca"...
            gioca_sessione(&obiettivi);                         // ...inizia una nuova sessione
        } else if (scelta == 2) {                               // se ha scelto "Regole"...
            mostra_regole();                                    // ...le mostra
        } else {                                                // altrimenti ha scelto "Obiettivi"...
            obiettivi_mostra(&obiettivi);                       // ...li mostra
        }                                                       // fine della scelta
        scelta = menu_principale();                             // torna al menu
    }                                                           // fine del ciclo
    printf("\nAlla prossima!\n");                              // saluto finale
    return 0;                                                   // fine, tutto ok
}                                                               // fine di main
