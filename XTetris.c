#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string.h> 
#include <stdlib.h>
#include <termios.h>
#define x  12
#define y  17

int posx = 12;
int posy = 17;

void gotoxy(int posx, int posy){
    printf("%c[%d;%df",0x1B,y,x);
}

void print_tet(){
    
}

void print_c(char c) { // se guardi nel main alla fine c'e scritto Tab[][]=c ed il 'c' che torna qua è semplicemente un #
	switch (c) {                
		case '#': //questo è quando c'è il #
			printf("##");
			break;
		case '1': //questo quando c'è un 1? bo
			printf("\x1b[32m##\x1b[0m");
			break;
		case '2':
			printf("\x1b[33m##\x1b[0m");
			break;
		default:
			printf("%c%c", c, c);
	}
}

void tabella(char Tab[y][x]){
    int i, j;

	for (i = 0; i < y; i++){
		for(j = 0; j < x; j++){
			print_c( Tab[i][j]);
		}
		printf("\n");
	}
} 

int main(){
    int gameover = 0;
    char Tab[y][x] = {{'#','#','#','#','#','#','#','#','#','#','#','#'},
										  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 		  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 		  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 		  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
								 		  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
										  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
											{'#','#','#','#','#','#','#','#','#','#','#','#'}};   
    while (!gameover) {
        int a, b, c;
        system("clear");
        tabella(Tab);
    }   
    return 0;
}
