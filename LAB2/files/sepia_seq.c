#include "image.h"
#include "sepia.h"
#include <stdlib.h>


/* in:  original image */
/* out: sepia image    */
void sepia(struct image *im, struct image *sim)
{
    int i;
    uint32_t temp;
    sim->rows= im->rows;
    sim->cols= im->cols;

    sim->pixbuf = malloc((im->rows)*(im->cols)*sizeof(struct pixel));

    struct pixel *pixSimP,*pixP;
	pixP = im->pixbuf;
	pixSimP = sim->pixbuf;


    for(i=0;i<((im->rows)*(im->cols));i++){

    	
    	temp = 0.393*pixP->r + 0.769*pixP->g + 0.189*pixP->b;    	
    	if(temp > 65535){
    	pixSimP->r = 65535;
    	}
    	else{
    	pixSimP->r =temp;
    	}

    	temp = 0.349*pixP->r + 0.686*pixP->g + 0.168*pixP->b;
    	if(temp > 65535){
    	pixSimP->g = 65535;
    	}
    	else{
    	pixSimP->g = temp;
    	}
    	
    	temp = 0.272*pixP->r + 0.534*pixP->g + 0.131*pixP->b;
    	if(temp > 65535){
    	pixSimP->b = 65535;
    	}
    	else{
    	pixSimP->b = temp;
    	}
    	pixSimP->a = pixP->a;
    	pixP++;
    	pixSimP++;
    }
    
}
