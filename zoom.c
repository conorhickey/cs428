#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image.h"
//Conor Hickey 12324806
//Zoom Code

void usage(void)
{
    printf("usage: zoom [-f n] infile outfile\n");
}

int main(int argc, char *argv[])
{
    char ch;
	int factor;
	FILE *inf, *outf;
	struct image img;


    while ((ch = getopt(argc, argv, "f:h")) != -1) {
        switch (ch) {
        case 'h':
            usage();
            exit(0);
            break;
        case 'f':
            factor = atoi(optarg);
            break;
        default:
            break;
        }
    }
    argc -= optind;
    argv += optind;

    if (argc != 2) {
        usage();
        exit(0);
    }

	inf = fopen(argv[0],"r");
	if (inf == NULL){
	printf("No open FIle \n");
	exit(0);
	} 

	outf = fopen(argv[1],"w");
	if (outf == NULL){
	printf("No out FIle \n");
	exit(0);
	} 
	
	imbread(inf,&img); //reads in binary file
	imbzoomwrite(outf,&img, factor); //calls the binary zoom write function which takes an output file and image and the zoom factor
	return 0 ;
}


int imbzoomwrite(FILE *fp, struct image *im,int factor)
{
    int i;
	int j;
	int z;
	uint16_t temp;

	int place;

	uint32_t rows = im->rows, cols = im->cols; 
	uint64_t farb = htobe64(0x6661726266656c64);
	
	//writes the farbfeld value and the new row and column value to the file
	fwrite(&farb,8,1,fp);
	rows = htobe32(rows*factor);
	fwrite(&rows,4,1,fp);
	cols = htobe32(cols*factor);
	fwrite(&cols,4,1,fp);
	
	struct pixel *pixP;
	pixP = im->pixbuf;
	//loops through the rows and columns factor times with place ensuring that the pixp is in the right location
	for(z=0; z< (im->rows);z++){
	place = z*im->rows;
		for(i= 0; i < factor; i++){
			for(j=0; j < im->cols*factor;j++){
				//writes out each part of the pixel rgba.
				temp = htobe16((pixP[(int)place+j/factor]).r);
				fwrite(&temp,2,1,fp);
				temp = htobe16((pixP[(int)place+j/factor]).g);
				fwrite(&temp,2,1,fp);
				temp = htobe16((pixP[(int)place+j/factor]).b);
				fwrite(&temp,2,1,fp);
				temp = htobe16((pixP[(int)place+j/factor]).a);
				fwrite(&temp,2,1,fp);
			}
		}
	}
	
	return 0;
}


