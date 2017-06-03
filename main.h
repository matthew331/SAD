#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sad_cpu.h"
#include "sad_openmp.h"

#define INVALID_DISP_SCALED 1023

#define __min(a, b) ((a) < (b) ? (a) : (b))
#define __max(a, b) ((a) > (b) ? (a) : (b))



void SAD_CPU(unsigned short *mCostBuf, char *imgSrcL, char *imgSrcR, int srcWidth, int srcHeight, int disparityRange);
void WinnerTakeAll(unsigned short *a_pwDisparityBuf, unsigned short *a_pwCost, int a_uwWidth, int a_uwHeight, int a_ptDisparity);

void MP_SAD_CPU(unsigned short *mCostBuf, char *imgSrcL, char *imgSrcR, int srcWidth, int srcHeight, int disparityRange);
void MP_WinnerTakeAll(unsigned short *a_pwDisparityBuf, unsigned short *a_pwCost, int a_uwWidth, int a_uwHeight, int a_ptDisparity);


#endif
