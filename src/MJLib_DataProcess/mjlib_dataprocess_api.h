#pragma once


#include "mjlib_frequencydomain.h"
#include "mjlib_prob.h"



extern "C" {


	MJLib_DataProcess_API int CavitationDataProcess(float* value, int length, float* result);


	MJLib_DataProcess_API uint32_t* CreateACFsum();


	MJLib_DataProcess_API float ACFsum(float* value, int length);


	MJLib_DataProcess_API float DataMean(float* value, int length);

}