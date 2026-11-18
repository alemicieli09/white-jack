#ifndef OBIETTIVI_H                                             // include guard
#define OBIETTIVI_H                                             // definisce OBIETTIVI_H

#include "stats.h"                                              // servono le statistiche per controllare gli obiettivi

#define NUM_OBIETTIVI 3                                         // quanti obiettivi ci sono

struct Obiettivi {                                              // lo stato degli obiettivi
    int sbloccato[NUM_OBIETTIVI];                               // per ogni obiettivo: 1 = sbloccato, 0 = ancora da sbloccare
};                                                              // fine della struct

void obiettivi_init(struct Obiettivi *o);                       // dichiarazione: tutti gli obiettivi partono bloccati
void obiettivi_controlla(struct Obiettivi *o, const struct Statistiche *s);   // dichiarazione: sblocca (e annuncia) quelli raggiunti
void obiettivi_mostra(const struct Obiettivi *o);               // dichiarazione: mostra l'elenco degli obiettivi

#endif                                                          // fine dell'include guard
