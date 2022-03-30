#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string.h> 
#include <stdlib.h>
#include <termios.h>

typedef struct grandezze{
    char tet[100];
    int size;
} gr;

struct grandezze g[5];

void tet(){
    g[1].size = 3;
    g[1].tet = "#";
}
