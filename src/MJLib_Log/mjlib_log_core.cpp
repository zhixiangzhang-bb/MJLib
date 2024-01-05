#include "mjlib_log_core.h"



namespace mjlib {

	namespace log {

		Log::Log(const char* name)
		{
			google::InitGoogleLogging(name);
			google::SetStderrLogging(google::GLOG_INFO);
		}


		//写入日志
		int32_t Log::Message(std::string message, const int32_t level)
		{

			switch (level)
			{
			case 0://如果是0按常规等级写入
				LOG(INFO) << message;

			case 1://按报警处理
				LOG(WARNING) << message;

			case 2://按错误处理
				LOG(ERROR) << message;

			case 3://按失败处理
				LOG(FATAL) << message;

			default:
				break;
			}
			return 1;
		}


		int32_t Log::UpdateStatus(std::vector<int8_t>& info, std::vector<int8_t>& error, std::vector<int8_t>& fatal)
		{			
			//最先判断错误状态		
			if (this->fatal.empty()) {
				this->fatal = std::move(fatal);
			}
			else {
				for (size_t i = 0; i < fatal.size(); i++)
				{
					//判断是否有状态变化
					if (this->fatal[i] != fatal[i]) {
						std::string status;
						//判断事件离去还是发生
						if (fatal[i]>0) {
							status = "	到达";
						}
						else {
							status = "	离去";
						}
						Message(fatal_message[i]+status,3);
					}
				}
			}

			//判断报警参数
			if (this->error.empty()) {
				this->error = std::move(error);
			}
			else {
				for (size_t i = 0; i < error.size(); i++)
				{
					//判断是否有状态变化
					if (this->error[i] != error[i]) {
						std::string status;
						//判断事件离去还是发生
						if (error[i] > 0) {
							status = "	到达";
						}
						else {
							status = "	离去";
						}
						Message(error_message[i] + status, 3);
					}
				}
			}


			//判断动作参数
			if (this->info.empty()) {
				this->info = std::move(info);
			}
			else {
				for (size_t i = 0; i < info.size(); i++)
				{
					//判断是否有状态变化
					if (this->info[i] != info[i]) {
						std::string status;
						//判断事件离去还是发生
						if (info[i] > 0) {
							status = "	到达";
						}
						else {
							status = "	离去";
						}
						Message(info_message[i] + status, 3);
					}
				}
			}


			return 1;
		}


		int32_t Log::SetText(std::vector<std::string>& info_message, std::vector<std::string>& error_message, std::vector<std::string>& fatal_message)
		{
			this->info_message = std::move(info_message);
			this->error_message = std::move(error_message);
			this->fatal_message = std::move(fatal_message);
			return 1;
		}


	}
}
