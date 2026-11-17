#ifndef CARTE_H                                                 // include guard: se CARTE_H non esiste ancora...
#define CARTE_H                                                 // ...lo definisce, così il file viene letto una volta sola

#define NUM_CARTE 52                                            // carte nel mazzo

enum Seme { CUORI, QUADRI, FIORI, PICCHE };                     // i 4 semi

struct Carta {                                                  // una carta...
    int valore;                                                 // ...ha un valore da 1 a 13
    enum Seme seme;                                             // ...e un seme
};                                                              // fine della struct

void stampa_carta(struct Carta c);                              // dichiarazione: il corpo è in carte.c (qui solo nome e parametri)
void crea_mazzo(struct Carta mazzo[]);                          // dichiarazione di crea_mazzo
void mescola_mazzo(struct Carta mazzo[], int n);                // dichiarazione di mescola_mazzo

#endif                                                          // fine dell'include guard
