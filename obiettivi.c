#include <stdio.h>                                              // printf
#include "grafica.h"                                            // i colori (VERDE, GIALLO, RESET)
#include "obiettivi.h"                                          // la struct e le dichiarazioni di questo modulo

static const char *nomi[NUM_OBIETTIVI] = {                      // i nomi degli obiettivi (static: visibili solo in questo file)
    "Primo blackjack",                                          // obiettivo 0
    "Cinque di fila",                                           // obiettivo 1
    "Cinquecento"                                               // obiettivo 2
};                                                              // fine dell'elenco dei nomi

static const char *descrizioni[NUM_OBIETTIVI] = {               // cosa bisogna fare per sbloccarli, nello stesso ordine
    "fai un blackjack naturale",                                // obiettivo 0
    "vinci 5 mani consecutive",                                 // obiettivo 1
    "arriva a 500 fiches"                                       // obiettivo 2
};                                                              // fine dell'elenco delle descrizioni

void obiettivi_init(struct Obiettivi *o) {                      // azzera gli obiettivi (o è un puntatore: la struttura originale)
    for (int i = 0; i < NUM_OBIETTIVI; i++) {                   // per ogni obiettivo...
        o->sbloccato[i] = 0;                                    // ...parte bloccato
    }                                                           // fine del ciclo
}                                                               // fine di obiettivi_init

void obiettivi_controlla(struct Obiettivi *o, const struct Statistiche *s) {   // controlla le statistiche e sblocca gli obiettivi raggiunti
    int raggiunto[NUM_OBIETTIVI];                               // per ogni obiettivo: la condizione è soddisfatta?
    raggiunto[0] = s->blackjack >= 1;                           // 0: almeno un blackjack (il confronto vale 1 se vero, 0 se falso)
    raggiunto[1] = s->serie_max >= 5;                           // 1: una serie di almeno 5 vittorie consecutive
    raggiunto[2] = s->record >= 500;                            // 2: il saldo ha toccato almeno 500 fiches
    for (int i = 0; i < NUM_OBIETTIVI; i++) {                   // per ogni obiettivo...
        if (raggiunto[i] && !o->sbloccato[i]) {                 // ...se è raggiunto e non era ancora sbloccato (! = "non")...
            o->sbloccato[i] = 1;                                // ...lo sblocca...
            printf(VERDE "\n★ Obiettivo sbloccato: %s" RESET " (%s)\n", nomi[i], descrizioni[i]);   // ...e lo annuncia
        }                                                       // fine del controllo
    }                                                           // fine del ciclo
}                                                               // fine di obiettivi_controlla

void obiettivi_mostra(const struct Obiettivi *o) {              // mostra l'elenco con lo stato di ognuno
    printf("\n" GIALLO "Obiettivi" RESET "\n");                 // titolo in giallo
    for (int i = 0; i < NUM_OBIETTIVI; i++) {                   // per ogni obiettivo...
        printf("  [%c] %s: %s\n", o->sbloccato[i] ? 'x' : ' ', nomi[i], descrizioni[i]);   // ...[x] se sbloccato, [ ] se no (condizione ? se_vero : se_falso)
    }                                                           // fine del ciclo
    printf("\n");                                               // riga vuota finale
}                                                               // fine di obiettivi_mostra
