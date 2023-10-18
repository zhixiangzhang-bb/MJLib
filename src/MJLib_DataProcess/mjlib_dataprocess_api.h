#pragma once


#include "mjlib_frequencydomain.h"
#include "mjlib_timedomain.h"




extern "C" MJLib_DataProcess_API int CavitationDataProcess(float* value, int length, float* result);


extern "C" MJLib_DataProcess_API float ACFsum(float* value,int length);


extern "C" MJLib_DataProcess_API float DataMean(float* value, int length);

