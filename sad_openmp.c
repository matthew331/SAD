#include "main.h"

void MP_Gain( short *a_pwDstImageBuf, short *a_pwSrcImageBuf, unsigned short a_uwWidth, unsigned short a_uwHeight, unsigned char a_ucGain)
{
	int index_i, index_j;

	printf("%s\n", __func__);
	
	#pragma omp parallel for private(index_i, index_j)
	for ( index_i = 0; index_i < a_uwHeight; index_i++)
    {
        for ( index_j = 0; index_j < a_uwWidth; index_j++)
        {
            a_pwDstImageBuf[index_i*a_uwWidth+index_j] = __min( a_pwSrcImageBuf[index_i*a_uwWidth+index_j]*a_ucGain, INVALID_DISP_SCALED);
        }
    }
}

void MP_WinnerTakeAll(unsigned short *a_pwDisparityBuf, unsigned short *a_pwCost, int a_uwWidth, int a_uwHeight, int a_ptDisparity)
{
	int maxDisparity = a_ptDisparity;
	unsigned int imSize = a_uwWidth * a_uwHeight;
	
	unsigned short *pwDisparityBuf = a_pwDisparityBuf;
	unsigned short *pwCost = a_pwCost;

	int index_i, index_j;

	printf("%s\n", __func__);

	#pragma omp parallel for private(index_i, index_j)
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

void MP_SAD_CPU(unsigned short *mCostBuf, char *imgSrcL, char *imgSrcR, int srcWidth, int srcHeight, int disparityRange)
{
	int disp;

	int index_height, index_width;

	unsigned char *pucLeftLine = (unsigned char *)imgSrcL;
	unsigned char *pucLeftLine_cb = (unsigned char *)imgSrcL+srcWidth*srcHeight;
	unsigned char *pucLeftLine_cr = (unsigned char *)imgSrcL+srcWidth*srcHeight*2;
	unsigned char *pucRightLine = (unsigned char *)imgSrcR;
	unsigned char *pucRightLine_cb = (unsigned char *)imgSrcR+srcWidth*srcHeight;
	unsigned char *pucRightLine_cr = (unsigned char *)imgSrcR+srcWidth*srcHeight*2;

	unsigned char ucSum_Y,ucSum_Cb,ucSum_Cr;

	printf("%s\n", __func__);
	
	#pragma omp parallel for private(index_height, index_width, disp)
	for ( index_height = 0; index_height < srcHeight; index_height++)
	{
		for ( index_width = 0; index_width < srcWidth; index_width++)
		{
			int pixel = index_height*srcWidth + index_width;
			
			for( disp = 0; disp < disparityRange; disp++)
			{
				if((index_width + disp) >= srcWidth)
				{
					mCostBuf[disp * srcWidth * srcHeight + pixel] = 65535;
				}
				else
				{
					ucSum_Y = abs(pucLeftLine[pixel] - pucRightLine[pixel+disp]);
					ucSum_Cb =(abs(pucLeftLine_cb[pixel] - pucRightLine_cb[pixel+disp]));
					ucSum_Cr =(abs(pucLeftLine_cr[pixel] - pucRightLine_cr[pixel+disp]));
					mCostBuf[disp * srcWidth * srcHeight + pixel] = 170 * ucSum_Y + 43 * (ucSum_Cb + ucSum_Cr);
				}
			}
		}	
	}	
}


