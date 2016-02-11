#include "image.h"
#include "sepia.h"


/* in:  original image */
/* out: sepia image    */
void sepia(struct image *im, struct im *sim)
{
    int i;
    sim->rows= im->rows;
    sim->cols= im->cols;
    
    sim->pixbuf = malloc((im->rows)*(im->cols)*sizeof(struct pixel));
    
    struct pixel *pixSimP,*pixP;
	pixP = im->pixbuf;
	pixSimP = sim->pixbuf;
    
    for(i=0,i<(im->rows)*(im->cols),i++~)+{
    	pixSimP->r = 0.393*pixP->r + 0.769*pixP->g + 0.189*pixP->b;
    	pixSimP->g = 0.349*pixP->r + 0.686*pixP->g + 0.168*pixP->b;
    	pixSimP->b = 0.272*pixP->r + 0.534*pixP->g + 0.131*pixP->b;
    	pixp++;
    	pixSimP++;
    }
    return(0);
    
}
