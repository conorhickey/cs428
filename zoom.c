#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image.h"

void usage(void)
{
    printf("usage: zoom [-f n] infile outfile\n");
}

int main(int argc, char *argv[])
{
    char ch;

    while ((ch = getopt(argc, argv, "f:h")) != -1) {
        switch (ch) {
        case 'h':
            usage();
            exit(0);
            break;
        case 'f':
            /* TODO */
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

    /* TODO */

}
