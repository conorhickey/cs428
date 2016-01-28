#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>             /* For the integral types */
#include <stdio.h>              /* For the declaration of FILE */

/* The data type we are using for an image */
struct image {
    uint32_t rows;
    uint32_t cols;
    struct pixel *pixbuf;
};

/* The data type of a pixel */
struct pixel {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t a;
};


/* Prototypes of the functions */

/* Read a file in binary format. Return 0 on success, -1 on failure. */
int imbread(FILE *fp, struct image *im);

/* Write a file in binary format. Return 0 on success, -1 on failure. */
int imbwrite(FILE *fp, struct image *im);

/* Read a file in textual format. Return 0 on success, -1 on failure. */
int imtread(FILE *fp, struct image *im);

/* Write a file in textual format. Return 0 on success, -1 on failure. */
int imtwrite(FILE *fp, struct image *im);


#endif  /* IMAGE_H */
