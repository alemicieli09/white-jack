#include <stdio.h>                                              // input/output (printf)
#include <stdlib.h>                                             // numeri casuali: rand e srand
#include <time.h>                                               // l'orario attuale: time

#define NUM_CARTE 52                                            // carte nel mazzo
#define MAX_MANO 12                                             // massimo di carte in una mano (con più di 11 si sfora 21 per forza)

enum Seme { CUORI, QUADRI, FIORI, PICCHE };                     // i 4 semi

struct Carta {                                                  // una carta...
    int valore;                                                 // ...ha un valore da 1 a 13
    enum Seme seme;                                             // ...e un seme
};                                                              // fine della struct Carta

struct Mano {                                                   // una mano è composta da...
    struct Carta carte[MAX_MANO];                               // ...un elenco di carte
    int numero;                                                 // ...e dal numero di carte che contiene adesso
};                                                              // fine della struct Mano

const char *nomi_semi[] = { "Cuori", "Quadri", "Fiori", "Picche" };            // testi dei semi
const char *nomi_valori[] = { "", "Asso", "2", "3", "4", "5", "6", "7",        // testi dei valori (posizione 0 vuota)
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
