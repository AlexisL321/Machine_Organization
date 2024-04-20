#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int size;
	int** magic_square;
} MagicSquare;

MagicSquare *generateMagicSquare(int n) {
	//create MagicSquare Struct and its member elements
	MagicSquare* Square = malloc(sizeof(MagicSquare));
	if (Square == NULL) {
		printf("Struct Square allocation failed.\n");
		exit(0);
	}   
	Square -> size = n;
	Square -> magic_square = malloc(n * sizeof(int*));
	if (Square -> magic_square == NULL){
		printf("magic_square inside Square allocation failed.\n");
		free(Square);
		exit(1);
	}   
	for (int i = 0 ; i < n; i ++){
		*(Square -> magic_square + i) = calloc(n, sizeof(int));
		if (*(Square -> magic_square + i) == NULL) {
			if (i != 0) {
				for (int j = 0; j < i; j++){
					free(*(Square -> magic_square + j));
				}   
			}   
			else {
				free(*Square -> magic_square);
			}   
			free(Square);
			exit(1);
		}   
	}   
	//generate the magic_square
	int rowOffset = 0;
	int colOffset = n * n;
	for (int i = 0; i < n * n; i ++){
		if (*(*(Square -> magic_square + ((rowOffset - i) % n + n) % n)
					+ ((n - 1) / 2 + i + colOffset) % n) != 0) {
			rowOffset += 2;
			colOffset --;
			*(*(Square -> magic_square + ((rowOffset - i) % n + n) % n)
					+ ((n - 1) / 2 + i + colOffset) % n) = i + 1;

		}
		else {
			*(*(Square -> magic_square + ((rowOffset - i) % n + n) % n)
					+ ((n - 1) / 2 + i + colOffset) % n) = i + 1;
		}
	}
	return Square;
}

int main (int argc, char** argv){
	MagicSquare* squarePtr = generateMagicSquare(4);
	//int result;
	int n = 4;
	printf("1\n");
	for (int i = 0 ; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			printf("%d,", *(*(squarePtr -> magic_square + i) + j));
			fflush(stdout);
			//if (result < 0) {
			//TODO: free squarePtr
			//fclose(fp);
			//exit(1);
			//}   
		}   
		printf("%d\n", *(*(squarePtr -> magic_square + i) + n - 1));
		fflush(stdout);
		//if (result < 0) {
		//TODO:free squarePtr
		//fclose(fp);
		//	exit(1);
		//}   
	}   
	return 0;
}
