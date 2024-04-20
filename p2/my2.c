///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

// add your own File Header information here (as provided in p2A or Commenting guide

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	printf("Enter magic square's size (odd integer >=3)\n");
	int input;
	if (scanf("%i", &input) > 0);
	else {
		printf("scan error.\n");
		exit(1);
	}
	if (input % 2 == 0) {
		printf("Magic square size must be odd.\n");
		exit(1);
	}
	else if ( input < 3) {
		printf("Magic square size must be >= 3.\n");
		exit(1);
	}

	return input;   
} 

/* TODO:
 * Makes a magic square of size n using the 
 * Siamese magic square algorithm or alternate from assignment 
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
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
	int offset = 0;
	/*for (int i = 0; i < n * n; i ++){
		if (*(*(Square -> magic_square + (offset - i) % n) 
					+ ((n - 1) / 2 + i) % n) != 0) {
			offset++;
*(*(Square -> magic_square + (offset - i) % n)
 + ((n - 1) / 2 + i) % n) = i + 1;

		}
		else {
			*(*(Square -> magic_square + (offset - i) % n) 
					+ ((n - 1) / 2 + i) % n) = i + 1;
		}
	}*/


	return Square;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		//TODO:free magic_square
		exit(1);
	}
	int result;
	int n = magic_square -> size;
	for (int i = 0 ; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			result = fprintf(fp,"%d,", *(*(magic_square -> magic_square + i) + j));
			if (result < 0) {
				//TODO: free magic_square
				fclose(fp);
				exit(1);
			}
		}
		result = fprintf(fp, "%d\n", *(*(magic_square -> magic_square + i) + n - 1));
		if (result < 0) {
			//TODO:free magic_square
			fclose(fp);
			exit(1);
		}
	}
	fclose(fp);
}



/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
	// TODO: Check input arguments to get output filename
	if (argc != 2) {
		printf("Usage: ./myMagicSquare <output_filename>\n");
		exit(1);
	}
	char* filename = *(argv + 1);
	// TODO: Get magic square's size from user
	int size = getSize();
	// TODO: Generate the magic square by correctly interpreting 
	//       the algorithm(s) in the write-up or by writing or your own.  
	//       You must confirm that your program produces a 
	//       Magic Sqare as described in the linked Wikipedia page.
	MagicSquare* squarePtr = generateMagicSquare(size); 
	// TODO: Output the magic square
	fileOutputMagicSquare(squarePtr, filename);
	//free the allocated heap memory
	for (int i = 0; i < size; i++){
		free(*(squarePtr -> magic_square + i));
	}
	free(squarePtr);
	return 0;
} 

// S23

