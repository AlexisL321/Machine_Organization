////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c 
// This File:        division.c 
// Other Files:      none 
// Semester:         CS 354 Lecture 002 Spring 2023
// Instructor:       deppeler
// 
// Author:           Alexis Liu
// Email:            liu2256@wisc.edu
// CS Login:         alexisl
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
// Online sources:   None
//////////////////////////// 80 columns wide ///////////////////////////////////
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<string.h>
#include<ctype.h>

int count = 0; //# of successful division

/*
   This is a handler function for SIGFPE. It prints out the number of successful
   divisions and then gracefully exit with 0.
 */
void handler_SIGFPE() {
	printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed successfully: %d\n", count);
	printf("The program will be terminated.\n");
	exit(0);
}

/*
   This is a handler for SIGINT. It prints out the number of successful division
   and then gracefully exit with 0.
 */
void handler_SIGINT() {
	printf("\nTotal number of operations completed successfully: %d\n", count);
	printf("The program will be terminated.\n");
	exit(0);
}

/*
   Main function that asks for input for two ints and perform the division 
   between the two.
 */
int main(int argc, char** argv) {
	//register handler function
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_SIGFPE;
	if (sigaction(SIGFPE, &sa, NULL) != 0) {
		printf("Error binding SIGFPE handler.\n");
		exit(1);
	}

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_SIGINT;
	if (sigaction(SIGINT, &sa, NULL) != 0) {
		printf("Error binding SIGINT handler.\n");
		exit(1);
	}

	//ask for user input for two ints and perform division
	while(1) {
		printf("Enter first integer: ");
		char int_c[100];
		memset(int_c, 0, sizeof(int_c));
		fgets(int_c, 100, stdin);

		//check that the number does not contain any non-numeric values
		int length = sizeof(int_c);
		int int1 = atoi(int_c);
		for (int i = 0; i < length; i++) {
			if (isdigit(*(int_c + i)) == 0) {
				if (*(int_c + i) != 10 && *(int_c + i) != 0){
					int1 = 0;
					break;
				}
			}
		}
		printf("Enter second integer: ");
		memset(int_c, 0, sizeof(int_c));
		fgets(int_c, 100, stdin);
		int int2 = atoi(int_c);

		//check the number does not contain any non-numeric values
		for (int i = 0; i < sizeof(int_c); i++) {
			if (isdigit(*(int_c + i)) == 0) {
				if (*(int_c + i) != 10 && *(int_c + i) != 0) {
					int2 = 0;
					break;
				}
			}
		}

		int q = int1 / int2;
		int r = int1 % int2;
		printf("%d / %d is %d with a remainder of %d\n", int1, int2, q, r);
		count++;
	}
	return 0;
}
