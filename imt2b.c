#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image.h"
#include <stdbool.h>

void usage(void)
{
    printf("usage: imt2b [-r] infile outfile\n");
}

int main(int argc, char *argv[])
{
	FILE *inf, *outf;
    	char ch;
	bool reverse = false;

	struct image img;


    while ((ch = getopt(argc, argv, "rh")) != -1) {
        switch (ch) {
        case 'h':
            usage();
            exit(0);
            break;
        case 'r':
            reverse = true;
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
	} 

	outf = fopen(argv[1],"w");
	if (outf == NULL){
	printf("No out FIle \n");
	} 
	
    if (reverse){
	return 0;
	}
	else{
	imtread(inf,&img);
	imtwrite(outf,&img);
	}

	return 0;
}
