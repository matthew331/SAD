#include<sys/time.h>
#include "main.h"

#define depthGain 2


#define L_FILE_NAME 1
#define R_FILE_NAME 2
#define DEPTH_FILE_NAME 3
#define PICTURE_SIZE_WIDTH 4
#define PICTURE_SIZE_HEIGHT 5
#define DISPARITY_LENGHT 6
#define NUM_OF_THREADS_USED 7
// arg1: L file name
// arg2: R file name
// arg3: Depth file name
// arg4: Picture size Width
// arg5: Picture size Height
// arg6: Disparity length

unsigned int getMSTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000+tv.tv_usec/1000;
}

int main(int argc, char * argv[])
{
	FILE *fp_L, *fp_R, *fp_Depth;
	int ps_width, ps_height, disparity_length;

	char *image_L, *image_R;
	unsigned short *costCube, *depth;
	int pictureSize, depthSize;
	
	#ifdef _SAD_OPENMP_
	int numOfThreads;
	#endif

	char *fileNameL, *fileNameR, *fileNameDepth;

	#ifdef _SAD_OPENMP_
	if(argc != 8) return 0;
	#else
	if(argc != 7) return 0;
	#endif

	fileNameL = argv[L_FILE_NAME];
	fileNameR = argv[R_FILE_NAME];
	fileNameDepth = argv[DEPTH_FILE_NAME];
	ps_width = atoi(argv[PICTURE_SIZE_WIDTH]);
	ps_height = atoi(argv[PICTURE_SIZE_HEIGHT]);
	disparity_length = atoi(argv[DISPARITY_LENGHT]);
	#ifdef _SAD_OPENMP_
	numOfThreads = atoi(argv[NUM_OF_THREADS_USED]);
	#endif

	// printf("L_IMG [%s] \n", fileNameL);
	// printf("R_IMG [%s] \n", fileNameR);
	// printf("Depth [%s] \n", fileNameDepth);
	// printf("SIZE [%dx%d] \n", ps_width, ps_height);
	// printf("Disparity Length [%d] \n", disparity_length);
	
	
	pictureSize = ps_width * ps_height * 3;
	depthSize = sizeof(unsigned short) * ps_width * ps_height;

	// printf("Allocate imageL\n");
	image_L = (char *)malloc(pictureSize);
	// printf("Allocate imageR\n");
	image_R = (char *)malloc(pictureSize);
	// printf("Allocate Depth\n");
	depth = (unsigned short *)malloc(depthSize);
	// printf("Allocate Cost Cube\n");
	costCube = (unsigned short *)malloc(depthSize * disparity_length);

	if((fp_L = fopen(fileNameL, "rb"))!=NULL)
	{	    
		(void)fread(image_L, 1, pictureSize, fp_L);
		fclose(fp_L);
		// printf("Close image_L\n");
	} else {
		printf("Open image_L failed!\n");
	}

	if((fp_R = fopen(fileNameR, "rb"))!=NULL)
	{	    
		(void)fread(image_R, 1, pictureSize, fp_R);
		fclose(fp_L);
		// printf("Close image_R\n");
	} else {
		printf("Open image_R failed!\n");
	}
	

	//MedianFilterUC(image_L, image_L, ps_width, ps_height);
	//MedianFilterUC(image_L + ps_width*ps_height,	image_L + ps_width*ps_height,	ps_width, ps_height);
	//MedianFilterUC(image_L + ps_width*ps_height*2,	image_L + ps_width*ps_height*2,	ps_width, ps_height);
	
	//MedianFilterUC(image_R, image_R, ps_width, ps_height);
	//MedianFilterUC(image_R + ps_width*ps_height,	image_R + ps_width*ps_height,	ps_width, ps_height);
	//MedianFilterUC(image_R + ps_width*ps_height*2,	image_R + ps_width*ps_height*2,	ps_width, ps_height);

	int t1 = getMSTime();
	#ifdef _SAD_OPENMP_
	omp_set_num_threads(numOfThreads);
	MP_SAD_CPU(costCube, image_L, image_R, ps_width, ps_height, disparity_length);
	MP_WinnerTakeAll(depth, costCube, (unsigned short)ps_width, (unsigned short)ps_height, (unsigned char)disparity_length);
	MP_Gain(depth, depth, ps_width, ps_height, (unsigned char)depthGain);
	#else
	SAD_CPU(costCube, image_L, image_R, ps_width, ps_height, disparity_length);
	WinnerTakeAll(depth, costCube, (unsigned short)ps_width, (unsigned short)ps_height, (unsigned char)disparity_length);
	Gain(depth, depth, ps_width, ps_height, (unsigned char)depthGain);	
	#endif

	printf("SAD Time: %d \n", getMSTime() - t1);

	//memcpy(depth, costCube, depthSize);

	if((fp_Depth = fopen(fileNameDepth, "wb"))!=NULL)
	{	    
		fwrite(depth, 1, depthSize, fp_Depth);
		fclose(fp_Depth);
		// printf("Close depth\n");
	} else {
		printf("Open depth failed!\n");
	}

	if(image_L != NULL) free(image_L);
	if(image_R != NULL) free(image_R);
	if(depth != NULL) free(depth);
	if(costCube != NULL) free(costCube);
	
	return 0;

}


