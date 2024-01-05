#pragma once

#include <iostream>



#ifdef MJLib_DataProcess_EXPORTS
#define MJLib_DataProcess_API __declspec(dllexport)
#else
#define MJLib_DataProcess_API __declspec(dllexport)
#endif



extern "C" {

	MJLib_DataProcess_API  double COD(double* data,int32_t length);


	MJLib_DataProcess_API  int32_t* NewZmp();


	MJLib_DataProcess_API  int32_t AddData(int32_t* point, const double data);


	MJLib_DataProcess_API  int32_t SetBorder(int32_t* point, const double border);


	MJLib_DataProcess_API  int32_t SetLength(int32_t* point, const double size);


	MJLib_DataProcess_API  double GetScore(int32_t* point);


	MJLib_DataProcess_API  int32_t GetStatisticData(int32_t* point, double* data);


	MJLib_DataProcess_API  int32_t DeleteZmp(int32_t* point);
}