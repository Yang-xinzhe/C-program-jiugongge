#ifndef _G_BMP_H
#define _G_BMP_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned short WORD; 
typedef unsigned char BYTE; 
typedef unsigned int DWORD; 
typedef int LONG; 
 
typedef struct tagBITMAPFILEHEADER { // bmfh  
	unsigned char reserv[14];
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER{ // bmih  
	DWORD  biSize;  
	LONG   biWidth;  
	LONG   biHeight;  
	WORD   biPlanes;  
	WORD   biBitCount; 
	DWORD  biCompression;  
	DWORD  biSizeImage;  
	LONG   biXPelsPerMeter;  
	LONG   biYPelsPerMeter;  
	DWORD  biClrUsed;  
	DWORD  biClrImportant;  
} BITMAPINFOHEADER;  

typedef struct _tag_bmp {
	int width ;
	int height ;
	void *data; 
}tag_bmp;

tag_bmp *load_bmp(char *filename);

#endif
