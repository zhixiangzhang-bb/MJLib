#pragma once



#include "mjlib_vision_macro.h"
#include "mjlib_imageprocess.h"
#include "mjlib_imagefileio.h"
#include "mjlib_imagestatistics.h"
#include "mjlib_edgedetection.h"



extern "C" {

	MJLib_Vision_API uint32_t* LVImagePointer2CVImage(unsigned char* LVImagePointer, int lineWidth, int height, int width, int channels);


	MJLib_Vision_API uint32_t * ImageRIO(uint32_t * image, int xStrt, int yStart, int xEnd, int yEnd);


	MJLib_Vision_API uint32_t * ImageGray(uint32_t * image);
}
