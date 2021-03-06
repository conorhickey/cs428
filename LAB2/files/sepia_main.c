#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "image.h"

void usage(void)
{
    printf("usage: zoom infile outfile\n");
}

int main(int argc, char **argv)
{
    struct image im, sim;
    struct timespec start, end;
    double accum;

    FILE *inf, *outf;

    if (argc != 3) {
        usage();
        exit(1);
    }

    /* open files */
    if (strlen(argv[1]) == 1 && argv[1][0] == '-') {
        inf  = stdin;
    } else {
        inf = fopen(argv[1], "r");
    }

    if (strlen(argv[1]) == 1 && argv[1][0] == '-') {
        outf = stdout;
    } else {
        outf = fopen(argv[2], "w");
    }

    /* read file */
    imbread(inf, &im);


    /* timing */
    clock_gettime(CLOCK_REALTIME, &start);

    /* perform the image transformation */
    sepia(&im, &sim);

    /* timing */
    clock_gettime(CLOCK_REALTIME, &end);

    /* write the new file */
    imbwrite(outf, &sim);

    /* calculate time it took and print it */
    accum = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1E9;
    fprintf(stderr, "%lf\n", accum );

    return 0;
}
