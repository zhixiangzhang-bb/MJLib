
#include "mjlib_log_api.h"
#include "mjlib_log_global.h"
#include "mjlib_log_core.h"


extern "C"
{

	int32_t* CreateLog(const char* name)
	{
		return reinterpret_cast<int32_t*>(new mjlib::log::Log(name));
	}


	int32_t UpdateStatus(int32_t* Log, int8_t* info, uint32_t infosize, int8_t* error, uint32_t errorsize, int8_t* fatal, uint32_t fatalsize)
	{
		return reinterpret_cast<mjlib::log::Log*>(Log)->UpdateStatus(std::vector<int8_t>(info, info + infosize), std::vector<int8_t>(error, error + errorsize), std::vector<int8_t>(fatal, fatal + fatalsize));
	}


	int32_t SetText(int32_t* Log, char** info_message, uint32_t info_messages_size, char** error_message, uint32_t error_message_size, char** fatal_message, uint32_t fatal_message_size)
	{
		auto point = reinterpret_cast<mjlib::log::Log*>(Log);
		std::string<char*> a(info_message, info_message + info_messages_size);
		
	}


}

	

