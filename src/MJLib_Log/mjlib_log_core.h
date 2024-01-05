#pragma once
#include "mjlib_log_global.h"




namespace mjlib {

	namespace log {


		class MJLib_Log_API Log {
		public:

			Log(const char* name);

			int32_t UpdateStatus(std::vector<int8_t>& info, std::vector<int8_t>& error, std::vector<int8_t>& fatal);

			//写入日志
			int32_t Message(std::string message, const int32_t level);

			//设置数字量判断文本
			int32_t SetText(std::vector<std::string>& info_message, std::vector<std::string>& error_message, std::vector<std::string>& fatal_message);

		private:
			std::vector<std::string> info_message;

			std::vector<std::string> error_message;

			std::vector<std::string> fatal_message;

			std::vector<int8_t> info;

			std::vector<int8_t> error;

			std::vector<int8_t> fatal;


		};


	}
}


