#include <stdio.h>
#include <unistd.h>

int mod(){
    int choose;
    printf("\n\n\n");
    printf("\t[1] Single Player\n");
    printf("\t[2] Multiplayer\n\n");
    printf("\tChoose mod: ");
    scanf("%d", &choose);
    
    return choose;
}
