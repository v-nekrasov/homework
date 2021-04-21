#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
BMPHEAD *Input(const char *sf)
{
	BMPHEAD *h = NULL;
	FILE *f = fopen(sf, "rb");
	int lb=(int)( ((char*)&(h->pal)) - ((char*)&(h->Signature))), i, j, ls;//lb=54
	lb=54;
	char c, *s=NULL;
	if(f==NULL) return NULL;
	h=(BMPHEAD*)malloc(sizeof(*h));
	if(fread(h, lb, 1, f)!=1)
	{
		free (h);
		return NULL;
	}
	for(i=0; i < h->Ptr - lb; i++) 
		fread(&c, 1, 1, f);
	h->v=NULL; h->g=NULL;
	if(h->BitsPerPixel==24)
	{
		ls=(h->SizeImage)/(h->Height);
		s=(char*)malloc(ls);
		h->v=(unsigned char (**)[4])malloc((h->Height)*sizeof(void*)+4*(h->Height)*(h->Width));
		h->v[0]=(unsigned char (*)[4])(h->v+h->Height);
		for(i=1; i<h->Height; i++)
			h->v[i]=h->v[i-1]+h->Width;
		for(i=0; i<h->Height; i++)
		{
			fread(s, 1, ls, f);
			for(j=0; j<h->Width; j++)
			{
				h->v[i][j][0]=s[j*3+2]; // Red
				h->v[i][j][1]=s[j*3+1]; // Green
				h->v[i][j][2]=s[j*3+0]; // Blue 
			}
		}
	}
	else if(h->BitsPerPixel==32)
	{
		ls=(h->SizeImage)/(h->Height);
		s=(char*)malloc(ls);
		h->v=(unsigned char (**)[4])malloc((h->Height)*sizeof(void*)+4*(h->Height)*(h->Width));
		h->v[0]=(unsigned char (*)[4])(h->v+h->Height);
		for(i=1; i<h->Height; i++)
			h->v[i]=h->v[i-1]+h->Width;
		for(i=0; i<h->Height; i++)
		{
			fread(s, 1, ls, f);
			for(j=0; j<h->Width; j++)
			{
				h->v[i][j][0]=s[j*4+2]; // Red
				h->v[i][j][1]=s[j*4+1]; // Green
				h->v[i][j][2]=s[j*4+0]; // Blue 
			}
		}
	}
	else if(h->BitsPerPixel==8)
	{
		ls=(h->SizeImage)/(h->Height);
		s=(char*)malloc(ls);
		h->g=(int (**))malloc((h->Height)*sizeof(void*)+sizeof(int)*(h->Height)*(h->Width));
		h->g[0]=(int (*))(h->g+h->Height);
		for(i=1; i<h->Height; i++)
			h->g[i]=h->g[i-1]+h->Width;
		for(i=0; i<h->Height; i++)
		{
			fread(s, 1, ls, f);
			for(j=0; j<h->Width; j++)
			{
				h->g[i][j]=(int)(unsigned int)(unsigned char)s[j]; // Grayscale 
			}
		}
	}
	free(s);
	fclose(f);
	return h;
}
//----------------------------------------------------------------------
int Output(const char *sf, BMPHEAD *h)
{
	FILE *f = fopen(sf, "wb");
	int lb = 54, i, j, ls;//lb=54
	char c, *s=NULL, pal[256][4];
	if(f==NULL) return -1;
	if(fwrite(h, lb, 1, f)!=1)
		return -1;
	if(h->BitsPerPixel==24||h->BitsPerPixel==32)
		for(i=0; i < h->Ptr - lb; i++) 
			fwrite(&c, 1, 1, f);
	else if(h->BitsPerPixel==8)
	{
		for(i=0; i<256; i++)
			pal[i][0]=pal[i][1]=pal[i][2]=(unsigned char)i;//grayscale
		fwrite(pal, 4, 256, f);
		for(i=0; i < h->Ptr - lb - 4*256; i++) 
			fwrite(&c, 1, 1, f);
	}
	ls=(h->SizeImage)/(h->Height);
	s=(char*)malloc(ls);
	if(h->BitsPerPixel==24)//true color
	{
		for(i=0; i<h->Height; i++)
		{
			for(j=0; j<h->Width; j++)
			{
				s[j*3+2]=h->v[i][j][0]; // Red
				s[j*3+1]=h->v[i][j][1]; // Green
				s[j*3+0]=h->v[i][j][2]; // Blue 
			}
			fwrite(s, 1, ls, f);
		}
	}
	else if(h->BitsPerPixel==32)//true color
	{
	    for(i=0; i<h->Height; i++)
		{
			for(j=0; j<h->Width; j++)
			{
				s[j*4+2]=h->v[i][j][0]; // Red
				s[j*4+1]=h->v[i][j][1]; // Green
				s[j*4+0]=h->v[i][j][2]; // Blue 
			}
			fwrite(s, 1, ls, f);
		}
	}
	else if(h->BitsPerPixel==8)//изображение с палитрой
	{
		ls=(h->SizeImage)/(h->Height);
		s=(char*)malloc(ls);
		for(i=0; i<h->Height; i++)
		{
			
			for(j=0; j<h->Width; j++)
			{
				s[j]=(char)h->g[i][j]; // Grayscale 
			}
			fwrite(s, 1, ls, f);
		}
	}	
	free(s);
	fclose(f);
	return 0;
}
//---------------------------------------------------------------------
unsigned int ui(unsigned char c) {return (unsigned int)c;}
//---------------------------------------------------------------------
int main(void)
{
    BMPHEAD *h1, *h2; int i,j;
	h1=Input("ball.bmp");
//----
	h2=(BMPHEAD*)malloc(sizeof(*h2));
	memcpy(h2, h1, 54);
	printf("%d, %d\n", h2->Height, h2->Width);
	h2->Height += 4;
	h2->Width += 4;
	h2->SizeImage = h2->Height * h2->Width * 3 ;
	h2->FileLength += (3*(2*2*h2->Width + 2*2*h1->Height));
	printf("%d, %d\n", h2->Height, h2->Width);
	h2->v=(unsigned char (**)[4])malloc((h2->Height)*sizeof(void*)+4*(h2->Height)*(h2->Width));
	h2->v[0]=(unsigned char (*)[4])(h2->v + h2->Height);
	for(i = 1; i < h2->Height; i++)
			h2->v[i]=h2->v[i-1]+h2->Width;
	for(i=0; i < h2->Height; i++)
	{
		for(j=0; j < h2->Width; j++)
		{
			h2->v[i][j][0]=0; // Red
			h2->v[i][j][1]=0; // Green
			h2->v[i][j][2]=0; // Blue 
		}
	}
	
	for(i=2; i < h2->Height-2; i++)
	{
		for(j=2; j < h2->Width-2; j++)
		{
			h2->v[i][j][0]=h1->v[i-2][j-2][0]; // Red
			h2->v[i][j][1]=h1->v[i-2][j-2][1]; // Green
			h2->v[i][j][2]=h1->v[i-2][j-2][2]; // Blue 
		}
	}	
//----
	Output("ball2.bmp", h1);			
	Output("ball3.bmp", h2);		
	printf("done\n");
	free(h1->v);
	free(h1);
	free(h2->v);
	free(h2);    
	h1=h2=NULL;
	return 0;
}