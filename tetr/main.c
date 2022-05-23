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
    
int onet = 4; //size of one
char two[4][4] = {{'#','#','n','n'},{'n','#','#','n'},{'n','n','n','n'},{'n','n','n','n'}}; //##
                                                                                            // ##
int alltet = 3; //size of other tetr
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

char tetr1[4][4]; //printed tetr
int gameover = 0; 
int movx = 4; //x 1st block of tetr
int movy = 0; //y 1st block of tetr
int score = 0; //score of P1
int shape = 0; //size of tetr
int g = 0; //rotation checker
int checkblock = 0;
int color = 0;

void gotoxy(int posx, int posy){  
    printf("%c[%d;%df",0x1B,posy,posx);
}

void scorecheck(){
    printf("Score: %d", score);
}

int stoptetr(char Tab[x][y]);

void otherblockcollision(char Tab[x][y]){ 
    for (int i = 0 ; i < x ; i++)
        for (int j = 0 ; j < y ; j++)
            if (Tab[i][j] == '#'){
                for (int k = 0; k < 4; k++){
                    for (int f = 0; f < 4; f++){
                        if (Tab[i+k][j+f] == '#'){
                            if (Tab[i+k][j+f+1] == '2' || Tab[i+k][j+f+1] == 'k' || Tab[i+k][j+f+1] == 'z' || Tab[i+k][j+f+1] == 'v' || Tab[i+k][j+f+1] == 'l' || Tab[i+k][j+f+1] == 'c' || Tab[i+k][j+f+1] == 'h' || Tab[i+k][j+f+1] == 'o' || Tab[i+k][j+f+1] == 'm'){
                                checkblock = 1;
                                return;
                            } else if (Tab[i+k][j+f-1] == '1' ||  Tab[i+k][j+f-1] == 'k' || Tab[i+k][j+f-1] == 'z' || Tab[i+k][j+f-1] == 'v' || Tab[i+k][j+f-1] == 'l' || Tab[i+k][j+f-1] == 'c' || Tab[i+k][j+f-1] == 'h' || Tab[i+k][j+f-1] == 'o' || Tab[i+k][j+f-1] == 'm'){
                                checkblock = 2;
                                return;
                            }
                        }    
                    }
                }
            }
    checkblock = 0;
}

void move(char Tab[x][y]){
    switch(getchar()){
        case 'a':
        if (checkblock != 2){
            movx--;
        }
        break;
        case 's':
            movy++;
        break;
        case 'd':
        if (checkblock != 1){
            movx++;
        }
        break;
        case 'x':
            gameover = 1;
        break;
        case 'r':
        if (checkblock == 0){
            g = 1;
        }
        break;
        case ' ':


        while (Tab[movy+2][movx] != 'k'){
            movy++;
        }


        break;
    }
}

void colors(){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (shape == 0) {color = 1; return;}
            else if (tetr1[i][j] == two[i][j]) {color = 2; return;}
            else if (tetr1[i][j] == three[i][j]) {color = 3; return;}
            else if (tetr1[i][j] == four[i][j]) {color = 4; return;}
            else if (tetr1[i][j] == five[i][j]) {color = 5; return;}
            else if (tetr1[i][j] == six[i][j]) {color = 6; return;} 
            else if (tetr1[i][j] == seven[i][j]) {color = 7; return;}
        }
    }
    color = 0;
}

void PrintCharTab(char c, char tab[x][y]){
    switch (c) {                
        case 'x': //floor
            printf("━━");
            break;
        case '1': //left wall
            printf("┃ ");
            break;
        case '2': //right wall
            printf("┃");
            break;
        case '3': //left corner
            printf("┗━");
            break;
        case '4': //right corner
            printf("┛");
            break;
        case 'n': //null
            printf("  ");
            break;
        case 'm': //topnull
            printf("  ");
            break;
        case '#': //tetramino
            if (color == 0) {printf("\x1b[36m%s \x1b[0m", bl);}
            if (color == 1) {printf("\x1b[31m%s \x1b[0m", bl);}
            if (color == 2) {printf("\x1b[32m%s \x1b[0m", bl);}
            if (color == 3) {printf("\x1b[34m%s \x1b[0m", bl);}
            if (color == 4) {printf("\x1b[33m%s \x1b[0m", bl);}
            if (color == 5) {printf("\x1b[37m%s \x1b[0m", bl);}
            if (color == 6) {printf("\x1b[35m%s \x1b[0m", bl);}
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
            printf("%c ", c);
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

void rotate_process(char tab[x][y], char tetr[4][4], int size){
    char flag[4][4];
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            flag[size-j-1][i] = tetr[i][j];
        }
    }
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            tetr[i][j] = flag[i][j];
        }
    }
}

void cleartab(char Tab[x][y]){
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (Tab[i+movy][j+movx] == '#'){
                Tab[i+movy][j+movx] = 'n';
            }
        }
    } 
}

void randomblock(){
    srandom(time(0));
    int temp = random()%7;
    if (temp == 0){ copyblock(tetr1, one); color = 0; shape = 0;
    } else if (temp == 1){ copyblock(tetr1, two); color = 1; shape = 1;
    } else if (temp == 2){ copyblock(tetr1, three); color = 2; shape = 1;
    } else if (temp == 3){ copyblock(tetr1, four); color = 3; shape = 1;
    } else if (temp == 4){ copyblock(tetr1, five); color = 4; shape = 1;
    } else if (temp == 5){ copyblock(tetr1, six); color = 5; shape = 1;
    } else if (temp == 6){ copyblock(tetr1, seven); color = 6; shape = 1;
    }
}

void changetab(char Tab[x][y]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (tetr1[i][j] == '#'){
                Tab[movy + i][movx + j] = tetr1[i][j];
            }
        }
    }
}

void tab(char Tab[x][y]){
    for (int i = 0 ; i < x ; i++ ){
        for (int j = 0 ; j < y ; j++ ){
           // printf("%c", Tab[i][j]);
            PrintCharTab(Tab[i][j], Tab);
        }
    printf("\n");
    }
}

void godown(char* Tab, int ics, int ips){
    for (int i = 1 ; i < x-1 ; i++){
        for (int j = 1 ; j < y-1 ; j++){
            if (Tab[i+j] == 'k'){
                Tab[i+j] = Tab[i+j-y]; 
            }    
        }
    }
}

int checklines(char* Tab){
    int count = 0;
    for (int i = 0 ; i < x ; i++){
        for (int j = 0 ; j < y ; j++){
            if (Tab[i*y+j] == 'k' || Tab[i*y+j] == 'z'|| Tab[i*y+j] == 'o'|| Tab[i*y+j] == 'v'|| Tab[i*y+j] == 'c'|| Tab[i*y+j] == 'l'|| Tab[i*y+j] == 'h'){
                count++; 
                if (count == y-2){
                    int f = i;
                    int k;
                    for (k = 1 ; k < y-1 ; k++)
                    Tab[f*y+k] = 'n'; godown(Tab,f,k); return 1;
                }
                if (count > y) count = 0;
            } else if (Tab[i*y+j] == 'n' || Tab[i*y+j] == '#'){
                count = 0;
            }
        }
    }
    return 0;
}

void removelines(char Tab[x][y]){
    if (checklines(*Tab) == 1){
        score += 100;
    }
}

int stoptetr(char Tab[x][y]){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            if (Tab[i][j] == '#'){
                if (i == 18){   //check for ground collisions
                    for (int k = i - 3; k <= i + 1; k++){
                        for (int f = j - 2; f <= j + 4; f++){
                            if (Tab[k][f] == '#'){
                                if (color == 0) Tab[k][f] = 'k';
                                if (color == 1) Tab[k][f] = 'l';
                                if (color == 2) Tab[k][f] = 'h';
                                if (color == 3) Tab[k][f] = 'o';
                                if (color == 4) Tab[k][f] = 'v';
                                if (color == 5) Tab[k][f] = 'c';
                                if (color == 6) Tab[k][f] = 'z';
                            }
                        }
                    }
                    return 1;
                }
                if (Tab[i+1][j] == 'k' || Tab[i+1][j] == 'z' || Tab[i+1][j] == 'v' || Tab[i+1][j] == 'l' || Tab[i+1][j] == 'c' || Tab[i+1][j] == 'h' || Tab[i+1][j] == 'o'){    //check for lower collisions
                    for (int k = i - 3; k <= i + 2; k++){
                        for (int f = j - 2; f <= j + 5; f++){
                            if (Tab[k][f] == '#'){
                                if (color == 0) Tab[k][f] = 'k';
                                if (color == 1) Tab[k][f] = 'l';
                                if (color == 2) Tab[k][f] = 'h';
                                if (color == 3) Tab[k][f] = 'o';
                                if (color == 4) Tab[k][f] = 'v';
                                if (color == 5) Tab[k][f] = 'c';
                                if (color == 6) Tab[k][f] = 'z';
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

void returngameover(char Tab[x][y]){
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
                printf("\n\n");
                tab(Tab);
                gotoxy(5,23);
                printf("Your score: %d", score);
                gotoxy(22,25);
                sleep(2);
                exit(0);
            }
        }
    }
}

void timep(){
    sleep(1);
    movy++;
}

void mod1(char Tab[x][y]){
    printf("\n\n");
    changetab(Tab);
    tab(Tab);
    otherblockcollision(Tab);
    if (stoptetr(Tab) == 1){
        randomblock();
        movx = 4;
        movy = 0;
    }
    cleartab(Tab);
//    gravity(Tab);
    removelines(Tab);
    returngameover(Tab); 
    gotoxy(9,23);
    printf("score: %d", score);
} 

int choose(){
    title();
    sleep(1);
    printf("\n\n");
    int m;
    printf("\t\x1b[34m[1] Giocatore singolo.\n\t[2] Giocatore vs Giocatore.\n\n");
    printf("\tSelezionare la modalità di gioco: \x1b[0m");
    scanf("%d", &m);
    if (m < 3 && m > 0){
        switch (m){
        case 1:
            sleep(1); printf("\n\t\x1b[32mmodalità selezionata -> Giocatore singolo.\x1b[0m \n\n\n");
            return 1;
            break;
        case 2:
            sleep(1); printf("\n\t\x1b[32mmodalità selezionata -> Giocatore vs Giocatore.\x1b[0m \n\n\n");
            return 2;
            break;
        }
    } else{
		  sleep(1); printf("\t\x1b[31mla modalità n. %d non esiste\x1b[0m \n", m);
		  sleep(1); system("clear");
    }
    return 0;
} 

int main(){

    randomblock();
    char Tab[x][y] = {{'m','n','n','n','n','n','n','n','n','n','n','m'},
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
    system("clear");
    if (gameover == 0){
        if (choose() == 1){
            sleep(1);
            system("clear");
            instructions();
            sleep(3);
            system("stty -icanon");
            system("stty -echo");
            system("tput civis");
            while (gameover == 0) {
                system("clear");                 
                gotoxy(0,0);
                if (g == 1){
                    if (shape == 0){
                        rotate_process(Tab, tetr1, onet);
                        g = 0;
                    }
                    if (shape == 1){
                        rotate_process(Tab, tetr1, alltet);
                        g = 0;
                    }
                }
                mod1(Tab);
                move(Tab);
            } system("tput cnorm");
        } else if (choose() == 2){

         }
    } else {
        exit(0);
    }
    return 0;
}
