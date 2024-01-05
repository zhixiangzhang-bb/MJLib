#pragma once

#include <iostream>




#ifdef MJLib_Net_EXPORTS
#define MJLib_Net_API __declspec(dllexport)
#else
#define MJLib_Net_API __declspec(dllimport)
#endif

namespace mjlib {
	namespace net {

		MJLib_Net_API enum  ByteOrder
		{
			Big_Endian = 0,//大端排序方法，西门子默认
			Little_Endian = 1//小端排序方法
		};



		/**
		 * @brief 交换字节顺序,根据不同的机器按大端排序和小端排序的方法
		 * @tparam T 定义的模版数据
		 * @param data 输入数据指针
		 * @param len 输入数据数组长度，默认为1单个元素
		*/
		template<typename NUM>
		inline void SwapByte(NUM* data, int16_t len = 1)
		{
			if (data == nullptr)
			{
				return;
			}
			const int16_t size = sizeof(NUM);
			unsigned char bytes[size];
			for (size_t i = 0; i < len; i++)
			{
				std::memcpy(bytes, &data[i], size);
				std::reverse(std::begin(bytes), std::end(bytes));
				std::memcpy(&data[i], bytes, size);
			}

		}

		/**
		 * @brief 字节数组转换成其他数据
		 * @tparam NUM 模版数据类型
		 * @param byte 字节数组
		 * @param data 需要转换的数据
		 * @param sort 排序方式
		 * @return 执行结果 -1为错误
		 */
		template<typename NUM>
		inline  int32_t  Char2Data(const char* byte, NUM* data, net::ByteOrder sort = Big_Endian)
		{
			auto size = sizeof(*data);
			//先判断字符串长度是否满足数据类型要求
			if (sizeof(byte) % size != 0) {
				return -1;
			}

			std::memcpy(data, byte, size);
			if (sort == Little_Endian) {
				SwapByte(data, 1);
			}
			return 1;
		}




	}
}