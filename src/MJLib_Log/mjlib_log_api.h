#pragma once

#include "mjlib_log_global.h"




extern "C"
{
	MJLib_Log_API int32_t* CreateLog(const char* name);


	MJLib_Log_API int32_t UpdateStatus(int32_t* Log, int8_t* info, uint32_t infosize,int8_t* error, uint32_t errorsize, int8_t* fatal, uint32_t fatalsize);


	MJLib_Log_API int32_t SetText(int32_t* Log, char** info_message, uint32_t info_messages_size, char** error_message, uint32_t error_message_size, char** fatal_message, uint32_t fatal_message_size);


}	