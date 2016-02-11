#include "image.h"
#include "sepia.h"

/* kernel function */
/*   inbuf:  pixels of the original image */
/*   outbuf: pixels of the sepia image */
/*   r:      number of rows */
/*   c:      number of cols */
__global__ sepia_ker(struct pixel *inbuf, struct pixel *outbuf, int r, int c)
{
    /* Your code goes here */
}

/* in:  original image */
/* out: sepia image    */
void sepia(struct image *im, struct im *sim)
{
    /* Your code goes here */
}
