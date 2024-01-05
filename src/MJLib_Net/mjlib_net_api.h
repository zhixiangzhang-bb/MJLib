#pragma once



#include "mjlib_net_tcp.h"
#include "mjlib_net_siemensclient.h"


#ifdef OS_WINDOWS
# define WINAPI __stdcall
#else
# define WINAPI
#endif


extern "C"
{
	
	MJLib_Net_API int32_t* WINAPI CreateSimensClient_Port(const char* Address, uint16_t TSAP);


	MJLib_Net_API int32_t* WINAPI CreateSimensClient_Slot(const char* Address, int32_t Rack, int32_t Slot);


	MJLib_Net_API int32_t WINAPI Connect(int32_t* Client);


	MJLib_Net_API int32_t WINAPI Disconnect(int32_t* Client);


	MJLib_Net_API int32_t WINAPI Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order,float* pUsrData);


	MJLib_Net_API int32_t WINAPI Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData);


	MJLib_Net_API int32_t WINAPI Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData);


	MJLib_Net_API int32_t WINAPI Read_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData);


	MJLib_Net_API int32_t WINAPI Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData);


	MJLib_Net_API int32_t WINAPI Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData);


	MJLib_Net_API int32_t WINAPI Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData);


	MJLib_Net_API int32_t WINAPI Write_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData);


	MJLib_Net_API int32_t WINAPI GetPlcConnect(int32_t* Client);


	MJLib_Net_API int32_t WINAPI GetPLCStatus(int32_t* Client);


	MJLib_Net_API int32_t WINAPI GetPLCLastError(int32_t* Client);


	MJLib_Net_API void WINAPI DeleteSimensClient(int32_t* Client);

}


