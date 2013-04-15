#include <string.h> 
#include <stdio.h> 

/***读入一幅BMP图片，得到一个二维数组***/ 




typedef   unsigned   long       DWORD;  
typedef   unsigned   short      WORD;  
typedef   unsigned   int        UINT;   


/* bitmap file header */ 
typedef struct tagBITMAPFILEHEADER 
{ 
	char  type[2]; 
	DWORD fileSize; 
	WORD reserved1; 
	WORD reserved2; 
	DWORD offbits; 
} BITMAPFILEHEADER,*PBITMAPFILEHEADER; 

/* bitmap info header */ 
typedef struct tagBITMAPINFOHEADER 
{ 
	DWORD dwSize; 
	DWORD width; 
	DWORD height; 
	WORD  planes; 
	WORD  bpp; 
	DWORD compression; 
	DWORD sizeImage; 
	DWORD hResolution; 
	DWORD vResolution; 
	DWORD colors; 
	DWORD importantColors; 
} BITMAPINFOHEADER,*PBITMAPINFOHEADER; 


int LoadBMPHeader(BMP_Header *image, char *fileName)
{
	image->fp = fopen(fileName, "rb");
	if (image->fp == NULL)
		return -1;//ERR_FILE_CANT_OPEN;
	fseek(image->fp, 0, SEEK_SET);
	fread(&(image->fileHeader), sizeof(BITMAPFILEHEADER), 1, image->fp);
	fread(&(image->infoHeader), sizeof(BITMAPINFOHEADER), 1, image->fp);
	if (strncmp((char *)&(image->fileHeader.bfType), "BM", 2) != 0)
	{
		fclose(image->fp);
		return -1;//ERR_FMT_NOT_BMP
	}
	if (image->infoHeader.biCompression)
	{
		fclose(image->fp);
		return -1;//ERR_FMT_COMPRESSION
	}
	return 0;
}
/*main() 
{ 
	//char filename[255]; 
	FILE* fp; 
	BITMAPFILEHEADER fileHeader; 
	BITMAPINFOHEADER infoHeader; 
	DWORD width,height; 

	//printf("input the filename of bitmap file:\n"); 
	// scanf("%s",filename); 
	//printf("%s\n",filename); 

fp=fopen("1.bmp","rb");                  
if(fp==NULL)
	{ 
		printf("open file error!\n"); 
		exit(0);                                   
	} 
	fseek(fp,0,0); 

	fread(&fileHeader,sizeof(fileHeader),1,fp); 
	fseek(fp,sizeof(fileHeader),0); 
	fread(&infoHeader,sizeof(infoHeader),1,fp); 
}
*/