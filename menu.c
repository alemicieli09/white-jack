#include <stdio.h>                                              // printf, scanf, getchar
#include "grafica.h"                                            // i colori (GIALLO, ROSSO, RESET)
#include "menu.h"                                               // le dichiarazioni di questo modulo

void mostra_logo(void) {                                        // disegna il logo, 5 righe: WHITE in giallo e JACK in rosso
    printf("\n");                                               // riga vuota sopra il logo
    printf("  " GIALLO "█   █ █   █ ███ █████ █████" RESET "   " ROSSO "  ███  ███   ████ █   █" RESET "\n");                    // riga 0 del logo
    printf("  " GIALLO "█   █ █   █  █    █   █    " RESET "   " ROSSO "   █  █   █ █     █  █" RESET "\n");                    // riga 1 del logo
    printf("  " GIALLO "█ █ █ █████  █    █   ████ " RESET "   " ROSSO "   █  █████ █     ███" RESET "\n");                    // riga 2 del logo
    printf("  " GIALLO "██ ██ █   █  █    █   █    " RESET "   " ROSSO "█  █  █   █ █     █  █" RESET "\n");                    // riga 3 del logo
    printf("  " GIALLO "█   █ █   █ ███   █   █████" RESET "   " ROSSO " ██   █   █  ████ █   █" RESET "\n");                    // riga 4 del logo
    printf("\n  Blackjack for the terminal\n\n");                // sottotitolo
}                                                               // fine di mostra_logo

int menu_principale(void) {                                     // mostra il menu e restituisce la scelta valida (da 1 a 4)
    int scelta;                                                 // qui memorizza il numero scritto
    while (1) {                                                 // ciclo infinito: se ne esce con return
        printf("  1) Gioca\n");                                 // prima voce
        printf("  2) Regole\n");                                // seconda voce
        printf("  3) Obiettivi\n");                             // terza voce
        printf("  4) Esci\n");                                  // quarta voce
        printf("\n  Scegli (1-4): ");                           // domanda
        int letti = scanf("%d", &scelta);                       // legge un intero; restituisce quanti valori ha letto
        if (letti == EOF) {                                     // se l'input è finito (es. Ctrl+D)...
            return 4;                                           // ...esce come se avesse scelto "Esci"
        }                                                       // fine del controllo
        if (letti != 1) {                                       // se non ha scritto un numero...
            int c;                                              // carattere letto
            while ((c = getchar()) != '\n' && c != EOF) {       // ...scarta il resto della riga
            }                                                   // il ciclo non ha altro da fare
        } else if (scelta >= 1 && scelta <= 4) {                // altrimenti, se il numero è tra 1 e 4...
            return scelta;                                      // ...è valido: lo restituisce
        }                                                       // fine dei controlli
        printf("\n  Scelta non valida.\n\n");                    // avvisa e ricomincia
    }                                                           // fine del ciclo
}                                                               // fine di menu_principale

void mostra_regole(void) {                                      // spiega le regole del gioco e i comandi
    printf("\n" GIALLO "Regole" RESET "\n");                    // titolo in giallo
    printf("- Vince chi si avvicina di più a 21 senza superarlo.\n");                  // obiettivo
    printf("- Le carte da 2 a 10 valgono il loro numero; J, Q, K valgono 10.\n");       // valori
    printf("- L'Asso vale 11, oppure 1 se con 11 si supererebbe 21.\n");                // asso
    printf("- Chi supera 21 sballa e perde.\n");                                        // sballo
    printf("- Il banco pesca finché ha meno di 17 punti.\n");                          // banco
    printf("- Un 21 con le prime due carte è un blackjack: paga 3 a 2.\n");            // blackjack
    printf("- Con un pareggio la puntata ti torna indietro.\n");                        // pareggio
    printf("- Si gioca con 6 mazzi, rimescolati quando restano poche carte.\n\n");      // scarpa
    printf(GIALLO "Comandi" RESET "\n");                        // titolo in giallo
    printf("- c = pesca una carta\n");                                                 // pescare
    printf("- s = fermati\n");                                                         // stare
    printf("- d = raddoppia: la puntata raddoppia e prendi una sola carta.\n");        // double down
    printf("  Si può solo con le prime due carte e se hai abbastanza fiches.\n");      // condizioni del raddoppio
    printf("- p = dividi: con due carte uguali (stesso numero o figura) giochi due\n"); // split
    printf("  mani, ognuna con la sua puntata. Serve avere abbastanza fiches.\n");     // condizioni della divisione
    printf("  Dopo la divisione non si può raddoppiare.\n\n");                         // limite
}                                                               // fine di mostra_regole
