#ifndef UTILITY_H
#define UTILITY_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Specify Visual Studio build by checking existance of VS version
#define PI_BUILD	(__GNUC__)
#define VS_BUILD	(_MSC_VER || PI_BUILD)
#define N2_BUILD	!VS_BUILD

/*** DEFINES ***/
#define MAX_CU_DEPTH            (6)                          // log2(CTUSize)
#define MAX_CU_SIZE             (1<<(MAX_CU_DEPTH))         // maximum allowable size of CU, surely 64? (not 1<<7 = 128)

// This algorithm only processes blocks that are 16x16 in size
#define CODING_UNIT_WIDTH			(16)
#define CODING_UNIT_HEIGHT			(16)
#define CODING_UNIT_SCRATCH_SIZE	(CODING_UNIT_WIDTH*CODING_UNIT_HEIGHT)

#define CODING_UNIT_REF_BUFFER_SIZE_Y		(CODING_UNIT_WIDTH + CODING_UNIT_HEIGHT + 1)
#define CODING_UNIT_REF_BUFFER_SIZE_UV		((CODING_UNIT_WIDTH >> 1) + (CODING_UNIT_HEIGHT >> 1) + 1)

// Input Format:
// Width/Height must be divisible evenly by 16
// YUV420 only
#define DEFAULT_PICTURE_WIDTH		(320)
#define DEFAULT_PICTURE_HEIGHT		(240)

#define BIT_DEPTH					(8) // 1 byte
#define DEFAULT_QP_VALUE			(0)

#define DEFAULT_SAMPLE_VALUE		(1 << (BIT_DEPTH - 1))
#define PICTURE_YUV420_SIZE			(((DEFAULT_PICTURE_WIDTH)*(DEFAULT_PICTURE_HEIGHT)*(3))>>1)



// LZ4
#if N2_BUILD
#define LZ4_COMPRESSION_LEVEL (0)
#define LZ4_NUM_PASSES		  (1)
#elif VS_BUILD
#define LZ4_COMPRESSION_LEVEL (25)
#define LZ4_NUM_PASSES		  (2) // More than 2 passes does not further increase compression
#endif

/*** MACRO FUNCTIONS ***/
#define MIN(a, b) (a<b?a:b)
#define MAX(a, b) (a>b?a:b)
#define ABS_DIFF(a, b) (a>b?a-b:b-a)

/*** STRUCTURES ***/
typedef unsigned char CuBuffer[CODING_UNIT_SCRATCH_SIZE];
typedef int CuIntBuffer[CODING_UNIT_SCRATCH_SIZE];

/*** FUNCTIONS ***/
int Clip3(
	const int minVal, 
	const int maxVal, 
	const int a);

void palloc(
	unsigned char **picturePointer, 
	int width, 
	int height);

void FindMaxMinInt(
	int *inputBlock, 
	int inputStride, 
	int width, 
	int height, 
	int *max, 
	int *min);

void SetInputPictureSamplesToValue(
	unsigned char *inputPicture, 
	int width, 
	int height, 
	int value);

void SetInputPictureSamplesToArbitrary(
	unsigned char *inputPicture, 
	int width, 
	int height);

int CheckIdenticalBuffers(
	unsigned char *left,
	int leftStride,
	unsigned char *right,
	int rightStride,
	int width,
	int height);

void CopyBlockByte(
	unsigned char *src,
	int srcStride,
	unsigned char *dest,
	int destStride,
	int width,
	int height);

void CopyCharToIntBuffer(
	CuBuffer src, 
	CuIntBuffer dst, 
	int size);

void CopyDWordToByteBuffer(
	CuIntBuffer src, 
	CuBuffer dst,  
	int size);

void CopyDWordToDWordBuffer(
	int *src, 
	int srcStride, 
	int *dst, 
	int dstStride, 
	int width, 
	int height);

void CopyWordToDWordBuffer(
	short *src, 
	int srcStride, 
	int *dst, 
	int dstStride, 
	int width,
	int height);

void CopyDWordToWordBuffer(
	int *src, 
	int srcStride, 
	short *dst, 
	int dstStride, 
	int width,
	int height);


/*** DEBUG FUNCTIONS **/
void PrintBlock(
	unsigned char *inputBlock, 
	int inputStride, 
	int width, 
	int height);

void PrintBlockSubtraction(
	unsigned char *leftBlock, 
	int leftStride,
	unsigned char *rightBlock, 
	int rightStride, 
	int width, 
	int height);

void PrintBlockInt(
	int *inputBlock, 
	int inputStride, 
	int width, 
	int height);

void PrintReferenceBuffer(
	unsigned char *referenceBufferY, 
	int cuX, 
	int cuY, 
	int size);

#endif
