#pragma once


#include "mjlib_siemens_global.h"
#include "mjlib_siemensclient.h"


extern "C"
{
	MJLib_Siemens_API int32_t* CreateSimensClient(const char* Address, int32_t LocalTSAP, int32_t RemoteTSAP);


	MJLib_Siemens_API int32_t Connect(int32_t* Client);


	MJLib_Siemens_API int32_t Disconnect(int32_t* Client);


	MJLib_Siemens_API int32_t Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order,float* pUsrData);


	MJLib_Siemens_API int32_t Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int32_t* pUsrData);


	MJLib_Siemens_API int32_t Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int16_t* pUsrData);


	MJLib_Siemens_API int32_t Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, float* pUsrData);


	MJLib_Siemens_API int32_t Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int32_t* pUsrData);


	MJLib_Siemens_API int32_t Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int16_t* pUsrData);


	MJLib_Siemens_API int32_t GetPlcConnect(int32_t* Client);


	MJLib_Siemens_API int32_t GetPLCStatus(int32_t* Client);


	MJLib_Siemens_API void DeleteSimensClient(int32_t* Client);
}