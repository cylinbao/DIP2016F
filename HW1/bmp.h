#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int UINT32;
typedef unsigned short int UINT16;
typedef unsigned char BYTE;

typedef struct bmp{
	// Bitmap File Header
	UINT16 id;
	UINT32 fileSize;
	UINT32 reserved;
	UINT32 offset;
	// Bitmap Info Header
	UINT32 headerSize;
	UINT32 width;
	UINT32 height;
	UINT16 planes;
	UINT16 bitPerPixel;
	UINT32 compression;
	UINT32 dataSize;
	UINT32 hResolution;
	UINT32 vResolution;
	UINT32 usedColors;
	UINT32 importantColors;
	// Palette
	// Bitmap Data
	BYTE *data;
} bmp;

void setPixel(int bytePP, BYTE *src, BYTE *des){
	int i;

	for(i = 0; i < bytePP; i++)
		des[i] = src[i];
}

int getIdx(int x, int y, int width){
	return y*width+x;
}

void bmpDownRes(bmp *img, int scale){
	int i;
	BYTE temp, mask;

	switch(scale){
		case 0:
			mask = 0b11111100;
			break;
		case 1:
			mask = 0b11110000;
			break;
		case 2:
			mask = 0b11000000;
			break;
	}

	for(i = 0; i < img->dataSize; i++)
		img->data[i] = img->data[i] & mask;
}


void bmpScaleUp(bmp *img){
	printf("Scaling up image\n");

	int i, j, k, bytePP; 
	int x, y;
	int oriIdx, newIdx;
	UINT32 newDataSize = img->dataSize*4;
	UINT32 newWidth = img->width*2;
	UINT32 newHeight = img->height*2;

	BYTE *newData = malloc(newDataSize);

	bytePP = img->bitPerPixel / 8;

	for(i = 0; i < newHeight; i++){
		for(j = 0; j < newWidth; j++){
			if((j+1)%2 == 0 && (i+1)%2 == 0)
				oriIdx = getIdx((j-1)/2, (i-1)/2, img->width);
			else{
				if((j+1)%2 != 0 && (i+1)%2 == 0)
					oriIdx = getIdx((j)/2, (i-1)/2, img->width);
				else if((j+1)%2 == 0 && (i+1)%2 != 0)
					oriIdx = getIdx((j-1)/2, (i)/2, img->width);
				else
					oriIdx = getIdx((j)/2, (i)/2, img->width);
			}
			newIdx = getIdx(j, i, newWidth);
			setPixel(bytePP, &img->data[oriIdx*bytePP], &newData[newIdx*bytePP]);
		}
	}

	free(img->data);
	img->data = newData;
	img->fileSize += newDataSize - img->dataSize;
	img->dataSize = newDataSize;
	img->width = newWidth;
	img->height = newHeight;
}

void bmpScaleDown(bmp *img){
	printf("Scaling down image\n");

	int i, j, k, bytePP; 
	int oriIdx, newIdx;
	UINT32 newDataSize = img->dataSize/4;
	UINT32 newWidth = img->width/2;
	UINT32 newHeight = img->height/2;

	bytePP = img->bitPerPixel/8;
	printf("bytePP = %d\n", bytePP);
	BYTE *newData = malloc(newDataSize);

	for(i = 0; i < newHeight; i++){
		for(j = 0; j < newWidth; j++){
			oriIdx = getIdx(j*2, i*2, img->width);
			newIdx = getIdx(j, i, newWidth);
			setPixel(bytePP, &img->data[oriIdx*bytePP], &newData[newIdx*bytePP]);
		}
	}

	free(img->data);
	img->data = newData;
	img->fileSize -= img->dataSize - newDataSize;
	img->dataSize = newDataSize;
	img->width = newWidth;
	img->height = newHeight;
}

void bmpRead(char *filename, bmp *img){
	FILE *inFile;

	printf("Reading file %s\n", filename);
	
	inFile = fopen(filename, "r");
	if(inFile == NULL){
		printf("Can't open file %s\n", filename);
		exit(0);
	}

	fread(&img->id, 1, 2, inFile); assert(img->id == 0x4D42);
	fread(&img->fileSize, 1, 4, inFile);
	fread(&img->reserved, 1, 4, inFile);
	fread(&img->offset, 1, 4, inFile);
	fread(&img->headerSize, 1, 4, inFile); assert(img->headerSize == 40);
	fread(&img->width, 1, 4, inFile);
	printf("width is %d\n", img->width);
	fread(&img->height, 1, 4, inFile);
	printf("height is %d\n", img->height);
	fread(&img->planes, 1, 2, inFile);
	fread(&img->bitPerPixel, 1, 2, inFile); 
	printf("bitPerPixel is %d\n", img->bitPerPixel);
	fread(&img->compression, 1, 4, inFile); assert(img->compression == 0);
	fread(&img->dataSize, 1, 4, inFile);
	printf("dataSize is %d\n", img->dataSize);
	fread(&img->hResolution, 1, 4, inFile);
	fread(&img->vResolution, 1, 4, inFile);
	fread(&img->usedColors, 1, 4, inFile);
	fread(&img->importantColors, 1, 4, inFile);

	img->data = malloc(img->dataSize);
	fseek(inFile, img->offset, SEEK_SET);
	fread(img->data, 1, img->dataSize, inFile);

	fclose(inFile);

	printf("Read file %s done\n", filename);
}

void bmpWrite(char *filename, bmp *img){
	FILE *outFile;
	printf("Writting file %s\n", filename);

	outFile = fopen(filename, "w");
	if(outFile == NULL){
		printf("Can't open file %s\n", filename);
		exit(0);
	}

	fwrite(&img->id, 1, 2, outFile);
	fwrite(&img->fileSize, 1, 4, outFile);
	fwrite(&img->reserved, 1, 4, outFile);
	fwrite(&img->offset, 1, 4, outFile);
	fwrite(&img->headerSize, 1, 4, outFile);
	fwrite(&img->width, 1, 4, outFile);
	fwrite(&img->height, 1, 4, outFile);
	fwrite(&img->planes, 1, 2, outFile);
	fwrite(&img->bitPerPixel, 1, 2, outFile);
	fwrite(&img->compression, 1, 4, outFile);
	fwrite(&img->dataSize, 1, 4, outFile);
	fwrite(&img->hResolution, 1, 4, outFile);
	fwrite(&img->vResolution, 1, 4, outFile);
	fwrite(&img->usedColors, 1, 4, outFile);
	fwrite(&img->importantColors, 1, 4, outFile);

	fseek(outFile, img->offset, SEEK_SET);
	fwrite(img->data, 1, img->dataSize, outFile);

	fclose(outFile);

	printf("Write file %s done\n", filename);
}
