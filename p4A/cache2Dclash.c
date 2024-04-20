////////////////////////////////////////////////////////////////////////////////
// Author:           Alexis Liu 
// Email:            liu2256@wisc.edu 
// CS Login:         alexisl 
//////////////////////////// 80 columns wide ///////////////////////////////////
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int arr2D[128][8];

int main(int argc, char** argv) {
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 128; j = j + 64) {
			for (int k = 0; k < 8; k++) {
				arr2D[j][k] = i + j + k;
			}
		}
	}
	return 0;
}
