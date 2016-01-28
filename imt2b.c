#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image.h"

void usage(void)
{
    printf("usage: imt2b [-r] infile outfile\n");
}

int main(int argc, char *argv[])
{
    char ch;

    while ((ch = getopt(argc, argv, "rh")) != -1) {
        switch (ch) {
        case 'h':
            usage();
            exit(0);
            break;
        case 'r':
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
