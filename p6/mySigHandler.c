////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

int second_pause = 4; // the second to pause
int counter = 0; //counter for SIGUSR1 signal

/*
   This function is a handler that is used to deal with SIGALRM.
 */
void handler_SIGALRM() {
	pid_t pid = getpid();
	//get the current time in correct format
	time_t current_time;
	time(&current_time);
	char* full_time = ctime(&current_time);
	printf("PID: %d CURRENT TIME: %s", (int)pid, full_time);

	//send SIGALRM 4 seconds later
	alarm(second_pause);
}

/*
   This is a SIGUSR1 handler that can count the number of times that the
   SIGUSR1 is received.
 */
void handler_SIGUSR1() {
	counter++;
	printf("SIGUSR1 handled and counted!\n");

}

/*
   This is SIGINT handler that can print out the number of times SIGUSR1
   is received.
 */
void handler_SIGINT() {
	printf("\nSIGINT handled.\n");
	printf("SIGUSR1 was handled %d times. Exiting now.\n", counter);
	exit(0);
}

/*
   This is the main function that can SEND SIGALRM every 4 seconds
 */
int main (int argc, char* argv[]) {

	//register SIGUSR1 handler
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_SIGUSR1;
	if (sigaction(SIGUSR1, &sa, NULL) != 0) {
		printf("Error binding SIGUSR1 handler.\n");
		exit(1);
	}

	alarm(second_pause);
	//register SIGALRM handler
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_SIGALRM;
	if(sigaction(SIGALRM, &sa, NULL) != 0) {
		printf("Error binding SIGALRM handler.\n");
		exit(1);
	}

	//register SIGINT handler
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_SIGINT;
	if (sigaction(SIGINT, &sa, NULL) != 0) {
		printf("Error binding SIGINT handler.\n");
		exit(1);
	}
	//infite loop
	while (1) {
	}
	return 0;

}
