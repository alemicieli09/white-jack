#ifndef CARTE_H                                                 // include guard: se CARTE_H non esiste ancora...
#define CARTE_H                                                 // ...lo definisce, così il file viene letto una volta sola

#define NUM_CARTE 52                                            // carte in un mazzo
#define NUM_MAZZI 6                                             // quanti mazzi si usano insieme (la "scarpa" dei casinò)
#define CARTE_SCARPA (NUM_CARTE * NUM_MAZZI)                    // carte totali nella scarpa: 52 x 6 = 312
#define SOGLIA_RIMESCOLA 78                                     // se restano meno carte di così (un quarto), si rimescola

enum Seme { CUORI, QUADRI, FIORI, PICCHE };                     // i 4 semi

struct Carta {                                                  // una carta...
    int valore;                                                 // ...ha un valore da 1 a 13
    enum Seme seme;                                             // ...e un seme
};                                                              // fine della struct

struct Scarpa {                                                 // la scarpa è il contenitore dei 6 mazzi: da qui si pescano le carte
    struct Carta carte[CARTE_SCARPA];                           // tutte le carte, già mescolate
    int prossima;                                               // posizione della prossima carta da pescare
};                                                              // fine della struct

void stampa_carta(struct Carta c);                              // dichiarazione: il corpo è in carte.c (qui solo nome e parametri)
void crea_mazzo(struct Carta mazzo[]);                          // dichiarazione di crea_mazzo
void mescola_mazzo(struct Carta mazzo[], int n);                // dichiarazione di mescola_mazzo
void scarpa_rimescola(struct Scarpa *s);                        // dichiarazione: ricrea i 6 mazzi e li mescola
struct Carta scarpa_pesca(struct Scarpa *s);                    // dichiarazione: prende la carta in cima alla scarpa
int scarpa_da_rimescolare(const struct Scarpa *s);              // dichiarazione: vero se restano poche carte

#endif                                                          // fine dell'include guard

