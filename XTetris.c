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

#include <stdio.h>
#include <stdlib.h>

typedef struct tetramini{
  int data[9];
}tet;


int one[16] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1}; //####
    
  tet two = {0,0,0,0,1,1,0,1,1}; //##
                                 //##

  tet three = {1,0,0,1,0,0,1,1,0}; //#
                                   //#
                                   //##
    
  tet four = {0,0,1,0,0,1,0,1,1}; // #
                                  // #
                                  //##

  tet five = {0,0,0,1,1,0,0,1,1}; //##
                                  // ##

  tet six = {0,0,0,0,1,1,1,1,0}; // ##
                                 //##   

  tet seven = {0,0,0,0,1,0,1,1,1}; // #
                                   //###
int posx = 12;
int posy = 17;
int movx = 5;
int movy = 5;
int score = 0;

void gotoxy(int posx, int posy){  
	printf("%c[%d;%df",0x1B,posy,posx);
}

void scorecheck(){
	printf("Score: %d", score);
}

void move(int gameover){
		switch(getchar()){
			case 'a':
				movx--;
				break;
			case 's':
				movy++;
				break;
			case 'd':
				movx++;
				break;
		}
}

void TetColour(int p){
	switch(p){
		case '1':
			printf("\x1b[33m#"); //yellow
		break;
		case '2':
			printf("\x1b[#"); //orange
		break;
		case '3':
			printf("\x1b[34m#"); //blue
		break;
		case '4':
			printf("\x1b[31m#"); //red
		break;
		case '5':
			printf("\x1b[32m#"); //green
		break;
		case '6':
			printf("\x1b[35m#"); //purple
		break;
		case '7':
			printf("\x1b[36m#"); //cyan
		break;
	}
}

void print_tet(tet ttr){
	int p = 3;
	for (int i = 0 ; i < 9 ; i++){
		if (ttr.data[i] == 1){
			TetColour(p);
    }
		if (i == 2 || i == 5){
			printf("\n");
    } 
  }
}

void showtet(){
	print_tet(two);
	print_tet(three);
}

void PrintCharTab(char c) { //se guardi nel main alla fine c'e scritto Tab[][]=c ed il 'c' che torna qua è semplicemente un #
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

void tab(char Tab[y][x]){
	int i, j;
	for ( i = 0 ; i < y ; i++ ){
		for ( j = 0 ; j < x ; j++ ){
			if ( i == 0 || i == y - 1 || j == 0 || j == x - 1 ){
				PrintCharTab(Tab[i][j]);
			} else
				printf(" ");
		}
		printf("\n");
  }
}

void mod1(char Tab[y][x]){
  
	title();
	printf("\n\n");
	tab(Tab);
	gotoxy(18,16);
	showtet();
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
			system("stty -icanon");
			system("stty -echo");
			while (!gameover) {
				gotoxy(18,26);
				printf("score: %d", score);
					system("clear");				 
					gotoxy(0,0);
					mod1(Tab);
					move(gameover);	
			}
		} else {
			main();
		}

    return 0;
}
