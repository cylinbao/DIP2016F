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

void bmpRead(char *filename, bmp *bmpS){
	FILE *inFile;

	printf("Reading file %s\n", filename);
	
	inFile = fopen(filename, "r");
	if(inFile == NULL){
		printf("Can't read file %s\n", filename);
		exit(0);
	}

	fread(&bmpS->id, 1, 2, inFile); assert(bmpS->id == 0x4D42);
	fread(&bmpS->fileSize, 1, 4, inFile);
	fread(&bmpS->reserved, 1, 4, inFile);
	fread(&bmpS->offset, 1, 4, inFile);
	fread(&bmpS->headerSize, 1, 4, inFile); assert(bmpS->headerSize == 40);
	fread(&bmpS->width, 1, 4, inFile);
	fread(&bmpS->height, 1, 4, inFile);
	fread(&bmpS->planes, 1, 2, inFile);
	fread(&bmpS->bitPerPixel, 1, 2, inFile);
	fread(&bmpS->compression, 1, 4, inFile);
	fread(&bmpS->dataSize, 1, 4, inFile);
	fread(&bmpS->hResolution, 1, 4, inFile);
	fread(&bmpS->vResolution, 1, 4, inFile);
	fread(&bmpS->usedColors, 1, 4, inFile);
	fread(&bmpS->importantColors, 1, 4, inFile);

	bmpS->data = malloc(bmpS->dataSize);
	fseek(inFile, bmpS->offset, SEEK_SET);
	fread(bmpS->data, 1, bmpS->dataSize, inFile);

	fclose(inFile);
}

void bmpWrite(char *filename, bmp *bmpS){
	FILE *outFile;
	printf("Write file %s\n", filename);

	outFile = fopen(filename, "w");

	fwrite(&bmpS->id, 1, 2, outFile);
	fwrite(&bmpS->fileSize, 1, 4, outFile);
	fwrite(&bmpS->reserved, 1, 4, outFile);
	fwrite(&bmpS->offset, 1, 4, outFile);
	fwrite(&bmpS->headerSize, 1, 4, outFile);
	fwrite(&bmpS->width, 1, 4, outFile);
	fwrite(&bmpS->height, 1, 4, outFile);
	fwrite(&bmpS->planes, 1, 2, outFile);
	fwrite(&bmpS->bitPerPixel, 1, 2, outFile);
	fwrite(&bmpS->compression, 1, 4, outFile);
	fwrite(&bmpS->dataSize, 1, 4, outFile);
	fwrite(&bmpS->hResolution, 1, 4, outFile);
	fwrite(&bmpS->vResolution, 1, 4, outFile);
	fwrite(&bmpS->usedColors, 1, 4, outFile);
	fwrite(&bmpS->importantColors, 1, 4, outFile);

	fseek(outFile, bmpS->offset, SEEK_SET);
	fwrite(bmpS->data, 1, bmpS->dataSize, outFile);

	fclose(outFile);
}
