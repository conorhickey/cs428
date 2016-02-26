#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include <endian.h>

/* Read a file in binary format. Return 0 on success, -1 on failure. */
int imbread(FILE *fp, struct image *im)
{	
	uint16_t temp;
	uint64_t farb;
	uint32_t rows, cols ; 
	//reads in farb value and returns error if not found.
	fread(&farb,8,1,fp);
	farb = be64toh(farb);
	if ( farb != 0x6661726266656c64){
	printf("File not in farbfeld value");
	return -1;
	}
	
	//reads rows and columns
	fread(&rows,4,1,fp);
	fread(&cols,4,1,fp);
	struct pixel *pixP;
	im->rows = rows, im->cols = cols; 
	im->pixbuf = malloc((im->rows)*(im->cols)*sizeof(struct pixel));
	pixP = im->pixbuf;
	
    int i; 
    //returns the type from big endian to host
    for(i= 0; i < (im->rows)*(im->cols); i++){
		fread(&temp,2,1,fp);
		pixP->r = be16toh(temp);
		fread(&temp,2,1,fp);
		pixP->g = be16toh(temp);
		fread(&temp,2,1,fp);
		pixP->b = be16toh(temp);
		fread(&temp,2,1,fp);
		pixP->a = be16toh(temp);
		pixP++;
	}
	return 0;
}

/* Write a file in binary format. Return 0 on success, -1 on failure. */
int imbwrite(FILE *fp, struct image *im)
{
    int i;

	uint16_t temp;
	//writes the farb row and columns in big endian binary
	uint32_t rows = im->rows, cols = im->cols; 
	uint64_t farb = htobe64(0x6661726266656c64);
	fwrite(&farb,8,1,fp);
	rows = htobe32(rows);
	fwrite(&rows,4,1,fp);
	cols = htobe32(cols);
	fwrite(&cols,4,1,fp);
	struct pixel *pixP;
	pixP = im->pixbuf;
	
	
	//writes each pixel in big endian binary
	for(i= 0; i < (im->rows)*(im->cols); i++){
	temp = htobe16(pixP->r);
	fwrite(&temp,2,1,fp);
	temp = htobe16(pixP->g);
	fwrite(&temp,2,1,fp);
	temp = htobe16(pixP->b);
	fwrite(&temp,2,1,fp);
	temp = htobe16(pixP->a);
	fwrite(&temp,2,1,fp);
	pixP++;
	}
	
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
	//reads in rows and columns
	//allocates space
	//scans each pixel
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
	
	//prints rows and columns
	fprintf(fp,"%d %d \n",im->rows,im->cols);
	
	//prints to file the pixels 
	for(i=0; i<(im->rows); i++){
		for (j=0; j<(im->cols); j++){
		fprintf(fp," (%hu, %hu, %hu, %hu) ", pixP->r, pixP->g, pixP->b, pixP->a);				
		pixP++;			
		}
	}
	return 0;


}
