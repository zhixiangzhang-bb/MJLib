#pragma once

#include <onnxruntime_cxx_api.h>
#include <iostream>




#ifdef	MJLib_SVM_EXPORTS
#define MJLib_SVM_API __declspec(dllexport)
#else
#define MJLib_SVM_API __declspec(dllimport)
#endif


