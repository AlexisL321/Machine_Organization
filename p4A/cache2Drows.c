////////////////////////////////////////////////////////////////////////////////
// Author:           Alexis Liu 
// Email:            liu2256@wisc.edu 
// CS Login:         alexisl 
//////////////////////////// 80 columns wide ///////////////////////////////////
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int arr2D[3000][500];

int main(int argc, char** argv) {
	for (int i = 0; i < 3000; i++){
		for (int j = 0; j < 500; j++) {
			arr2D[i][j] = i + j;
		}
	}
	return 0;
}
