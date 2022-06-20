#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "title.c"
#define x 20
#define y 12
#define bl "▣"

char one[4][4] = {{'n','n','#','n'},{'n','n','#','n'},{'n','n','#','n'},{'n','n','#','n'}}; //####

char two[4][4] = {{'#','#','n','n'},{'n','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; //##
                                                                                            // ##
char three[4][4] = {{'n','#','#','n'},{'#','#','n','n'},{'n','n','n','n'},{'n','n','n','n'}}; // ##
                                                                                              //##
char four[4][4] = {{'n','#','n','n'},{'n','#','n','n'},{'#','#','n','n'},{'n','n','n','n'}}; // # 
                                                                                             // #
                                                                                             //##
char five[4][4] = {{'n','#','#','n'},{'n','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; //##
                                                                                             //##
char six[4][4] = {{'n','#','n','n'},{'n','#','n','n'},{'n','#','#','n'},{'n','n','n','n'}}; //#
                                                                                            //#
                                                                                            //##
char seven[4][4] = {{'n','#','n','n'},{'#','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; // #
                                                                                              //###

typedef struct numberoftet{
   int tet1;
   int tet2;
   int tet3;
   int tet4;
   int tet5;
   int tet6;
   int tet7;
} ntet;

typedef struct movetet{
   char tetr1[4][4]; //printed tetromino
   int movx; //x 1st block of tetr
   int movy; //y 1st block of tetr
   int movx2;
   int movy2;
   int checkblock; //score P1
   int g; //rotation check
   int shape; //collision check
   int color; //color check
   int dist;
   int onet; //size of one
   int alltet; //size of other tetr
   int switchp;
} mtet;

typedef struct gameobj{
   int gameover;
   int score;
   int score2p;
   int gamemode;
} game;

void gotoxy(int posx, int posy){  
   printf("%c[%d;%df",0x1B,posy,posx);
}

void scorecheck(score){
   printf("\x1b[32mScore:\x1b[32m %d\x1b[0m", score);
}

int stoptetr(char Tab[x][y], mtet* obj);

void otherblockcollision(char Tab[x][y], mtet* obj){ 
   for (int i = 0 ; i < x ; i++)
      for (int j = 0 ; j < y ; j++)
         if (Tab[i][j] == '#'){
            for (int k = 0; k < 4; k++){
               for (int f = 0; f < 4; f++){
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
         printf("\n\nsure u want to quit?\n[1] yes\n[2] no\n");
         scanf("%d", &d);
         if (d == 1) {gm->gameover = 1;}
         else if (d == 2) {gm->gameover = 0;
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
         printf("\n\nsure u want to quit?\n[1] yes\n[2] no\n");
         scanf("%d", &d);
         if (d == 1) {gm->gameover = 1;}
         else if (d == 2) {gm->gameover = 0;
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

void colors(mtet* obj){
   for (int i = 0 ; i < 4 ; i++){
      for (int j = 0 ; j < 4 ; j++){
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

void PrintCharTab(char c, mtet* obj){
   switch (c) {                
      case 'x': //floor
         printf("\x1b[34m━━\x1b[0m");
         break;
      case '1': //left wall
         printf("\x1b[34m┃ \x1b[0m");
         break;
      case '2': //right wall
         printf("\x1b[34m┃\x1b[0m");
         break;
      case '3': //left corner
         printf("\x1b[34m┗━\x1b[0m");
         break;
      case '4': //right corner
         printf("\x1b[34m┛\x1b[0m");
         break;
      case 'n': //null
         printf("  ");
         break;
      case 'm': //topnull
         printf("  ");
         break;
      case '#': //tetramino
         if (obj->color == 0) {printf("\x1b[36m%s \x1b[0m", bl);}
         if (obj->color == 1) {printf("\x1b[31m%s \x1b[0m", bl);}
         if (obj->color == 2) {printf("\x1b[32m%s \x1b[0m", bl);}
         if (obj->color == 3) {printf("\x1b[34m%s \x1b[0m", bl);}
         if (obj->color == 4) {printf("\x1b[33m%s \x1b[0m", bl);}
         if (obj->color == 5) {printf("\x1b[37m%s \x1b[0m", bl);}
         if (obj->color == 6) {printf("\x1b[35m%s \x1b[0m", bl);}
         break;
      case 'k': //blocked tetramino
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
      default:
         printf("\x1b[35m%c\x1b[0m ", c);
         break;
   }
}

void copyblock(char tetr[4][4], char tet[4][4]){
   for (int i = 0 ; i < 4 ; i++){
      for (int j = 0 ; j < 4 ; j++){
         tetr[i][j] = tet[i][j];
      }
   }
}

void rotate_process(char tab[x][y], mtet* obj, int size){
   char flag[4][4];
   for (int i = 0 ; i < 4 ; i++){
      for (int j = 0 ; j < 4 ; j++){
         flag[size-j-1][i] = obj->tetr1[i][j];
      }
   }
   for (int i = 0 ; i < 4 ; i++){
      for (int j = 0 ; j < 4 ; j++){
         obj->tetr1[i][j] = flag[i][j];
      }
   }
}

void cleartab(char Tab[x][y], int movx, int movy){
   /*   for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
        if (Tab[i+movy][j+movx] == '#'){ 
        Tab[i+movy][j+movx] = 'n';
        }
        }
        } */
   for (int i = 0 ; i < x ; i++){
      for (int j = 0 ; j < y ; j++){
         if (Tab[i][j] == '#'){
            Tab[i][j] = 'n';
         }
      }
   }
}

int randomnumber(){
   srandom(time(0));
   int num = random()%7;
   if (num == 0) return 1;
   if (num == 1) return 2;
   if (num == 2) return 3;
   if (num == 3) return 4;
   if (num == 4) return 5;
   if (num == 5) return 6;
   if (num == 6) return 7;
   return 0;
}

void randomblock(ntet* pezzo, mtet* obj){
   srandom(time(0));
   int temp = random()%7;
   int t1 = pezzo->tet1; if (pezzo->tet1 == 0) t1 = 0;
   int t2 = pezzo->tet3; if (pezzo->tet3 == 0) t2 = 0;
   int t3 = pezzo->tet4; if (pezzo->tet4 == 0) t3 = 0;
   int t4 = pezzo->tet6; if (pezzo->tet6 == 0) t4 = 0;
   int t5 = pezzo->tet7;
   int t6 = pezzo->tet5;
   int t7 = pezzo->tet2;
   //   printf("%d", pezzo->tet1);
   if (randomnumber() == 1 && t1 >= 0){ copyblock(obj->tetr1, one); obj->color = 0; obj->shape = 0; --pezzo->tet1;
   }  
   else if (t3 >= 0 && randomnumber() == 2){ copyblock(obj->tetr1, two); obj->color = 1; obj->shape = 1; --pezzo->tet3;
   }
   else if (t4 >= 0 && randomnumber() == 3){ copyblock(obj->tetr1, three); obj->color = 2; obj->shape = 1; --pezzo->tet4;
   }
   else if (t6 >= 0 && randomnumber() == 4){ copyblock(obj->tetr1, four); obj->color = 3; obj->shape = 1; --pezzo->tet6;
   }
   else if (t7 >= 0 && randomnumber() == 5){ copyblock(obj->tetr1, five); obj->color = 4; obj->shape = 1; --pezzo->tet7;
   }
   else if (t5 >= 0 && randomnumber() == 6){ copyblock(obj->tetr1, six); obj->color = 5; obj->shape = 1; --pezzo->tet5;
   }
   else if (t2 >= 0 && randomnumber() == 7){ copyblock(obj->tetr1, seven); obj->color = 6; obj->shape = 1; --pezzo->tet2;
   }
}

void changetab(char Tab[x][y], char Tab2[x][y], mtet* obj, char tetr[4][4], int movx, int movy, int movx2, int movy2){
   if (obj->switchp == 0){
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            if (tetr[i][j] == '#'){
               Tab[movy + i][movx + j] = tetr[i][j];
            }
         }
      }
   } else if (obj->switchp == 1){
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            if (tetr[i][j] == '#'){
               Tab2[movy2 + i][movx2 + j] = tetr[i][j];
            }
         }
      }
   }
}

void choose(game* gm){
   title();
   sleep(1);
   printf("\n\n");
   int m;
   printf("\t\x1b[34m[1] Single Player\n\t[2] Multiplayer\n\n");
   printf("\tSelect your mod: \x1b[0m");
   scanf("%d", &m);
   if (m < 3 && m > 0){
      switch (m){
         case 1:
            sleep(1); printf("\n\t\x1b[32mSelected mod -> Single Player\x1b[0m \n\n\n");
            gm->gamemode = 1;
            break;
         case 2:
            sleep(1); printf("\n\t\x1b[32mSelected mod -> Multiplayer\x1b[0m \n\n\n");
            gm->gamemode = 2;
            break;
      }
   } else{
      sleep(1); printf("\t\x1b[31mmod n. %d doesn't exist\x1b[0m \n", m);
      sleep(1); system("clear");
   }
}

void tetrgui(ntet* pezzo, game* gm){ 
   if (gm->gamemode == 1){
      printf("\n\t\t\t\t\x1b[36m  %s %s %s %s  \x1b[0m[1] %d", bl, bl, bl, bl, pezzo->tet1);
      printf("\n\n\t\t\t\t    \x1b[35m%s\n\t\t\t\t  %s %s %s    \x1b[0m[2] %d", bl, bl, bl, bl, pezzo->tet2);
      printf("\n\n\t\t\t\t\x1b[31m  %s %s\n\t\t\t\t\x1b[31m    %s %s    \x1b[0m[3] %d", bl, bl, bl, bl, pezzo->tet3);
      printf("\n\n\t\t\t\t\x1b[32m    %s %s\n\t\t\t\t\x1b[32m  %s %s      \x1b[0m[4] %d", bl, bl, bl, bl, pezzo->tet4);
      printf("\n\n\t\t\t\t\x1b[34m    %s\n\t\t\t\t    %s      \x1b[0m[5] %d\n\t\t\t\t\x1b[34m    %s %s    \x1b[0m", bl, bl, pezzo->tet6, bl, bl);
      printf("\n\n\t\t\t\t\x1b[37m    %s\n\t\t\t\t    %s      \x1b[0m[6] %d\n\t\t\t\t\x1b[37m    %s %s    \x1b[0m", bl, bl, pezzo->tet5, bl, bl);
      printf("\n\n\t\t\t\t\x1b[33m    %s %s\n\t\t\t\t    %s %s    \x1b[0m[7] %d", bl, bl, bl, bl, pezzo->tet7);

   }
   if (gm->gamemode == 2){
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\x1b[36m  %s %s %s %s  \x1b[0m[1] %d", bl, bl, bl, bl, pezzo->tet1);
      printf("\n\n\t\t\t\t    \x1b[35m%s\n\t\t\t\t  %s %s %s    \x1b[0m[2] %d", bl, bl, bl, bl, pezzo->tet2);
      printf("\n\n\t\t\t\t\x1b[31m  %s %s\n\t\t\t\t\x1b[31m    %s %s    \x1b[0m[3] %d", bl, bl, bl, bl, pezzo->tet3);
      printf("\n\n\t\t\t\t\x1b[32m    %s %s\n\t\t\t\t\x1b[32m  %s %s      \x1b[0m[4] %d", bl, bl, bl, bl, pezzo->tet4);
      printf("\n\n\t\t\t\t\x1b[34m    %s\n\t\t\t\t    %s      \x1b[0m[5] %d\n\t\t\t\t\x1b[34m    %s %s    \x1b[0m", bl, bl, pezzo->tet6, bl, bl);
      printf("\n\n\t\t\t\t\x1b[37m    %s\n\t\t\t\t    %s      \x1b[0m[6] %d\n\t\t\t\t\x1b[37m    %s %s    \x1b[0m", bl, bl, pezzo->tet5, bl, bl);
      printf("\n\n\t\t\t\t\x1b[33m    %s %s\n\t\t\t\t    %s %s    \x1b[0m[7] %d", bl, bl, bl, bl, pezzo->tet7);
   }
}

void tab(char Tab[x][y], mtet* obj){
   for (int i = 0 ; i < x ; i++ ){
      for (int j = 0 ; j < y ; j++ ){
         PrintCharTab(Tab[i][j], obj);
      }
      printf("\n");
   }
}

int p;

int removelines(char* Tab){
   int count = 0;
   for (int i = 0 ; i < x ; i++){
      count = 0;
      for (int j = 0 ; j < y ; j++){
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

void dupanother(char* Tab, game* gm){
   if (removelines(Tab) == 1){
         l++;
      if (l == 2){
         gm->score += 1;
      }
      if (l == 3){
         gm->score += 1;
      }
   } else l = 0;
}

void dupanotherp2(char* Tab, game* gm){
   if (removelines(Tab) == 1){
         l++;
      if (l == 2){
         gm->score2p += 1;
      }
      if (l == 3){
         gm->score2p += 1;
      }
   } else l = 0;
}

void restoreproblem(char Tab[x][y]){
   for (int i = 4 ; i < x-1 ; i++){
      Tab[i][y-1] = '2';
      Tab[i][0] = '1';
   }   
}

void checkscorep1(char Tab[x][y], mtet* obj, game* gm){
   if (removelines(*Tab) == 1){
      gm->score += 1;
      dupanother(*Tab, gm);
      for (int i = p-1 ; i >= 0 ; i--){
         for (int j = y-1 ; j >= 1 ; j--){
            Tab[i+1][j] = Tab[i][j]; 
         }
      }
   }
   restoreproblem(Tab);
}

void checkscorep2(char Tab[x][y], mtet* obj, game* gm){
   if (removelines(*Tab) == 1){
      gm->score2p += 1;
      dupanotherp2(*Tab, gm);
      for (int i = p-1 ; i >= 0 ; i--){
         for (int j = y-1 ; j >= 1 ; j--){
            Tab[i+1][j] = Tab[i][j];
         }
      }
   }
   restoreproblem(Tab);
}

int stoptetr(char Tab[x][y], mtet* obj){
   for (int i = 0; i < x; i++){
      for (int j = 0; j < y; j++){
         if (Tab[i][j] == '#'){
            obj->dist = 0;
            if (i == 18){   //check for ground collisions
               for (int k = i - 3; k <= i + 1; k++){
                  for (int f = j - 2; f <= j + 4; f++){
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
            if (Tab[i+1][j] == 'k' || Tab[i+1][j] == 'z' || Tab[i+1][j] == 'v' || Tab[i+1][j] == 'l' || Tab[i+1][j] == 'c' || Tab[i+1][j] == 'h' || Tab[i+1][j] == 'o'){    //check for lower collisions
               for (int k = i - 3 ; k <= i + 2; k++){
                  for (int f = j - 2 ; f <= j + 5; f++){
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
         } 
      }
   }
   return 0;
}

void win(ntet* pezzo, game* gm){
   if (pezzo->tet1+pezzo->tet2+pezzo->tet3+pezzo->tet4+pezzo->tet5+pezzo->tet6+pezzo->tet7 == 0){
      system("clear");
      printf("YOU WIN!");
      scorecheck(gm->score);
      gm->gameover = 1;
   }
}

void returngameover(char Tab[x][y], mtet* obj, game* gm){
   gotoxy(0,2);
   for (int i = 0 ; i < 3 ; i++){
      for (int j = 0 ; j < y ; j++){
         if (Tab[i][j] == 'k' || Tab[i][j] == 'o'|| Tab[i][j] == 'h'|| Tab[i][j] == 'l'|| Tab[i][j] == 'z'|| Tab[i][j] == 'v'|| Tab[i][j] == 'c'){
            char s[4][6] = {{' ',' ',' ',' ',' ',' '},{' ','G','A','M','E',' '}, {' ','O','V','E','R',' '},{' ',' ',' ',' ',' ',' '}};
            for (int k = 0 ; k < 4 ; k++){
               for (int f = 0 ; f < 6 ; f++){
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
int gameoverreturn(char Tab[x][y], game* gm){
   for (int i = 0 ; i < 3 ; i++){
      for (int j = 0 ; j < y ; j++){
         if (Tab[i][j] == 'k' || Tab[i][j] == 'o'|| Tab[i][j] == 'h'|| Tab[i][j] == 'l'|| Tab[i][j] == 'z'|| Tab[i][j] == 'v'|| Tab[i][j] == 'c'){
            return 1;
         }
      }
   }
   return 0;
}

void mod2gameover(char Tab[x][y], char Tab2[x][y], mtet* obj, game* gm){
   gotoxy(0,2);
   if (gameoverreturn(Tab, gm) == 1){
      if (gm->score > gm->score2p){
         sleep(2);
         system("clear");
         printf("P1");
         exit(0);
      } else if (gm->score < gm->score2p){
         sleep(2);
         system("clear");
         printf("P2");
         exit(0);
      } else if (gm->score == gm->score2p){
         sleep(2);
         system("clear");
         printf("Nessun vincitore");
         exit(0);
      }
   }
   if (gameoverreturn(Tab2, gm) == 1){
      if (gm->score > gm->score2p){
         sleep(2);
         system("clear");
         printf("P1");
         exit(0);
      } else if (gm->score < gm->score2p){
         sleep(2);
         system("clear");
         printf("P2");
         exit(0);
      } else if (gm->score == gm->score2p){
         sleep(2);
         system("clear");
         printf("Nessun vincitore");
         exit(0);
      }
   }
}

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

void initntet(ntet* pezzo){
   pezzo->tet1 = 2;
   pezzo->tet1 = 2;
   pezzo->tet2 = 2;
   pezzo->tet3 = 2;
   pezzo->tet4 = 2;
   pezzo->tet5 = 2;
   pezzo->tet6 = 2;
   pezzo->tet7 = 2;
}

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

void initgame(game* gm){
   gm->gameover = 0;
   gm->score = 0;
   gm->score2p = 0;
   gm->gamemode = 0;
}
