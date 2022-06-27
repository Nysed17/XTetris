#include <stdio.h>
#include <stdlib.h>
#include "func.c"

/**
 * Funzione che controlla le collisioni nella tabella di p2 (multigiocatore).
 */

void mod2collision(char Tab[x][y], mtet* obj){ 
   int i, j;
   for (i = 0 ; i < x ; i++)
      for (j = 0 ; j < y ; j++)
         if (Tab[i][j] == '#'){
            int k, f;
            for (k = 0; k < 4; k++){
               for (f = 0; f < 4; f++){
                  if (Tab[i+k][j+f] == '#'){
                     if (Tab[i+k][j+f+1] == '2' || Tab[i+k][j+f+1] == 'k' || Tab[i+k][j+f+1] == 'z' || Tab[i+k][j+f+1] == 'v' || Tab[i+k][j+f+1] == 'l' || Tab[i+k][j+f+1] == 'c' || Tab[i+k][j+f+1] == 'h' || Tab[i+k][j+f+1] == 'o' || Tab[i+k][j+f+1] == 'm'){
                        obj->checkblock = 1;
                        return;
                     } else if (Tab[i+k][j+f-1] == '1' ||  Tab[i+k][j+f-1] == 'k' || Tab[i+k][j+f-1] == 'z' || Tab[i+k][j+f-1] == 'v' || Tab[i+k][j+f-1] == 'l' || Tab[i+k][j+f-1] == 'c' || Tab[i+k][j+f-1] == 'h' || Tab[i+k][j+f-1] == 'o' || Tab[i+k][j+f-1] == 'm'){
                        obj->checkblock = 2;
                        return;
                     }
                  }    
               }
            }
         }
}

/**
 * Funzione che contiene tutte le funzioni organizzate per
 * eseguire la modalità singleplayer.
 */

void mod1(char Tab[x][y], char Tab2[x][y], ntet* pezzo, mtet* obj, game* gm){
   printf("\n\n\n\n");
   changetab(Tab, Tab2, obj, obj->tetr1, obj->movx, obj->movy, obj->movx2, obj->movy2);
   gotoxy(0,2);
   tetrgui(pezzo, gm);
   gotoxy(0,2);
   tab(Tab, obj);
   otherblockcollision(Tab, obj);
   if (stoptetr(Tab, obj) == 1){
      randomblock(pezzo, obj);
      obj->movx = 4;
      obj->movy = 0;
   }
   cleartab(Tab, obj->movx, obj->movy);
   dupanother(*Tab, Tab2, gm);
   checkscorep1(Tab, obj, gm);
   gotoxy(0,2);
   returngameover(Tab, obj, gm);
   gotoxy(9,23);
   scorecheck(gm->score);
   win(Tab, pezzo, obj, gm);
}

/**
 * Funzione per stampare spazi.
 */

void printspace(char space[5][1]){
   int i, j;
   for (i = 0 ; i < 5 ; i++){
      for (j = 0 ; j < 1 ; j++){
         printf("%c", space[i][j]);
      }
      printf("\n");
   }
}

/**
 * Funzione contenente altre funzioni organizzate per eseguire
 * la modalità multigiocatore.
 */

void mod2(char Tab[x][y], char Tab2[x][y], ntet* pezzo, mtet* obj, game* gm){
   char space[5][1] = {{' '},
      {' '},
      {' '},
      {' '},
      {' '}};
   printf("\n\n");
   changetab(Tab, Tab2, obj, obj->tetr1, obj->movx, obj->movy, obj->movx2, obj->movy2);
   printf("\n\n\n\n\n\n");
   gotoxy(0,2);
   tetrgui(pezzo, gm);
   gotoxy(0,2);
   tab(Tab, obj);
   otherblockcollision(Tab, obj);
   if (stoptetr(Tab, obj) == 1){
      cleartab(Tab, obj->movx, obj->movy);
      randomblock(pezzo, obj);
      obj->movx = 4;
      obj->movy = 0;
      obj->switchp = 2;
      obj->switchp = 1;
   }
   cleartab(Tab, obj->movx, obj->movy);
   printspace(space);
   if (obj->switchp == 1){ changetab(Tab, Tab2, obj, obj->tetr1, obj->movx, obj->movy, obj->movx2, obj->movy2);}
   tab(Tab2, obj);
   mod2collision(Tab2, obj);
   if (stoptetr(Tab2, obj) == 1){
      randomblock(pezzo, obj);
      obj->movx2 = 4;
      obj->movy2 = 0;
      obj->switchp = 2;
      obj->switchp = 0;
   }
   cleartab(Tab2, obj->movx2, obj->movy2);
   dupanother(*Tab, Tab2, gm);
   checkscorep1(Tab, obj, gm);
   dupanotherp2(Tab, *Tab2, gm);
   checkscorep2(Tab2, obj, gm);
   gotoxy(0,2);
   mod2gameover(Tab, Tab2, obj, gm, pezzo);
   gotoxy(7,23);
   printf("P1 "); scorecheck(gm->score);
   gotoxy(7, 48);
   printf("P2 "); scorecheck(gm->score2p);
}
