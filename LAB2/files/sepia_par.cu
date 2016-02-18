
#include "image.h"
#include "sepia.h"
#include <stdlib.h>

/* kernel function */
/*   inbuf:  pixels of the original image */
/*   outbuf: pixels of the sepia image */
/*   r:      number of rows */
/*   c:      number of cols */
__global__ void sepia_ker(struct pixel *inbuf, struct pixel *outbuf, int r, int c)
{
	int i;
	uint32_t temp;
	i = blockIdx.x * blockDim.x * threadIdx.x;
	for(i=0;i<r*c;i++){
	//if(i<r*c){    	
		temp = 0.393f * inbuf[i].r + 0.769f * inbuf[i].g + 0.189f * inbuf[i].b;    	
	   	if(temp > 65535){
	   	outbuf[i].r = 65535;
	   	}
	   	else{
	   	     outbuf[i].r =temp;
		}

		temp = 0.349f * inbuf[i].r + 0.686f * inbuf[i].g + 0.168f * inbuf[i].b;
		if(temp > 65535){
		outbuf[i].g = 65535;
		}
		else{
			outbuf[i].g = temp;
		}
			
		temp = 0.272f * inbuf[i].r + 0.534f * inbuf[i].g + 0.131f * inbuf[i].b;
		if(temp > 65535){
		outbuf[i].b = 65535;
		}
		else{
			outbuf[i].b = temp;
		}
		
		outbuf[i].a = inbuf[i].a;
		
     }
}


/* in:  original image */
/* out: sepia image    */
void sepia(struct image *im, struct image *sim)
{	
	sim->rows= im->rows;
    sim->cols= im->cols;
    struct pixel *dpixSimP,*dpixP;
    struct pixel *pixSimP,*pixP;
    int n = sim->rows * sim->cols;
    int n_threads = 1024;
    int n_blocks = (n-1)/1024 +1;
	printf("%d\n",n_blocks);
    sim->pixbuf = (struct pixel *)malloc(n*sizeof(struct pixel));
    pixP = im->pixbuf;
	pixSimP = sim->pixbuf;
	cudaMalloc((void **) &dpixSimP,n*sizeof(struct pixel));
	cudaMalloc((void **) &dpixP,n*sizeof(struct pixel));
	
	cudaMemcpy(dpixSimP,pixSimP, n*sizeof(struct pixel),cudaMemcpyHostToDevice);
	cudaMemcpy(&dpixP, pixP, n*sizeof(struct pixel),cudaMemcpyHostToDevice);
	sepia_ker<<<n_blocks,n_threads>>>(sim->pixbuf,im->pixbuf,im->rows,im->cols);
	
	
	cudaFree(dpixSimP);
	cudaFree(dpixP);
	

}
