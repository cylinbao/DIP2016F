#include <stdio.h>
#include "../bmp.h"

#define inNum 2
#define inNameLen 14
#define outNum 2
#define outNameLen 17

char inNames[inNum][inNameLen] = {"../input1.bmp", "../input2.bmp"};
char *outNames[inNum][outNum] = {
		 	"output1_up.bmp", "output1_down.bmp",
		 	"output2_up.bmp", "output2_down.bmp"
		 };

bmp imgs[inNum][outNum];

int main(int argc, char *argv[])
{
	int i, j;

	printf("argc = %d\n", argc);

	if(argc == 1){
		for(i = 0; i < inNum; i++){
			bmpRead(inNames[i], &imgs[i][0]);
			bmpRead(inNames[i], &imgs[i][1]);
			bmpScaleUp(&imgs[i][0]);
			bmpScaleDown(&imgs[i][1]);
			bmpWrite(outNames[i][0], &imgs[i][0]);
			bmpWrite(outNames[i][1], &imgs[i][1]);
		}
	}
	else if(argc == 2){
		bmpRead(argv[1], &imgs[0][0]);
		bmpRead(argv[1], &imgs[0][1]);
		bmpScaleUp(&imgs[0][0]);
		bmpScaleDown(&imgs[0][1]);
		bmpWrite("scalingDemo_up.bmp", &imgs[0][0]);
		bmpWrite("scalingDemo_down.bmp", &imgs[0][1]);
	}

	return 0;
}
