#include <stdio.h>
#include <stdlib.h>

void printtab(int m[5][5]){
  for (int i = 0 ; i < 5 ; i++){
    for (int j = 0 ; j < 5 ; j++){
      printf("%d", m[i][j]);
    }
    printf("\n");
  }
}

void can(int* m){
  int count = 0;
  for (int i = 0 ; i < 5 ; i++)
    for (int j = 0 ; j < 5 ; j++)
      if (m[i*5+j] == 1){
          count++;
          if (count == 5){
            int g = i;
            for (int h = 0 ; h < 5 ; h++)
            m[g*5+h] = 2;
          }
      }
}

int main(){

  int m[5][5] = {{0,0,0,0,0},
                 {0,0,0,0,0},
                 {1,0,0,0,0},
                 {0,0,0,0,0},
                 {1,1,1,1,1}};
  
  while (1){
    system("clear");
    printtab(m);
    can(&m[0][0]);
  }

  return 0;
}
