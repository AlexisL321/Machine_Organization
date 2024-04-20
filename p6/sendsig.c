////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c 
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
#include<signal.h>
#include<time.h>
#include<sys/types.h>

/*
   This main function sends signal to the designated process with 
   pid specified in the command line argument.
 */
int main(int argc, char* argv[]) {

	//check the command line argument has only 3 words
	if (argc != 3) {
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(0);
	}
	char* signal_type = argv[1];
	//convert ascii to int
	int pid = atoi(argv[2]);

	//send different signal according to different user inputs
	if (strcmp(signal_type, "-u") == 0) {
		int kill_result = kill((pid_t)pid, SIGUSR1);
		if (kill_result != 0) {
			printf("Error sending SIGUSR1.\n");
			exit(1);
		}
	}

	if (strcmp(signal_type, "-i") == 0) {
		if (kill((pid_t)pid, SIGINT) != 0) {
			printf("Error sending SIGINT.\n");
			exit(1);
		}
	}
	return 0;
}
