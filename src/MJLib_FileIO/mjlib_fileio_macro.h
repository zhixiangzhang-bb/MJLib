#pragma once
#include <iostream>



#ifdef MJLib_FileIO_EXPORTS
#define MJLib_FileIO_API __declspec(dllexport)
#else
#define MJLib_FileIO_API __declspec(dllimport)
#endif