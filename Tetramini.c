#include "Tetramini.h"

#include <stdlib.h>

int Tet1[]={0,0,0,0,1,1,1,1,0,0,0,0};
int Tet2[]={2,2,2,2};
int Tet3[]={0,0,0,3,3,3,0,0,0};
int Tet4[]={0,4,4,4,4,0,0,0,0};
int Tet5[]={5,5,0,0,5,5,0,0,0};
int Tet6[]={6,0,0,6,6,6,0,0,0};
int Tet7[]={0,0,7,7,7,7,0,0,0};

const Tetramini tetramini[7] = {
	{Tet1, 4},
	{Tet2, 2},
	{Tet3, 3},
	{Tet4, 3},
	{Tet5, 3},
	{Tet6, 3},
	{Tet7, 3},
};

Tetramini
tetramini_n(int size){
	t.size = size;
	t.data = malloc(sizeof(int) * size * size);
	return t;
}

Tetramini
tetramini_o(tetramini_t o.size){
Tetramini t = tetramini_n(other.size);
memcpy(t.data, o.data, sizeof(int) * o.size * o.size);
return t;
}

void rotate_tetramino(Tetramini src, Tetramini *dest){
	int i, j;
	for (i = 0; i < src.size; i++){
		for(j = 0; j < src.size, j++){
			dest->data[j * src.size + src.size - -1] = src.data[i*src.size + j]
		}
	}
	dest->size = src.size;
}

Tetramini
tetramino_random(){
	return tetramini[rand() % 7];
}
