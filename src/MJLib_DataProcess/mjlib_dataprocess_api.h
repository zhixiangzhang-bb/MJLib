#pragma once


#include "mjlib_frequencydomain.h"
#include "mjlib_prob.h"



extern "C" {


	MJLib_DataProcess_API int CavitationDataProcess(double* value, int length, double* result);


	MJLib_DataProcess_API uint32_t* CreateACFsum();


	MJLib_DataProcess_API double ACFsum(double* value, int length);


	MJLib_DataProcess_API double DataMean(double* value, int length);

}