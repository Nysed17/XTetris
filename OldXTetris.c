#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string.h> 
#include <stdlib.h>
#include <termios.h>
#define ANSI_RESET_ALL          "\x1b[0m"
#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"
#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"
#define ANSI_STYLE_BOLD         "\x1b[1m"
#define ANSI_STYLE_ITALIC       "\x1b[3m"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m"
#define clear "\e[1;1H\e[2J"
#define tabx 12
#define taby 17

int gameover = 0;
int x = 11, y = 5;
int i, j;

void waitFor (unsigned int sec){
  	unsigned int retTime = time(0) + sec;
    while (time(0) < retTime);
}

void gotoxy(int x, int y){
    printf("%c[%d;%df",0x1B,y,x);
}

void clr(){
    system("clear");
}

void titolo(){
	printf("\t\x1b[35m __   __  _______  _______  _______  ______    ___   _______ "
         "\n\t\x1b[35m|  |_|  ||       ||       ||       ||    _ |  |   | |       |"
         "\n\t\x1b[35m|       ||_     _||    ___||_     _||   | ||  |   | |  _____|"
         "\n\t\x1b[36m|       |  |   |  |   |___   |   |  |   |_||_ |   | | |_____ "
         "\n\t\x1b[36m |     |   |   |  |    ___|  |   |  |    __  ||   | |_____  |"
         "\n\t\x1b[34m|   _   |  |   |  |   |___   |   |  |   |  | ||   |  _____| |"
         "\n\t\x1b[34m|__| |__|  |___|  |_______|  |___|  |___|  |_||___| |_______|"
         "\n\n\x1b[0m ");
}

void sottotitolo(){
    waitFor(1); printf("\x1b[34m\t\t\tCreato da Curzio e Tullio.\n\n\n\n");
}

void movimento_sexy(){
    switch (getchar()){
        case 'w':
            x--;
            break;
        case 'a':
            y--;
            break;
        case 's':
            x++;
            break;
        case 'd':
            y++;
            break;
        case 'x':
            gameover = 1;
            break;
    }
}

/*void pezz_diocane(char *tulzio, int w, int h, int x, int y) {
    for (int j = 0; j < w; j++) {
        for (int i = 0 ; i < h ; i++) {
            gotoxy(y + i, x + j);
            if (tulzio[j * w + i] != ' ') {
                printf("\x1b[31m%c\x1b[0m", tulzio[j * w + i]);
            }
        }
    }
} )
*/
/*
siwtch (
    case 1 : tulzio = tulzio1;
    case 2 : tulzio = tulzio2;
    case 3 : tulzio = tulzio3;
)

pezz_diocane(tulzio, 2, 3, x, y);
*/

void pezz1(int still, int* p){
    char tulzio[1][4]={'#', '#', '#', '#'};

    for(j = 0; j < 1; j++){
        for ( i = 0 ; i < 4 ; i++){
            if (!still) gotoxy(y + i, x + j);
            else gotoxy(20 + i, 10 + j);
            if (tulzio[j][i] != ' ' && y < 9 && x < 27)
                printf("\x1b[31m%c\x1b[0m", tulzio[j][i]);
					 else if (y > 8 && *p == 1){
					 	y = 8;
					 } else if (x > 26 && *p == 1){
					 	x = 26;
					 }
        }
    }
}

void pezz2(int still){
    char tulzio1[2][3]={{' ','#',' '},
                        {'#','#','#'}};

    for (j = 0 ; j < 2 ; j++){
        for (i = 0 ; i < 3 ; i++){
            if (!still) gotoxy(y + i, x + j);
            else gotoxy(20 + i, 12 + j);
            if (tulzio1[j][i] != ' ')
                printf("\x1b[35m%c\x1b[0m", tulzio1[j][i]);
        }
    }
}

void pezz3(int still, int* p){
    char tulzio2[2][3]={{'#','#',' '},
                        {'#','#',' '}};
    for (i = 0 ; i < 2 ;i++){
        for (j = 0 ; j < 3 ; j++){
            if (!still) gotoxy(y + j, x + i);
            else gotoxy(20 + j, 15 + i);
         	if (tulzio2[i][j] != ' ')
					printf("\x1b[32m%c\x1b[0m", tulzio2[i][j]);
        }
    }
}

// #
// ###

//   #
// ###

//  ## 
// ##

// ##
//  ##

void pezz4(int still){
    char tulzio3[2][3]={{'#',' ',' '},
                        {'#','#','#'}};
    for (i = 0 ; i < 3 ; i++){
        for (j = 0 ; j < 2 ; j++){
            if (!still) gotoxy(y + i, x + j);
            else gotoxy(20 + i, 18 + j);
            if (tulzio3[j][i] != ' ' && y < 10 && x > 10 && y > 1 && x < 26)
                printf("\x1b[34m%c\x1b[0m", tulzio3[j][i]);
					 else if (y > 9){
					 	y = 9;
					 } else if (x < 11){
					 	x = 11;
					 } else if (x > 24){
					 	x = 24;
					 } else if (y < 2){
					 	y = 2;
					 }
        }
    }
}

void pezz5(int still){
	char tulzio4[2][3]={{' ',' ','#'},
							  {'#','#','#'}};
	for (i = 0 ; i < 3 ; i++){
		for (j = 0 ; j < 2 ; j++){
			if (!still) gotoxy(y + i, x + j);
			else gotoxy(20 + i, 21 + j);
			if (tulzio4[j][i] != ' ')
				printf("\x1b[38m%c\x1b[0m", tulzio4[j][i]);	
		}	
	}
}

void pezz6(int still){
	char tulzio5[2][3]={{'#','#',' '},
							  {' ','#','#'}};
	for (i = 0 ; i < 3 ; i++){
		for (j = 0 ; j < 2 ; j++){
			if (!still) gotoxy(y + i, x + j);
			else gotoxy(20 + i, 24 + j);
			if (tulzio5[j][i] != ' ')
				printf("\x1b[31m%c\x1b[0m", tulzio5[j][i]);
		}
	}
}

void qualepezzo(int *p){
    // for (i = 0; i < n_tetramini; i++) { pezz_diocane(tertramino[i]); }
    pezz1(1, p);
    pezz2(1);
    pezz3(1, p);
    pezz4(1);
	 pezz5(1);
	 pezz6(1);
}

void tab1P(int p){
    system("stty -echo");
    system("stty -icanon"); 


    clr();
    
    titolo();

    printf("\n");

    qualepezzo(&p);

    printf("\n");

    gotoxy(0, 10);
	for ( i = 0 ; i < taby ; i++ ){
		for ( j = 0 ; j < tabx ; j++ ){
			if ( i == 0 || i == taby - 1 || j == 0 || j == tabx - 1 ){
				printf("\x1b[33m#\x1b[0m");
			} else
				printf(" ");
		}
		printf("\n");
    }
        printf("Quale pezzo vuoi scegliere?");

        printf("\nPremere 'x' per uscire\n");

        // pezz_diocane(tetrimanio[p]);
        if (p == 1){
            pezz1(0, &p);
        }
        else if (p == 2){
            pezz2(0);
        }
        else if (p == 3){
            pezz3(0, &p);
        }
        else if (p == 4){
            pezz4(0);
        }
		  else if (p == 5){
				pezz5(0);
		  }
		  else if (p == 6){
				pezz6(0);
		  }
        /*gotoxy(y, x);
        pezz2(); // il problema è il newline alla definizione di pezz2;
        */
}

void tab2P(){

	clr();

	gotoxy(0, 0);
	for ( i = 0 ; i < taby ; i++ ){
		for ( j = 0 ; j < tabx ; j++ ){
			if ( i == 0 || i == taby - 1 || j == 0 || j == tabx - 1 ){
				printf("#");
			} else
				printf(" ");
		}
		printf("\n");
	} 
	
	gotoxy(y, x);
		

    gotoxy(0, 0);
	for ( i = 0 ; i < taby ; i++ ){
		for ( j = 0 ; j < tabx ; j++ ){
			if ( i == 0 || i == taby - 1 || j == 0 || j == tabx - 1 ){
				printf("#");
			} else
				printf(" ");
		}
		printf("\n");
	} 
	
	gotoxy(y, x);
	printf("O");
}

int modalita(){
    
    int m;
    printf("\x1b[34m1) Giocatore singolo.\n2) Giocatore vs Giocatore.\n\n");
    printf("Selezionare la modalità di gioco: \x1b[0m");
    
    scanf("%d", &m);

    if (m < 3 && m >0){
        switch (m){
        case 1:
            waitFor(1); printf("\n\x1b[32mmodalità selezionata -> Giocatore singolo.\x1b[0m \n\n\n");
            return 1;
            break;
        case 2:
            waitFor(1); printf("\n\x1b[32mmodalità selezionata -> Giocatore vs Giocatore.\x1b[0m \n\n\n");
            return 2;
            break;
        }
    } else{
		  waitFor(1); printf("\x1b[31mla modalità n. %d non esiste\x1b[0m \n", m);
		  waitFor(1); system("clear");
		  return titolo(), sottotitolo(), modalita();
    }
    return 0;

}

int main(){
    system("clear");

	 int oldp;
    int i;
    char curzio[x][y]; //la variabile si chiama curzio perchè chi l'ha inventata aveva un berretto verde e la pelle rossa
    waitFor(1);	
    titolo();
	sottotitolo();
	
    if (modalita() == 1){     
        waitFor(1);
        while(gameover == 0){
            int p;
            tab1P(p);
            scanf("%d", &p);
            movimento_sexy();
            if (oldp != p) {
                x = 11;
                y = 5;
            }
            oldp = p;
            //waitFor(1);
            printf(clear);
        }
        while(gameover == 1){
            for ( i = 0 ; i < 17 ; i++ ){
                printf("GAME - OVER\n");
            }
            system("stty sane");
            exit(1);
        }
    } else {
        while(gameover == 0){
            tab2P();
            waitFor(1);
            printf(clear);
        }
    }	 
    return 0;
}

// Variabile con scanf per chiedere quale pezzo si desidera inserire, poi il dove e una volta scelto il pezzo e la posizione, la funzione andrà a inserire i caratteri dentro il nuovo array per poi ricaricare la pagina e rigenerare la tabella nuova nella stessa posizione con i colori diversi.
