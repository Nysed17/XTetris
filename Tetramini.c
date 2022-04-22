#include <stdio.h>
#include <stdlib.h>

typedef struct tetramini{
    int data[9];
}tet;

void print_tet(tet ttr){
    for (int i = 0 ; i < 9 ; i++){
       if (ttr.data[i] != 0){
            printf("#");
        } 
        if (i == 2 || i == 5){
            printf("\n");
        } 
 
    }
}

int main(){

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
    print_tet(two);
    return 0;
}
