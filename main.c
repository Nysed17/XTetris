#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mod.c" //mod 1P

/*int choose(){
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
  return 1;
  break;
  case 2:
  sleep(1); printf("\n\t\x1b[32mSelected mod -> Multiplayer\x1b[0m \n\n\n");
  return 2;
  break;
  }
  } else{
  sleep(1); printf("\t\x1b[31mmod n. %d doesn't exist\x1b[0m \n", m);
  sleep(1); system("clear");
  }
  return 0;
  }
  */
int main(){    
   ntet pezzo;
   initntet(&pezzo);
   mtet obj;
   initmtet(&obj);
   game gm;
   initgame(&gm);
   char Tab[x][y] =  {{'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'3','x','x','x','x','x','x','x','x','x','x','4'}};

   char Tab2[x][y] = {{'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'m','n','n','n','n','n','n','n','n','n','n','m'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'1','n','n','n','n','n','n','n','n','n','n','2'},
      {'3','x','x','x','x','x','x','x','x','x','x','4'}};

   choose(&gm);

   if (gm.gameover == 0){
      if (gm.gamemode == 1){
         //if (cho == 1){
         sleep(1);
         system("clear");
         instructions();
         sleep(3);
         system("stty -icanon");
         system("stty -echo");
         system("tput civis");
         randomblock(&pezzo, &obj);
         while (gm.gameover == 0) {
            system("clear");                 
            gotoxy(0,0);
            if (obj.g == 1){
               if (obj.shape == 0){
                  rotate_process(Tab, &obj, obj.onet);
                  obj.g = 0;
               }
               if (obj.shape == 1){
                  rotate_process(Tab, &obj, obj.alltet);
                  obj.g = 0;
               }
            }
            mod1(Tab, Tab2, &pezzo, &obj, &gm);
            movep1(Tab, &obj, &gm);
         } system("tput cnorm");
      } else if (gm.gamemode == 2){
         sleep(1);
         system("clear");
         instructions();
         sleep(3);
         system("stty -icanon");
         system("stty -echo");
         system("tput civis");
         sdoppiapezzi(&gm, &pezzo);
         randomblock(&pezzo, &obj);
         while (gm.gameover == 0){
            system("clear");
            if (obj.g == 1){
               if (obj.shape == 0){
                  rotate_process(Tab2, &obj, obj.onet);
                  obj.g = 0;
               }
               if (obj.shape == 1){
                  rotate_process(Tab2, &obj, obj.alltet);
                  obj.g = 0;
               }
            }
            // mod1(Tab, &pezzo, &obj, &gm);
            mod2(Tab, Tab2, &pezzo, &obj, &gm);
            if (obj.switchp == 0){
               movep1(Tab, &obj, &gm);
            } if (obj.switchp == 1){
               movep2(Tab2, &obj, &gm);
            }
         } system("tput civis");
      }
   } else {
      exit(0);
   }
   return 0;
}
