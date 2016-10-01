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

typedef struct index{
	UINT32 x;
	UINT32 y;
	UINT32 width;
	UINT32 bytePP;
} index;

typedef struct pixel{
	UINT32 bytePP;
	UINT32 b;
	UINT32 g;
	UINT32 r;
	UINT32 a;
} pixel;

int getDataIdx(index *idx){
	return (idx->y*idx->width + idx->x)*idx->bytePP;
}

pixel* getPixel(index *idx, BYTE *data){
	int i, dataIdx;
	pixel *tmpPix = malloc(sizeof(pixel));

	dataIdx = getDataIdx(idx);

	tmpPix->bytePP = idx->bytePP;
	tmpPix->b = data[dataIdx];
	tmpPix->g = data[dataIdx + 1];
	tmpPix->r = data[dataIdx + 2];
	if(idx->bytePP > 3)
		tmpPix->a = data[dataIdx + 3];

	return tmpPix;
}

void setPixel(pixel *pix, index *idx, BYTE *data){
	int i, dataIdx;

	dataIdx = getDataIdx(idx);

	data[dataIdx] = pix->b;
	data[dataIdx + 1] = pix->g;
	data[dataIdx + 2] = pix->r;
	if(pix->bytePP > 3)
		data[dataIdx + 3] = pix->a;
}

void scaleRep(BYTE *srcData, index *srcIdx, BYTE *desData, index *desIdx){
	pixel *tmpPix;

	tmpPix = getPixel(srcIdx, srcData);
	setPixel(tmpPix, desIdx, desData);
}

void scaleLiInt(BYTE *srcData, index *srcIdx1, index *srcIdx2, 
								BYTE *desData, index *desIdx){
	pixel *pix1, *pix2; 

	pix1 = getPixel(srcIdx1, srcData);
	pix2 = getPixel(srcIdx2, srcData);

	pixel *tmpPix = malloc(sizeof(pixel));

	tmpPix->bytePP = pix1->bytePP;
	tmpPix->b = (pix1->b + pix2->b)/2;
	tmpPix->g = (pix1->g + pix2->g)/2;
	tmpPix->r = (pix1->r + pix2->r)/2;
	if(tmpPix->bytePP > 3)
		tmpPix->a = (pix1->a + pix2->a)/2;

	setPixel(tmpPix, desIdx, desData);
}

void scaleBiliInt(BYTE *srcData, index *srcIdx1, index *srcIdx2, index *srcIdx3, 
									index *srcIdx4, BYTE *desData, index *desIdx){

}

void bmpScaleUp(bmp *img){
	printf("Scaling up image\n");

	int i, j, k, bytePP; 
	int x, y;
	UINT32 newDataSize = img->dataSize*4;
	UINT32 newWidth = img->width*2;
	UINT32 newHeight = img->height*2;
	index srcIdx1, srcIdx2, srcIdx3, srcIdx4;
	index desIdx;

	BYTE *newData = malloc(newDataSize);

	bytePP = img->bitPerPixel / 8;

	for(i = 0; i < newHeight; i++){
		for(j = 0; j < newWidth; j++){
			if((j+1)%2 == 0 && (i+1)%2 == 0){
				srcIdx1.x = (j-1)/2; srcIdx1.y = (i-1)/2;
				srcIdx1.width = img->width; srcIdx1.bytePP = bytePP;
				desIdx.x = j; desIdx.y = i; 
				desIdx.width = newWidth; desIdx.bytePP = bytePP;

				scaleRep(img->data, &srcIdx1, newData, &desIdx);
			}
			else if((j+1)%2 == 0) {
				if(i > 1){
					srcIdx1.x = (j-1)/2; srcIdx1.y = (i-2)/2;
					srcIdx1.width = img->width; srcIdx1.bytePP = bytePP;
					srcIdx2.x = (j-1)/2; srcIdx2.y = i/2;
					srcIdx2.width = img->width; srcIdx2.bytePP = bytePP;

					desIdx.x = j; desIdx.y = i; 
					desIdx.width = newWidth; desIdx.bytePP = bytePP;

					scaleLiInt(img->data, &srcIdx1, &srcIdx2, newData, &desIdx);
				}
			}
			else if((i+1)%2 == 0){
				if(j > 1){
					srcIdx1.x = (j-2)/2; srcIdx1.y = (i-1)/2;
					srcIdx1.width = img->width; srcIdx1.bytePP = bytePP;
					srcIdx2.x = j/2; srcIdx2.y = (i-1)/2;
					srcIdx2.width = img->width; srcIdx2.bytePP = bytePP;

					desIdx.x = j; desIdx.y = i; 
					desIdx.width = newWidth; desIdx.bytePP = bytePP;

					scaleLiInt(img->data, &srcIdx1, &srcIdx2, newData, &desIdx);
				}
			}
			else{
				srcIdx1.x = j/2; srcIdx1.y = i/2;
				srcIdx1.width = img->width; srcIdx1.bytePP = bytePP;
				desIdx.x = j; desIdx.y = i; 
				desIdx.width = newWidth; desIdx.bytePP = bytePP;

				scaleRep(img->data, &srcIdx1, newData, &desIdx);
			}
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
	UINT32 newDataSize = img->dataSize/4;
	UINT32 newWidth = img->width/2;
	UINT32 newHeight = img->height/2;
	index oriIdx, newIdx;

	bytePP = img->bitPerPixel/8;
	printf("bytePP = %d\n", bytePP);
	BYTE *newData = malloc(newDataSize);

	for(i = 0; i < newHeight; i++){
		for(j = 0; j < newWidth; j++){
			oriIdx.x = j*2; oriIdx.y = i*2;
			oriIdx.width = img->width; oriIdx.bytePP = bytePP;
			newIdx.x = j; newIdx.y = i; 
			newIdx.width = newWidth; newIdx.bytePP = bytePP;

			scaleRep(img->data, &oriIdx, newData, &newIdx);
		}
	}

	free(img->data);
	img->data = newData;
	img->fileSize -= img->dataSize - newDataSize;
	img->dataSize = newDataSize;
	img->width = newWidth;
	img->height = newHeight;
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
