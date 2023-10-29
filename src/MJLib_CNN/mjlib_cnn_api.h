#pragma once

#include "mjlib_cnn_macro.h"




extern "C" {

	MJLib_CNN_API  uint32_t* CNN_CreateModel();


	MJLib_CNN_API int CNN_LoadModel(uint32_t* model, const char* path);


	MJLib_CNN_API  float CNN_ReasoningModel(uint32_t* model, uint32_t* image);


	MJLib_CNN_API int CNN_DeleteModel(uint32_t* model);


}

