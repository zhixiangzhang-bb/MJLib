#pragma once


#include "mjlib_dataprocess_global.h"







namespace mjlib {

	namespace dp {

		/**
		 * @brief 将输入字节根据大端顺序排列并转换
		 * @param byteArray 输入字节数组
		 * @return 返回转换的值
		*/
		template<typename T>
		inline T  Byte2DoubleBig(const void* data, const int size);

		//字节流转浮点(小端排列）
		inline double  Byte2DoubleLittle(const std::vector<char>& byteArray);

		//字节流转整形(大端排列）
		inline int16_t  Byte2IntBig(const std::vector<char>& byteArray);

		//字节流转整形(小端排列）
		inline int16_t  Byte2IntLittle(const std::vector<char>& byteArray);

		/**
		 * @brief 
		 * @tparam T 任意数据类型，这里接受各种整形和浮点类型
		 * @param data 输入数据
		 * @return 返回字节数组
		*/
		template<typename T>
		inline const char* Data2Byte(const T& data);

		//浮点转字节
		inline const char*  Double2Byte(const double& data);

		//整形转字节
		inline const char*  Int2Byte(const int& data);




	}
}
