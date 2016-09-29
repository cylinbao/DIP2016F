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

void bmpDownRes(bmp *img, int scale){

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
	fread(&img->height, 1, 4, inFile);
	fread(&img->planes, 1, 2, inFile);
	fread(&img->bitPerPixel, 1, 2, inFile); 
	//printf("bitPerPixel is %d\n", img->bitPerPixel);
	fread(&img->compression, 1, 4, inFile); assert(img->compression == 0);
	fread(&img->dataSize, 1, 4, inFile);
	//printf("dataSize is %d\n", img->dataSize);
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
