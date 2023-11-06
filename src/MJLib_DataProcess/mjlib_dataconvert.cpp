#include "mjlib_dataconvert.h"


namespace mjlib {

	namespace dp {

		template<typename T>
		inline T  Byte2DoubleBig(const void* data,const int size)
		{
			if (byteArray.size() == sizeof(float)) {
				T floatValue;
				memcpy(&floatValue, byteArray.data(), size);
				return T;
			}
		}



		//字节流转浮点(小端排列）
		inline double  Byte2DoubleLittle(const std::vector<char>& byteArray)
		{
			if (byteArray.size() == sizeof(float)) {
				float floatValue;
				memcpy(&floatValue, byteArray.data(), sizeof(float));
				return floatValue;
			}
			else {
				return 0.0;
			}
		}


		//字节流转整形(大端排列）
		inline int16_t  Byte2IntBig(const std::vector<char>& byteArray)
		{
			if (byteArray.size() == sizeof(int16_t)) {
				int16_t Value;
				memcpy(&Value, byteArray.data(), sizeof(int16_t));
				return Value;
			}
			else {
				return 0;
			}
		}


		//字节流转整形(小端排列）
		inline int16_t  Byte2IntLittle(const std::vector<char>& byteArray)
		{
			if (byteArray.size() == sizeof(int16_t)) {
				int16_t Value;
				memcpy(&Value, byteArray.data(), sizeof(int16_t));
				return Value;
			}
			else {
				return 0;
			}
		}

		/**
		 * @brief
		 * @tparam T 任意数据类型，这里接受各种整形和浮点类型
		 * @param data 输入数据
		 * @return 返回字节数组
		*/
		template<typename T>
		inline const char* Data2Byte(const T& data)
		{
			reinterpret_cast<const char*>(&data);
		}



		//浮点转字节
		inline const char*  Double2Byte(const double& data)
		{			
			return reinterpret_cast<const char*>(&data);
		}


		//整形转字节
		inline const char*  Int2Byte(const int& data)
		{
			return reinterpret_cast<const char*>(&data);
		}


	}
}