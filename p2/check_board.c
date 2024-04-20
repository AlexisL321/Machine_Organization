///////////////////////////////////////////////////////////////////////////////
// copyright 2021 deb deppeler
// posting or sharing this file is prohibited, including any changes/additions.
//
// we have provided comments and structure for this program to help you get 
// started.  later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 revised to free memory allocated in get_board_size function.
// 01/24/2022 revised to use pointers for clas
//
////////////////////////////////////////////////////////////////////////////////
// main file:        check_board.c  
// this file:        check_board.c
// other files:      None 
// semester:         cs 354 spring 2023
// instructor:       Deppeler 
//
// author:           Alexis Liu
// email:            liu2256@wisc.edu 
// cs login:         alexisl 
// gg#:              7 
//                   (see https://canvas.wisc.edu/groups for your gg number)
//
/////////////////////////// other sources of help //////////////////////////////
// persons:          None  
// online sources:   None 
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delim = ",";  // commas ',' are a common delimiter character for data strings

/* completed (do not edit):       
 * read the first line of input file to get the size of that board.
 * 
 * pre-condition #1: file exists
 * pre-condition #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * post-condition: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line1 = NULL;
	size_t len = 0;

	if ( getline(&line1, &len, fptr) == -1 ) {
		printf("error reading the input file.\n");
		free(line1);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line1, delim);
	*size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}



/* todo:
 * returns 1 if and only if the board is in a valid sudoku board state.
 * otherwise returns 0.
 * 
 * a valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * note: p2a requires only that each row and each column are valid.
 * 
 * board: heap allocated 2d array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
	// check each row whether it violate the rule
	for(int i = 0; i < size; i++){
		int list[size]; // create a list to keep track of numbers appeared
		for (int k = 0; k < size; k++){
			*(list + k) = 0;
		}
		for (int j = 0; j < size; j++){

			if(*( *(board + i) + j) == 0) ;
			else {
				if(*(list + (*(*(board + i) + j)) - 1) == 0)
					*(list + (*(*(board + i) + j)) - 1) = 1;
				else {
					return 0;
				}
			}
		}
	}
	// check each column whether it violate the rule
	for(int j = 0; j < size; j++){
		int list[size];
		for (int k = 0; k < size; k++){
			*(list + k) = 0;
		}

		for (int i = 0; i < size; i++){
			if(*(*(board + i) + j) == 0) ;
			else {
				if(*(list + (*(*(board + i) + j)) - 1) == 0)
					*(list + (*(*(board + i) + j)) - 1) = 1;
				else {
					return 0;
				}
			}
		}
	}


	return 1;
}    



/* todo: complete the main function
 * this program prints "valid" (without quotes) if the input file contains
 * a valid state of a sudoku puzzle board wrt to rows and columns only.
 *
 * a single cla is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (clas)
 * argv: the cla strings, includes the program name
 *
 * returns 0 if able to correctly output valid or invalid.
 * only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

	// todo: check if number of command-line arguments is correct.
	if(argc == 2);
	else {
		printf("Usage: ./check_board <input_filename>\n");
		exit(1);
	}
	// open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("can't open file for reading.\n");
		exit(1);
	}

	// declare local variables.
	int size;

	// todo: call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
	// todo: dynamically allocate a 2d array for given board size.
	int** board;
	board = malloc(size * sizeof(int*));
	if (board == NULL) {
			printf("invalid\n");
		fclose(fp);
		free(fp);
		exit(1);
	}
	for (int i = 0; i < size; i++){
		*(board + i) = malloc(size * sizeof(int));
		if(*(board + i) == NULL){
			printf("invalid\n");
			if (i != 0){
				for (int p = 0; p < i; p++){
					free(*(board + p));
				}
			}
			free(board);
			fclose(fp);
			exit(1);
		}
	}
	// read the rest of the file line by line.
	// tokenize each line wrt the delimiter character 
	// and store the values in your 2d array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("error while reading line %i of the file.\n", i+2);
			free(line);
			exit(1);
		}

		token = strtok(line, delim);
		for (int j = 0; j < size; j++) {
			// todo: complete the line of code below
			// to initialize your 2d array.
			*(*(board + i) + j) = atoi(token);
			token = strtok(NULL, delim);
		}
	}
	free(line);
	// todo: call the function valid_board and print the appropriate
	//       output depending on the function's return value.
	int output;
	output = valid_board(board,size);
	if (output == 0){
		printf("invalid\n");
	}
	else printf("valid\n");
	// todo: free all dynamically allocated memory.
	for (int i = 0; i < size; i++){
		free(*(board + i));
	}
	free(board);
	//close the file.
	if (fclose(fp) != 0) {
		free(fp);
		printf("error while closing the file.\n");
		exit(1);
	} 

	return 0;       
}       

