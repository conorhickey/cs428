//allows the program to compile as C
extern "C"{
#include "sepia.h"
}
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

	//Code similar to sequential code excpet it uses a value i calucalted
	//from 	i = (blockIdx.x * blockDim.x) * threadIdx.x;
	//inbuf and outbuf used instead of PixP and simPixP

	int i;
	uint32_t temp;
	i = (blockIdx.x * blockDim.x) * threadIdx.x;

	if(i<r*c){ 
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
	//sets up various values and pixels
	sim->rows= im->rows;
    sim->cols= im->cols;
    struct pixel *dpixSimP,*dpixP;
    struct pixel *pixSimP,*pixP;   
	
	
	//used to calculate the threads and block size
    int n = sim->rows * sim->cols;
    int size = n*sizeof(struct pixel);
    int n_threads = 1024;
    int n_blocks = (n-1)/(n_threads +1);
	printf("%d\n",n_blocks);
    sim->pixbuf = (struct pixel *)malloc(size);
    pixP = im->pixbuf;
	pixSimP = sim->pixbuf;
	
	//allocates the cuda memory
	cudaMalloc((void **) &dpixSimP,size);
	cudaMalloc((void **) &dpixP,size);
	
	//copies it to device
	cudaMemcpy(dpixP,im->pixbuf,size,cudaMemcpyHostToDevice);
	sepia_ker<<<n_blocks,n_threads>>>(im->pixbuf,sim->pixbuf,im->rows,im->cols);
	
	//copies output from device to host
	cudaMemcpy(sim->pixbuf, dpixSimP, size,cudaMemcpyDeviceToHost);
	
	//Frees up the memory 
	cudaFree(dpixSimP);
	cudaFree(dpixP);
	

}
