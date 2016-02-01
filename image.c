#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/* Read a file in binary format. Return 0 on success, -1 on failure. */
int imbread(FILE *fp, struct image *im)
{
    int i; 
	
	return 0;
}

/* Write a file in binary format. Return 0 on success, -1 on failure. */
int imbwrite(FILE *fp, struct image *im)
{
    /* Your code here! */
	return 0;
}

/* Read a file in textual format. Return 0 on success, -1 on failure. */
int imtread(FILE *fp, struct image *im)
{
	int i;

	struct pixel *pixP;
	fscanf(fp,"%d %d",&(im->rows),&(im->cols));
	im->pixbuf = malloc((im->rows)*(im->cols)*sizeof(struct pixel));
	pixP = im->pixbuf;
	
	for(i=0; i<(im->rows)*(im->cols); i++){
	fscanf(fp," (%hu, %hu, %hu, %hu) ", &pixP->r, &pixP->g, &pixP->b, &pixP->a);
	pixP++;
	}


	return 0;
}

/* Write a file in textual format. Return 0 on success, -1 on failure. */
int imtwrite(FILE *fp, struct image *im)
{
	int i; 
	int j;
	struct pixel *pixP;
	pixP = im->pixbuf;
	fprintf(fp,"%d %d \n",im->rows,im->cols);
	for(i=0; i<(im->rows); i++){
		for (j=0; j<(im->cols); j++){
		fprintf(fp," (%hu, %hu, %hu, %hu) ", pixP->r, pixP->g, pixP->b, pixP->a);				
		pixP++;			
		}
	}
	return 0;


}
