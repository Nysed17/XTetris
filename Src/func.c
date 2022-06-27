#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "title.c"
#define x 20
#define y 12
#define bl "▣"

char one[4][4] = {{'n','n','#','n'},{'n','n','#','n'},{'n','n','#','n'},{'n','n','#','n'}}; /* #### */

char two[4][4] = {{'#','#','n','n'},{'n','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; /* ##
## */
char three[4][4] = {{'n','#','#','n'},{'#','#','n','n'},{'n','n','n','n'},{'n','n','n','n'}}; /* ##
## */
char four[4][4] = {{'n','#','n','n'},{'n','#','n','n'},{'#','#','n','n'},{'n','n','n','n'}}; /* # 
#
## */
char five[4][4] = {{'n','#','#','n'},{'n','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; /* ##
## */
char six[4][4] = {{'n','#','n','n'},{'n','#','n','n'},{'n','#','#','n'},{'n','n','n','n'}}; /* #
#
## */
char seven[4][4] = {{'n','#','n','n'},{'#','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; /* #
### */

/**
 * Struct che contiene il numero di tetramini disponibili.
 */

typedef struct numberoftet{
   int tet1;
   int tet2;
   int tet3;
   int tet4;
   int tet5;
   int tet6;
   int tet7;
} ntet;

/**
 * Struct che contiene le variabili per determinare la posizione, come per esempio
 * movx e movy, poi checkblock che serve a verificare la collisione, le altre servono 
 * per colore, forma e dimensione dei tetramini.
 */

typedef struct movetet{
   char tetr1[4][4]; /*printed tetromino*/
   int movx; /*x 1st block of tetr*/
   int movy; /*y 1st block of tetr*/
   int movx2;
   int movy2;
   int checkblock;
   int g; /*rotation check*/
   int shape; /*collision check*/
   int color; /*color check*/
   int dist;
   int onet; /*size of one*/
   int alltet; /*size of other tetr*/
   int switchp;
} mtet;

/**
 * Struct con gli lementi del punteggio.
 */

typedef struct gameobj{
   int gameover;
   int score;
   int score2p;
   int gamemode;
} game;

/**
 * Posiziona il cursore alle coordinate posx e posy.
 */

void gotoxy(int posx, int posy){  
   printf("%c[%d;%df",0x1B,posy,posx);
}

/**
 * Funzione per stampare lo score del giocatore.
 */

void scorecheck(int score){
   printf("\x1b[32mScore:\x1b[32m %d\x1b[0m", score);
}

/**
 * La funzione stoptetr controlla la collisione con il suolo
 * e la collisione dal basso.
 */

int stoptetr(char Tab[x][y], mtet* obj);

/**
 * Funzione che controlla le collisioni generali.
 */

void otherblockcollision(char Tab[x][y], mtet* obj){ 
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
   obj->checkblock = 0;
}

/**
 * Determina lo spostamento del giocatore, in questo caso la funzione
 * viene utilizzata per la modalità giocatore singolo e per il p1 nella
 * modalità multigiocatore.
 */

void movep1(char Tab[x][y], mtet* obj, game* gm){
   int d;
   switch(getchar()){
      case 'a':
         if (obj->checkblock != 2){
            obj->movx--;
         }
         break;
      case 's':
         obj->movy++;
         break;
      case 'd':
         if (obj->checkblock != 1){
            obj->movx++;
         }
         break;
      case 'x':
         system("stty echo");
         printf("\n\nAre you sure you want to quit?\n[1] yes\n[2] no\n");
         scanf("%d", &d);
         if (d == 1){ 
            gm->gameover = 1;
         } else if (d == 2){ 
            gm->gameover = 0;
            system("stty -echo");
            system("stty -icanon");
         }
         break;
      case 'r':
         if (obj->checkblock == 0){
            obj->g = 1;
         }
         break;
      case ' ':
         if (stoptetr(Tab, obj) != 1){
            obj->movy++;
         }
         break;
   }
}

/**
 * Determina il movimento del p2 nella modalità multigiocatore.
 */

void movep2(char Tab2[x][y], mtet* obj, game* gm){
   int d;
   switch(getchar()){
      case 'a':
         if (obj->checkblock != 2){
            obj->movx2--;
         }
         break;
      case 's':
         obj->movy2++;
         break;
      case 'd':
         if (obj->checkblock != 1){
            obj->movx2++;
         }
         break;
      case 'x':
         system("stty echo");
         printf("\n\nAre you sure you want to quit?\n[1] yes\n[2] no\n");
         scanf("%d", &d);
         if (d == 1){
            gm->gameover = 1;
         } else if (d == 2){ 
            gm->gameover = 0;
            system("stty -echo");
            system("stty -icanon");
         }
         break;
      case 'r':
         if (obj->checkblock == 0){
            obj->g = 1;
         }
         break;
      case ' ':
         if (stoptetr(Tab2, obj) != 1){
            obj->movy2++;
         }
         break;
   }
}

/**
 * Funzione che assegna il colore al tetramino.
 */

void colors(mtet* obj){
   int i, j;
   for (i = 0 ; i < 4 ; i++){
      for (j = 0 ; j < 4 ; j++){
         if (obj->shape == 0) {obj->color = 1; return;}
         else if (obj->tetr1[i][j] == two[i][j]) {obj->color = 2; return;}
         else if (obj->tetr1[i][j] == three[i][j]) {obj->color = 3; return;}
         else if (obj->tetr1[i][j] == four[i][j]) {obj->color = 4; return;}
         else if (obj->tetr1[i][j] == five[i][j]) {obj->color = 5; return;}
         else if (obj->tetr1[i][j] == six[i][j]) {obj->color = 6; return;} 
         else if (obj->tetr1[i][j] == seven[i][j]) {obj->color = 7; return;}
      }
   }
   obj->color = 0;
}

/**
 * Funzione che stampa la tabella secondo diversi criteri.
 */

void PrintCharTab(char c, mtet* obj){
   switch (c) {                
      case 'x': /*floor*/
         printf("\x1b[34m━━\x1b[0m");
         break;
      case '1': /*left wall*/
         printf("\x1b[34m┃ \x1b[0m");
         break;
      case '2': /*right wall*/
         printf("\x1b[34m┃\x1b[0m");
         break;
      case '3': /*left corner*/
         printf("\x1b[34m┗━\x1b[0m");
         break;
      case '4': /*right corner*/
         printf("\x1b[34m┛\x1b[0m");
         break;
      case 'n': /*null*/
         printf("  ");
         break;
      case 'm': /*topnull*/
         printf("  ");
         break;
      case '#': /*tetramino*/
         if (obj->color == 0) {printf("\x1b[36m%s \x1b[0m", bl);}
         if (obj->color == 1) {printf("\x1b[31m%s \x1b[0m", bl);}
         if (obj->color == 2) {printf("\x1b[32m%s \x1b[0m", bl);}
         if (obj->color == 3) {printf("\x1b[34m%s \x1b[0m", bl);}
         if (obj->color == 4) {printf("\x1b[33m%s \x1b[0m", bl);}
         if (obj->color == 5) {printf("\x1b[37m%s \x1b[0m", bl);}
         if (obj->color == 6) {printf("\x1b[35m%s \x1b[0m", bl);}
         break;
      case 'k': /*blocked tetramino*/
         printf("\x1b[36m%s \x1b[0m", bl);
         break;
      case 'o':
         printf("\x1b[34m%s \x1b[0m", bl);
         break;
      case 'l':
         printf("\x1b[31m%s \x1b[0m", bl);
         break;
      case 'z':
         printf("\x1b[35m%s \x1b[0m", bl);
         break;
      case 'h':
         printf("\x1b[32m%s \x1b[0m", bl);
         break;
      case 'c':
         printf("\x1b[37m%s \x1b[0m", bl);
         break;
      case 'v':
         printf("\x1b[33m%s \x1b[0m", bl);
         break;
      case 'u':
         printf("\x1b[35m%s \x1b[0m", bl);
         break;
      default:
         printf("\x1b[35m%c\x1b[0m ", c);
         break;
   }
}

/**
 * Funzione importante che copia il valore di uno dei tetramini all'interno di 
 * tetr1, variabile che viene poi stampata ad ogni ciclo.
 */

void copyblock(char tetr[4][4], char tet[4][4]){
   int i, j;
   for (i = 0 ; i < 4 ; i++){
      for (j = 0 ; j < 4 ; j++){
         tetr[i][j] = tet[i][j];
      }
   }
}

/**
 * Funzione per la rotazione.
 */

void rotate_process(char tab[x][y], mtet* obj, int size){
   char flag[4][4];
   int i, j;
   int k, f;
   for (i = 0 ; i < 4 ; i++){
      for (j = 0 ; j < 4 ; j++){
         flag[size-j-1][i] = obj->tetr1[i][j];
      }
   }
   for (k = 0 ; k < 4 ; k++){
      for (f = 0 ; f < 4 ; f++){
         obj->tetr1[k][f] = flag[k][f];
      }
   }
}

/**
 * Funzione che rimuove tutti i caratteri indesiderati dalla tabella.
 */

void cleartab(char Tab[x][y], int movx, int movy){
   int i, j;
   for (i = 0 ; i < x ; i++){
      for (j = 0 ; j < y ; j++){
         if (Tab[i][j] == '#'){
            Tab[i][j] = 'n';
         }
      }
   }
}

/**
 * Funzione che genera numeri random che poi vengono passati a randomblock().
 */

int randomnumber(){
   int num;
   num = random()%7;
   if (num == 0) return 1;
   if (num == 1) return 2;
   if (num == 2) return 3;
   if (num == 3) return 4;
   if (num == 4) return 5;
   if (num == 5) return 6;
   if (num == 6) return 7;
   return 0;
}

/**
 * Funzione che controlla se ci sono abbastanza pezzi di un determinato tipo.
 * Se i pezzi sono più di 0 allora la funzione ritorna 1, altrimenti genera un nuovo numero
 * random.
 */

int checkrandom(int n, ntet* pezzo){
   switch (n){
      case 1:
         if (pezzo->tet1 > 0) return 1;
         break;
      case 2:
         if (pezzo->tet3 > 0) return 1;
         break;
      case 3:
         if (pezzo->tet4 > 0) return 1;
         break;
      case 4:
         if (pezzo->tet6 > 0) return 1;
         break;
      case 5:
         if (pezzo->tet7 > 0) return 1;
         break;
      case 6: 
         if (pezzo->tet5 > 0) return 1;
         break;
      case 7:
         if (pezzo->tet2 > 0) return 1;
         break;
   }
   return 0;
}

/**
 * Funzione che assegna i pezzi in base al numero randomico 
 * generato dalla funzione randomnumber().
 */

void randomblock(ntet* pezzo, mtet* obj){
   int temp, valid = 0;
   srandom(time(0));
   while (valid == 0){
      temp = randomnumber();
      valid = checkrandom(temp, pezzo);
   }
   if (temp == 1) { copyblock(obj->tetr1, one); obj->color = 0; obj->shape = 0; pezzo->tet1--; }
   if (temp == 2) { copyblock(obj->tetr1, two); obj->color = 1; obj->shape = 1; pezzo->tet3--; }
   if (temp == 3) { copyblock(obj->tetr1, three); obj->color = 2; obj->shape = 1; pezzo->tet4--; }
   if (temp == 4) { copyblock(obj->tetr1, four); obj->color = 3; obj->shape = 1; pezzo->tet6--; }
   if (temp == 5) { copyblock(obj->tetr1, five); obj->color = 4; obj->shape = 1; pezzo->tet7--; }
   if (temp == 6) { copyblock(obj->tetr1, six); obj->color = 5; obj->shape = 1; pezzo->tet5--; }
   if (temp == 7) { copyblock(obj->tetr1, seven); obj->color = 6; obj->shape = 1; pezzo->tet2--; }
}

/**
 * Funzione che va a sostituire alcuni caratteri della tabella di gioco con 
 * i blocchi, che poi formano i tertamini.
 */

void changetab(char Tab[x][y], char Tab2[x][y], mtet* obj, char tetr[4][4], int movx, int movy, int movx2, int movy2){
   int i, j;
   int k, f;
   if (obj->switchp == 0){
      for (i = 0; i < 4; i++){
         for (j = 0; j < 4; j++){
            if (tetr[i][j] == '#'){
               Tab[movy + i][movx + j] = tetr[i][j];
            }
         }
      }
   } else if (obj->switchp == 1){
      for (k = 0; k < 4; k++){
         for (f = 0; f < 4; f++){
            if (tetr[k][f] == '#'){
               Tab2[movy2 + k][movx2 + f] = tetr[k][f];
            }
         }
      }
   }
}

/**
 * Funzione per selezionare la modalità di gioco.
 */

void choose(game* gm){
   int m;
   title();
   sleep(1);
   printf("\n\n");
   printf("\t\x1b[34m[1] SinglePlayer\n\t[2] MultiPlayer\n\n");
   printf("\tSelect a mode: \x1b[0m");
   scanf("%d", &m);
   if (m < 3 && m > 0){
      switch (m){
         case 1:
            sleep(1); printf("\n\t\x1b[32mSelected mode -> SinglePlayer\x1b[0m \n\n\n");
            gm->gamemode = 1;
            break;
         case 2:
            sleep(1); printf("\n\t\x1b[32mSelected mode -> MultiPlayer\x1b[0m \n\n\n");
            gm->gamemode = 2;
            break;
      }
   } else{
      sleep(1); printf("\t\x1b[31mmode n. %d doesn't exist\x1b[0m \n", m);
      sleep(1); system("clear");
   }
}

/**
 * Funzione che stampa la Gui di gioco, dove vengono mostrati
 * i pezzi rimanenti.
 */

void tetrgui(ntet* pezzo, game* gm){ 
   if (gm->gamemode == 1){
      printf("\n\t\t\t\t\x1b[36m  %s %s %s %s  \x1b[0m[1] %d", bl, bl, bl, bl, pezzo->tet1);
      printf("\n\n\t\t\t\t    \x1b[35m%s\n\t\t\t\t  %s %s %s    \x1b[0m[2] %d", bl, bl, bl, bl, pezzo->tet2);
      printf("\n\n\t\t\t\t\x1b[31m  %s %s\n\t\t\t\t\x1b[31m    %s %s    \x1b[0m[3] %d", bl, bl, bl, bl, pezzo->tet3);
      printf("\n\n\t\t\t\t\x1b[32m    %s %s\n\t\t\t\t\x1b[32m  %s %s      \x1b[0m[4] %d", bl, bl, bl, bl, pezzo->tet4);
      printf("\n\n\t\t\t\t\x1b[34m    %s\n\t\t\t\t    %s      \x1b[0m[5] %d\n\t\t\t\t\x1b[34m  %s %s    \x1b[0m", bl, bl, pezzo->tet6, bl, bl);
      printf("\n\n\t\t\t\t\x1b[37m    %s\n\t\t\t\t    %s      \x1b[0m[6] %d\n\t\t\t\t\x1b[37m    %s %s    \x1b[0m", bl, bl, pezzo->tet5, bl, bl);
      printf("\n\n\t\t\t\t\x1b[33m    %s %s\n\t\t\t\t    %s %s    \x1b[0m[7] %d", bl, bl, bl, bl, pezzo->tet7);

   }
   if (gm->gamemode == 2){
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\x1b[36m  %s %s %s %s  \x1b[0m[1] %d", bl, bl, bl, bl, pezzo->tet1);
      printf("\n\n\t\t\t\t    \x1b[35m%s\n\t\t\t\t  %s %s %s    \x1b[0m[2] %d", bl, bl, bl, bl, pezzo->tet2);
      printf("\n\n\t\t\t\t\x1b[31m  %s %s\n\t\t\t\t\x1b[31m    %s %s    \x1b[0m[3] %d", bl, bl, bl, bl, pezzo->tet3);
      printf("\n\n\t\t\t\t\x1b[32m    %s %s\n\t\t\t\t\x1b[32m  %s %s      \x1b[0m[4] %d", bl, bl, bl, bl, pezzo->tet4);
      printf("\n\n\t\t\t\t\x1b[34m    %s\n\t\t\t\t    %s      \x1b[0m[5] %d\n\t\t\t\t\x1b[34m  %s %s    \x1b[0m", bl, bl, pezzo->tet6, bl, bl);
      printf("\n\n\t\t\t\t\x1b[37m    %s\n\t\t\t\t    %s      \x1b[0m[6] %d\n\t\t\t\t\x1b[37m    %s %s    \x1b[0m", bl, bl, pezzo->tet5, bl, bl);
      printf("\n\n\t\t\t\t\x1b[33m    %s %s\n\t\t\t\t    %s %s    \x1b[0m[7] %d", bl, bl, bl, bl, pezzo->tet7);
   }
}

/**
 * Funzione che passa la tabella a PrintCharTab() per stamparla.
 */

void tab(char Tab[x][y], mtet* obj){
   int i, j;
   for (i = 0 ; i < x ; i++ ){
      for (j = 0 ; j < y ; j++ ){
         PrintCharTab(Tab[i][j], obj);
      }
      printf("\n");
   }
}

int p;

/**
 * Funzione che va a rimuovere tutte le righe completate.
 */

int removelines(char* Tab){
   int count = 0;
   int i, j;
   for (i = 0 ; i < x ; i++){
      count = 0;
      for (j = 0 ; j < y ; j++){
         if (Tab[i*y+j] == 'k' || Tab[i*y+j] == 'z'|| Tab[i*y+j] == 'o'|| Tab[i*y+j] == 'v'|| Tab[i*y+j] == 'c'|| Tab[i*y+j] == 'l'|| Tab[i*y+j] == 'h'){
            count++; 
            if (count == y-2){
               int f = i;
               int k;
               for (k = 1 ; k < y-1 ; k++) p = i;
               Tab[f*y+k] = 'n'; return 1;
            }
            if (count > 10) return 0;
         } else if (Tab[i*y+j] == 'n' || Tab[i*y+j] == '#'){
            count = 0;
         }
      }
   }
   return 0;
}

int l = 0;
int h = 0;

/**
 * Funzione che conta quante righe di seguito sono state completate.
 */

void countlines(char* Tab){
   int count = 0;
   int i, j;
   for (i = 0 ; i < x ; i++){
      count = 0;
      for (j = 0 ; j < y ; j++){
         if (Tab[i*y+j] == 'k' || Tab[i*y+j] == 'z'|| Tab[i*y+j] == 'o'|| Tab[i*y+j] == 'v'|| Tab[i*y+j] == 'c'|| Tab[i*y+j] == 'l'|| Tab[i*y+j] == 'h'){
            count++;
            if (count == y-2){
               l++;
            }
         }
      }
   }
   h = l;
   l = 0;
}

/**
 * Funzione per il multigiocatore che va a invertire alcune righe 
 * della tabella avversaria quando vengono rimosse più di due righe in un colpo solo.
 */

void addlines(char Tab[x][y], int n){
   int i, j;
   for (i = x-n ; i < x-1 ; i++){
      for (j = 1 ; j < y-1 ; j++){
         if (Tab[i][j] == 'n') { Tab[i][j] = 'c'; }
         else Tab[i][j] = 'n';
      }
   }
}

/**
 * Funzione che aumenta i punti, del giocatore p1 e del giocatore singolo, a seconda di quante righe vengono
 * rimosse con un solo tetramino.
 */

void dupanother(char* Tab, char Tab2[x][y], game* gm){
   int n;
   countlines(Tab);
   if (h == 4){
      n = 5;
      gm->score += 12;
      h = 0;
      addlines(Tab2, n);
   } else if (h == 3){
      n = 4;
      gm->score += 6;
      h = 0;
      addlines(Tab2, n);
   } else if (h == 2){
      gm->score += 3;
      h = 0;
   } else if (h == 1){
      gm->score += 1;
      h = 0;
   }
}

/**
 * Funzione che aumenta i punti del giocatore p2 a seconda di quante righe vengono
 * rimosse con un solo tetramino.
 */

void dupanotherp2(char Tab[x][y], char* Tab2, game* gm){
   int n;
   countlines(Tab2);
   if (h == 4){
      n = 5;
      gm->score2p += 12;
      h = 0;
      addlines(Tab, n);
   } else if (h == 3){
      n = 4;
      gm->score2p += 6;
      h = 0;
      addlines(Tab, n);
   } else if (h == 2){
      gm->score2p += 3;
      h = 0;
   } else if (h == 1){
      gm->score2p += 1;
      h = 0;
   }
}

/**
 * Funzione che corregge qualche errore di stampa dei bordi della tabella.
 */

void restoreproblem(char Tab[x][y]){
   int i;
   for (i = 4 ; i < x-1 ; i++){
      Tab[i][y-1] = '2';
      Tab[i][0] = '1';
   }   
}

/**
 * Funzione strettamente collegata a removelines(), infatti quando
 * la funzione removelines() rimuove una della righe questa funzione
 * sposta in basso tutte le righe sopra.
 * (Usata per modalità singleplayer e multiplayer con p1).
 */

void checkscorep1(char Tab[x][y], mtet* obj, game* gm){
   if (removelines(*Tab) == 1){
      int i, j;
      for (i = p-1 ; i >= 0 ; i--){
         for (j = y-1 ; j >= 1 ; j--){
            Tab[i+1][j] = Tab[i][j]; 
         }
      }
   }
   restoreproblem(Tab);
   if (removelines(*Tab) == 1) checkscorep1(Tab, obj, gm);
}

/**
 * Funzione strettamente collegata a removelines(), infatti quando
 * la funzione removelines() rimuove una della righe questa funzione
 * sposta in basso tutte le righe sopra.
 * (Usata per modalità multiplayer con p2).
 */

void checkscorep2(char Tab[x][y], mtet* obj, game* gm){
   if (removelines(*Tab) == 1){
      int i, j;
      for (i = p-1 ; i >= 0 ; i--){
         for (j = y-1 ; j >= 1 ; j--){
            Tab[i+1][j] = Tab[i][j]; 
         }
      }
   }
   restoreproblem(Tab);
   if (removelines(*Tab) == 1) checkscorep2(Tab, obj, gm);
}

int stoptetr(char Tab[x][y], mtet* obj){
   int i, j;
   for (i = 0; i < x; i++){
      for (j = 0; j < y; j++){
         if (Tab[i][j] == '#'){
            obj->dist = 0;
            if (i == 18){   /*check for ground collisions*/
               int k, f;
               for (k = i - 3; k <= i + 1; k++){
                  for (f = j - 2; f <= j + 4; f++){
                     if (Tab[k][f] == '#'){
                        if (obj->color == 0) Tab[k][f] = 'k';
                        if (obj->color == 1) Tab[k][f] = 'l';
                        if (obj->color == 2) Tab[k][f] = 'h';
                        if (obj->color == 3) Tab[k][f] = 'o';
                        if (obj->color == 4) Tab[k][f] = 'v';
                        if (obj->color == 5) Tab[k][f] = 'c';
                        if (obj->color == 6) Tab[k][f] = 'z';
                     }
                  }
               }
               return 1;
            }
            if (Tab[i+1][j] == 'k' || Tab[i+1][j] == 'z' || Tab[i+1][j] == 'v' || Tab[i+1][j] == 'l' || Tab[i+1][j] == 'c' || Tab[i+1][j] == 'h' || Tab[i+1][j] == 'o'){    /*check for lower collisions*/
               int l, r;                                                                                                                                                
               for (l = i - 3 ; l <= i + 2; l++){
                  for (r = j - 2 ; r <= j + 5; r++){
                     if (Tab[l][r] == '#'){
                        if (obj->color == 0) Tab[l][r] = 'k';
                        if (obj->color == 1) Tab[l][r] = 'l';
                        if (obj->color == 2) Tab[l][r] = 'h';
                        if (obj->color == 3) Tab[l][r] = 'o';
                        if (obj->color == 4) Tab[l][r] = 'v';
                        if (obj->color == 5) Tab[l][r] = 'c';
                        if (obj->color == 6) Tab[l][r] = 'z';
                     }    
                  }
               }
               return 1;
            } 
         } 
      }
   }
   return 0;
}

/**
 * Funzione che determina la vittoria del giocatore appena
 * i tetramini sono esauriti. (Modalità singleplayer).
 */

void win(char Tab[x][y], ntet* pezzo, mtet* obj, game* gm){
   char s[4][6] = {{' ',' ',' ',' ',' ',' '},{' ','Y','O','U','!',' '}, {' ','W','O','N','!',' '},{' ',' ',' ',' ',' ',' '}};
   if (pezzo->tet1+pezzo->tet2+pezzo->tet3+pezzo->tet4+pezzo->tet5+pezzo->tet6+pezzo->tet7 == 0){
      int k, f;
      gotoxy(0,2);
      system("clear");
      for (k = 0 ; k < 4 ; k++){
         for (f = 0 ; f < 6 ; f++){
            Tab[7+k][3+f] = s[k][f];
         }
      }

      tab(Tab, obj);
      scorecheck(gm->score);
      sleep(2);
      gm->gameover = 1;
   }
}

/**
 * Funzione singleplayer che determina gameover quando un tetramino esce dalla tabella.
 */

void returngameover(char Tab[x][y], mtet* obj, game* gm){
   int i, j;
   char s[4][6] = {{' ',' ',' ',' ',' ',' '},{' ','G','A','M','E',' '}, {' ','O','V','E','R',' '},{' ',' ',' ',' ',' ',' '}};
   gotoxy(0,2);
   for (i = 0 ; i < 3 ; i++){
      for (j = 0 ; j < y ; j++){
         if (Tab[i][j] == 'k' || Tab[i][j] == 'o'|| Tab[i][j] == 'h'|| Tab[i][j] == 'l'|| Tab[i][j] == 'z'|| Tab[i][j] == 'v'|| Tab[i][j] == 'c'){
            int k, f;
            for (k = 0 ; k < 4 ; k++){
               for (f = 0 ; f < 6 ; f++){
                  Tab[7+k][3+f] = s[k][f];
               }
            }
            system("clear");
            tab(Tab, obj);
            gotoxy(5,23);
            printf("\x1b[32mYour score: \x1b[33m%d\x1b[0m", gm->score);
            gotoxy(22,25);
            sleep(2);
            exit(0);
         }
      }
   }
}

/**
 * Funzione che determina se i blocchi escono dalla tabella.
 */

int gameoverreturn(char Tab[x][y], game* gm){
   int i, j;
   for (i = 0 ; i < 3 ; i++){
      for (j = 0 ; j < y ; j++){
         if (Tab[i][j] == 'k' || Tab[i][j] == 'o'|| Tab[i][j] == 'h'|| Tab[i][j] == 'l'|| Tab[i][j] == 'z'|| Tab[i][j] == 'v'|| Tab[i][j] == 'c'){
            return 1;
         }
      }
   }
   return 0;
}

/**
 * Funzione che stampa una matrice di spazi vuoti.
 */

void spacep(char space[5][1]){
   int i, j;
   for (i = 0 ; i < 5 ; i++){
      for (j = 0 ; j < 1 ; j++){
         printf("%c", space[i][j]);
      }
      printf("\n");
   }
}

/**
 * Funzione multiplayer di gameover.
 */

void mod2gameover(char Tab[x][y], char Tab2[x][y], mtet* obj, game* gm, ntet* pezzo){
   int retgame = gameoverreturn(Tab, gm);
   int k, f;
   char space[5][1] = {{' '},{' '},{' '},{' '},{' '}};

   char s[4][6] = {{' ',' ',' ',' ',' ',' '},{' ','O','N','E','!',' '}, {' ','W','O','N','!',' '},{' ',' ',' ',' ',' ',' '}};
   char s2[4][6] = {{' ',' ',' ',' ',' ',' '},{' ','T','W','O','!',' '}, {' ','W','O','N','!',' '},{' ',' ',' ',' ',' ',' '}};
   char s3[4][6] = {{' ',' ',' ',' ',' ',' '},{' ',' ','N','O',' ',' '}, {'W','I','N','N','E','R'},{' ',' ',' ',' ',' ',' '}};
   gotoxy(0,2);
   if (pezzo->tet1+pezzo->tet2+pezzo->tet3+pezzo->tet4+pezzo->tet5+pezzo->tet6+pezzo->tet7 == 0){
      retgame = 1;
   }
   if (retgame == 1){
      if (gm->score > gm->score2p){
         sleep(1);
         system("clear");
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab[7+k][3+f] = s[k][f];
            }
         }
         tab(Tab, obj);
         printf("    P1 score:\x1b[32m %d", gm->score);
         spacep(space);
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      } else if (gm->score < gm->score2p){
         sleep(1);
         system("clear");
         tab(Tab, obj);
         printf("    P1 score: %d", gm->score);
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab2[7+k][3+f] = s2[k][f];
            }
         }
         spacep(space);
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      } else if (gm->score == gm->score2p){
         sleep(1);
         system("clear");
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab[7+k][3+f] = s3[k][f];
               Tab2[7+k][3+f] = s3[k][f];
            }
         }
         tab(Tab, obj);
         printf("    P1 score: %d", gm->score);
         spacep(space);
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      }
   }
   if (retgame == 1){
      if (gm->score > gm->score2p){
         sleep(1);
         system("clear");
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab[7+k][3+f] = s[k][f];
            }
         }
         tab(Tab, obj);
         printf("    P1 score: %d", gm->score);
         spacep(space);
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      } else if (gm->score < gm->score2p){
         sleep(1);
         system("clear");
         tab(Tab, obj);
         printf("    P1 score: %d", gm->score);
         spacep(space);
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab2[7+k][3+f] = s2[k][f];
            }
         }
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      } else if (gm->score == gm->score2p){
         sleep(1);
         system("clear");
         for (k = 0 ; k < 4 ; k++){
            for (f = 0 ; f < 6 ; f++){
               Tab[7+k][3+f] = s3[k][f];
               Tab2[7+k][3+f] = s3[k][f];
            }
         }
         tab(Tab, obj);
         printf("    P1 score: %d", gm->score);
         spacep(space);
         tab(Tab2, obj);
         printf("    P2 score: %d", gm->score2p);
         sleep(2);
         exit(0);
      }
   }
}

/**
 * Init del numero di pezzi della modalità multigiocatore.
 */

void sdoppiapezzi(game* gm, ntet* pezzo){
   if (gm->gamemode == 2){
      pezzo->tet1 = 40;
      pezzo->tet2 = 40;
      pezzo->tet3 = 40;
      pezzo->tet4 = 40;
      pezzo->tet5 = 40;
      pezzo->tet6 = 40;
      pezzo->tet7 = 40;
   }
}

/**
 * Init del numero di pezzi della modalità singleplayer.
 */

void initntet(ntet* pezzo){
   pezzo->tet1 = 20;
   pezzo->tet1 = 20;
   pezzo->tet2 = 20;
   pezzo->tet3 = 20;
   pezzo->tet4 = 20;
   pezzo->tet5 = 20;
   pezzo->tet6 = 20;
   pezzo->tet7 = 20;
}

/**
 * Init delle variabili di movimento, colore, forma e altre generalità.
 */

void initmtet(mtet* obj){
   obj->tetr1;
   obj->movx = 4;
   obj->movy = 0;
   obj->movx2 = 4;
   obj->movy2 = 0;
   obj->shape = 0;
   obj->g = 0;
   obj->checkblock = 0;
   obj->color = 0;
   obj->dist = 0;
   obj->onet = 4;
   obj->alltet = 3;
   obj->switchp = 0;
}

/**
 * Init degli elementi di punteggio.
 */

void initgame(game* gm){
   gm->gameover = 0;
   gm->score = 0;
   gm->score2p = 0;
   gm->gamemode = 0;
}
