#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ww "🆆 "
#define aa "🅰 "
#define ss "🆂 "
#define dd "🅳 "
#define rr "🆁 "
#define xx "🆇 "

/**
 * Funzione che stampa il titolo all'avvio del gioco.
 */

void title(){
   system("clear");
   printf(
         "\t\x1b[35m __   __  _______  _______  _______  ______    ___   _______ "
         "\n\t\x1b[35m|  |_|  ||       ||       ||       ||    _ |  |   | |       |"
         "\n\t\x1b[35m|       ||_     _||    ___||_     _||   | ||  |   | |  _____|"
         "\n\t\x1b[36m|       |  |   |  |   |___   |   |  |   |_||_ |   | | |_____ "
         "\n\t\x1b[36m |     |   |   |  |    ___|  |   |  |    __  ||   | |_____  |"
         "\n\t\x1b[34m|   _   |  |   |  |   |___   |   |  |   |  | ||   |  _____| |"
         "\n\t\x1b[34m|__| |__|  |___|  |_______|  |___|  |___|  |_||___| |_______|"
         "\n\n\x1b[0m"); 
}

/**
 * Funzione che stampa a schermo le istruzioni del gioco.
 */

void instructions(){
   title();
   sleep(1);
   printf("\n\n");
   printf("\tInstructions:\n\n");
   printf("\tTo rotate press: %s", rr);
   printf("\n\n\tTo move press:\n\n");
   printf("\t%s%s%s\n", aa, ss, dd);
   printf("\n\n\t To exit press: %s", xx);
}
