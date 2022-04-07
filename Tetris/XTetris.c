#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string.h> 
#include <stdlib.h>
#include <termios.h>
//other files:
#include "Title.c"
#include "Mod.c"
//
#define x  12
#define y  17

//main code

int posx = 12;
int posy = 17;
int score = 0;

void gotoxy(int posx, int posy){
    printf("%c[%d;%df",0x1B,y,x);
}

void scorecheck(){
	printf("Score: %d", score);
}

void print_tet(){
    
}

void print_c(char c) { // se guardi nel main alla fine c'e scritto Tab[][]=c ed il 'c' che torna qua è semplicemente un #
	switch (c) {                
		case '#': //questo è quando c'è il #
			printf("\u2501");
			break;
		case '1': //questo quando c'è un 1? bo
			printf("\u2503");
			break;
		case '2':
			printf("\u250F");
			break;
		case '3':
			printf("\u2513");
			break;
		case '4':
			printf("\u2517");
			break;
		case '5':
			printf("\u251B");
			break;
		default:
			printf("%c%c", c, c);
	}
}

void tabella(char Tab[y][x]){
    int i, j;
for ( i = 0 ; i < y ; i++ ){
		for ( j = 0 ; j < x ; j++ ){
			if ( i == 0 || i == y - 1 || j == 0 || j == x - 1 ){
				print_c(Tab[i][j]);
			} else
				printf(" ");
		}
		printf("\n");
    }

} 

int main(){
    int gameover = 0;
    char Tab[y][x] = {{'2','#','#','#','#','#','#','#','#','#','#','3'},
										  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
								 		  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
								 		  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
								 		  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
								 		  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
										  {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1'},
											{'4','#','#','#','#','#','#','#','#','#','#','5'}};   
		system("clear");title();
		sleep(1);
	  if (mod() == 1){
			sleep(1);
			while (!gameover) {
				system("clear");				 
				tabella(Tab);
			}
		} else {
			printf("\n\n\tMod not valid!");
			mod();
		}

    return 0;
}
