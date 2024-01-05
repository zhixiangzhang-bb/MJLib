#pragma once


#include "mjlib_siemens_global.h"




extern "C"
{
	MJLib_Siemens_API int32_t* CreateSimensClient_Port(const char* Address, uint16_t TSAP);


	MJLib_Siemens_API int32_t* CreateSimensClient_Slot(const char* Address, int32_t Rack, int32_t Slot);


	MJLib_Siemens_API int32_t Connect(int32_t* Client);


	MJLib_Siemens_API int32_t Disconnect(int32_t* Client);


	MJLib_Siemens_API int32_t Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order,float* pUsrData);


	MJLib_Siemens_API int32_t Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData);


	MJLib_Siemens_API int32_t Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData);


	MJLib_Siemens_API int32_t Read_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData);


	MJLib_Siemens_API int32_t Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData);


	MJLib_Siemens_API int32_t Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData);


	MJLib_Siemens_API int32_t Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData);


	MJLib_Siemens_API int32_t Write_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData);


	MJLib_Siemens_API int32_t GetPlcConnect(int32_t* Client);


	MJLib_Siemens_API int32_t GetPLCStatus(int32_t* Client);


	MJLib_Siemens_API int32_t GetPLCLastError(int32_t* Client);


	MJLib_Siemens_API void DeleteSimensClient(int32_t* Client);

}