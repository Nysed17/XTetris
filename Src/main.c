#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mod.c" /*mod 1P*/

int main(){    
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

   ntet pezzo;
   mtet obj;
   game gm;
   initntet(&pezzo);
   initmtet(&obj);
   initgame(&gm);

   choose(&gm);
   randomblock(&pezzo, &obj);
   if (gm.gameover == 0){
      if (gm.gamemode == 1){
         sleep(1);
         system("clear");
         instructions();
         sleep(3);
         system("stty -icanon");
         system("stty -echo");
         system("tput civis");
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
