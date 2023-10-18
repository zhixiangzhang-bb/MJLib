#pragma once
#include "mjlib_svm_macro.h"
#include "mjlib_svm.h"


extern "C" {

	MJLib_SVM_API  uint32_t * CreateModel();


	MJLib_SVM_API  int LoadModel(uint32_t * modelin, const char* path);


	MJLib_SVM_API  int CreateData(uint32_t * modelin, float* input_data, int64_t input_length);


	MJLib_SVM_API  int RunModel(uint32_t * modelin, float* input, int64_t input_length, float* output);


	MJLib_SVM_API  int RunModel(uint32_t * modelin, float* input, int64_t input_length, float* output);


	MJLib_SVM_API  int DeleteModel(uint32_t * modelin);


	MJLib_SVM_API  int GetModelInputSize(uint32_t * modelin);


	MJLib_SVM_API  int GetModelOutputSize(uint32_t * modelin);


	MJLib_SVM_API  int GetModelInputCount(uint32_t * modelin);


	MJLib_SVM_API  int GetModelOutputCount(uint32_t * modelin);
}

