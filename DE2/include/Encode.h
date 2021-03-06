#ifndef ENCODE_H
#define ENCODE_H

#include "../include/Utility.h"
#include "../include/CodingUnitStructure.h"
#include "../include/Bitstream.h"

void CopyReferenceSamples(
	unsigned char *referenceBuffer, 
	unsigned char *inputY, 
	int cuX, 
	int cuY, 
	int stride,
	int codingUnitWidth,
	int codingUnitHeight);

int ComputeCost(
	unsigned char *input, 
	int inputStride, 
	unsigned char *recon, 
	int reconStride, 
	int width, 
	int height);

void Decode(
	CuIntBuffer transformBufferDWord,
	CuBuffer reconBuffer,
	unsigned char *referenceBuffer,
	int predictionMode, 
	int codingUnitWidth,
	int codingUnitHeight,
	int *qp);

void EncodeDecode(
	// OUT
	CuIntBuffer transformBuffer, 
	CuBuffer reconBuffer,
	// IN
	unsigned char *inputCU,
	int cuStride,
	unsigned char *referenceBuffer,
	int predictionMode, 
	int codingUnitWidth, 
	int codingUnitHeight,
	int *qp,
	int processType);

void EncodeCu(
	CodingUnitStructure_t *codingUnitStructure, 
	int cuX, 
	int cuY);

void DecodeLoop(
	CodingUnitStructure_t *codingUnitStructure
	);

void EncodeLoop(
	CodingUnitStructure_t *codingUnitStructure);

void GenerateBitstream(
	CodingUnitStructure_t *codingUnitStructure,
	Bitstream_t *outputBitstream);

#endif
