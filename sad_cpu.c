#include "main.h"

#define PIX_SORT( a, b) { if ((a)>(b)) PIX_SWAP((a),(b)); }
#define PIX_SWAP( a, b) { unsigned char temp=(a);(a)=(b);(b)=temp; }

void Gain(unsigned short *a_pwDstImageBuf, unsigned short *a_pwSrcImageBuf, unsigned short a_uwWidth, unsigned short a_uwHeight, unsigned char a_ucGain)
{
	int index_i, index_j;
	
	for ( index_i=0; index_i<a_uwHeight; index_i++)
    {
        for ( index_j=0; index_j<a_uwWidth; index_j++)
        {
            a_pwDstImageBuf[index_i*a_uwWidth+index_j] = __min( a_pwSrcImageBuf[index_i*a_uwWidth+index_j]*a_ucGain, INVALID_DISP_SCALED);
        }
    }
}

void WinnerTakeAll(unsigned short *a_pwDisparityBuf, unsigned short *a_pwCost, int a_uwWidth, int a_uwHeight, int a_ptDisparity)
{
	int maxDisparity = a_ptDisparity;
	unsigned int imSize = a_uwWidth*a_uwHeight;
	
	unsigned short *pwDisparityBuf = a_pwDisparityBuf;
	unsigned short *pwCost = a_pwCost;

	int index_i, index_j;

	for(index_i = 0; index_i < imSize; index_i++)
	{
		unsigned int minCost = 0xFFFF;
		short winDis = 0;

		for(index_j = 0; index_j < maxDisparity; index_j++)
		{
			if ( pwCost[index_i + (index_j * imSize)] < minCost )
			{
				minCost = pwCost[index_i + (index_j * imSize)];
				winDis = index_j;
			}
		}
		pwDisparityBuf[index_i] = winDis *8; //dis:64 -> dis:1024
	}
}

unsigned char opt_med9_UC( unsigned char *p)
{
	PIX_SORT(p[1], p[2]) ; PIX_SORT(p[4], p[5]) ; PIX_SORT(p[7], p[8]) ;
	PIX_SORT(p[0], p[1]) ; PIX_SORT(p[3], p[4]) ; PIX_SORT(p[6], p[7]) ;
	PIX_SORT(p[1], p[2]) ; PIX_SORT(p[4], p[5]) ; PIX_SORT(p[7], p[8]) ;
	PIX_SORT(p[0], p[3]) ; PIX_SORT(p[5], p[8]) ; PIX_SORT(p[4], p[7]) ;
	PIX_SORT(p[3], p[6]) ; PIX_SORT(p[1], p[4]) ; PIX_SORT(p[2], p[5]) ;
	PIX_SORT(p[4], p[7]) ; PIX_SORT(p[4], p[2]) ; PIX_SORT(p[6], p[4]) ;
	PIX_SORT(p[4], p[2]) ; return(p[4]) ;
}


void MedianFilterUC( unsigned char *a_pwDstImageBuf, unsigned char *a_pwSrcImageBuf, unsigned short a_uwImageWidth, unsigned short a_uwImageHeight)
{
	unsigned char *pwTempBuf = malloc(a_uwImageWidth*a_uwImageHeight);

	memcpy(pwTempBuf, a_pwSrcImageBuf, sizeof(unsigned char)*a_uwImageWidth*a_uwImageHeight);
	//create a sliding window of size 9
	unsigned char awWindow[9];

	long x, y;

	//#pragma omp parallel for schedule(dynamic) num_threads(4)
	for( y=1; y<a_uwImageHeight-1; y++)
	{
		for(x=1; x<a_uwImageWidth-1; x++)
		{
			// Pick up window element
			awWindow[0] = a_pwSrcImageBuf[(y-1)*a_uwImageWidth+x-1];
			awWindow[1] = a_pwSrcImageBuf[(y-1)*a_uwImageWidth+x];
			awWindow[2] = a_pwSrcImageBuf[(y-1)*a_uwImageWidth+x+1];
			awWindow[3] = a_pwSrcImageBuf[y*a_uwImageWidth+x-1];
			awWindow[4] = a_pwSrcImageBuf[y*a_uwImageWidth+x];
			awWindow[5] = a_pwSrcImageBuf[y*a_uwImageWidth+x+1];
			awWindow[6] = a_pwSrcImageBuf[(y+1)*a_uwImageWidth+x-1];
			awWindow[7] = a_pwSrcImageBuf[(y+1)*a_uwImageWidth+x];
			awWindow[8] = a_pwSrcImageBuf[(y+1)*a_uwImageWidth+x+1];

			// sort the window to find median
			opt_med9_UC(awWindow);

			// assign the median to centered element of the matrix
			pwTempBuf[y*a_uwImageWidth+x] = awWindow[4];
		}
	}

	memcpy( a_pwDstImageBuf, pwTempBuf, sizeof(unsigned char)*a_uwImageWidth*a_uwImageHeight);

	if(pwTempBuf != NULL) free(pwTempBuf);
}

void SAD_CPU(unsigned short *mCostBuf, char *imgSrcL, char *imgSrcR, int srcWidth, int srcHeight, int disparityRange)
{
	int disp;

	int index_height, index_width;

	unsigned char *pucLeftLine =  (unsigned char *)imgSrcL;
	unsigned char *pucLeftLine_cb = (unsigned char *)imgSrcL+srcWidth*srcHeight;
	unsigned char *pucLeftLine_cr = (unsigned char *)imgSrcL+srcWidth*srcHeight*2;
	unsigned char *pucRightLine = (unsigned char *)imgSrcR;
	unsigned char *pucRightLine_cb = (unsigned char *)imgSrcR+srcWidth*srcHeight;
	unsigned char *pucRightLine_cr = (unsigned char *)imgSrcR+srcWidth*srcHeight*2;

	unsigned char ucSum_Y,ucSum_Cb,ucSum_Cr;
		
	for ( index_height=0; index_height<srcHeight; index_height++)
	{
		for ( index_width=0; index_width<srcWidth; index_width++)
		{
			int pixel = index_height*srcWidth + index_width;
				
			for( disp=0;disp < disparityRange;disp++)
			{
				if((index_width + disp) >= srcWidth)
				{
					mCostBuf[disp * srcWidth * srcHeight + pixel] = 65535;
				} else {
				
					ucSum_Y = abs(pucLeftLine[pixel]-pucRightLine[pixel+disp]);
					ucSum_Cb =(abs(pucLeftLine_cb[pixel]-pucRightLine_cb[pixel+disp]));
					ucSum_Cr =(abs(pucLeftLine_cr[pixel]-pucRightLine_cr[pixel+disp]));
					mCostBuf[disp * srcWidth * srcHeight + pixel] = 170*ucSum_Y+43*(ucSum_Cb+ucSum_Cr);
				}
			}
		}	
	}	
}

