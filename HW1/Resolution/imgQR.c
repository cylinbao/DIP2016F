#include <stdio.h>
#include "../bmp.h"

#define inNum 2
#define inNameLen 14
#define outNum 3
#define outNameLen 14

char inNames[inNum][inNameLen] = {"../input1.bmp", "../input2.bmp"};
char outNames[inNum][outNum][outNameLen] = {
		 	"output1_1.bmp", "output1_2.bmp", "output1_3.bmp",
		 	"output2_1.bmp", "output2_2.bmp", "output2_3.bmp"
		 };

bmp imgs[inNum][outNum];

int main()
{
	int i, j;

	for(i = 0; i < inNum; i++){
		for(j = 0; j < outNum; j++){
			bmpRead(inNames[i], &imgs[i][j]);
			bmpDownRes(&imgs[i][j], j);
			bmpWrite(outNames[i][j], &imgs[i][j]);
		}
	}

	return 0;
}
