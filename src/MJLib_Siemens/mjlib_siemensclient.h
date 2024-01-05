// MJLib_Siemens.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once



#include "mjlib_siemens_global.h"
#include <vector>
#include <algorithm>




namespace mjlib {

	namespace siemens {

		/**
		 * @brief 定义数据类型用于转换
		*/
		enum DataType
		{
			Double,//双精度浮点
			Float,//单精度浮点
			Int32,//32位整数
			Int16,//16位整数
			Bool//数字量
		};

		/**
		 * @brief 定义读取的数据区域
		*/
		enum DataArea
		{
			INPUT=129,//PLC 数据输入区域
			OUTPUT=130,//PLC 数据输出区域
			M=131,//PLC M数据区域
			DB=132,//PLC DB数据区域
			CT=28,//PLC 计数区域
			TM=29//PLC 时间数据区域

		};

		/**
		 * @brief 字节顺序
		*/
		enum ByteOrder
		{
			Big_Endian=0,//大端排序方法，西门子默认
			Little_Endian=1//小端排序方法
		};


		/**
		 * @brief 交换字节顺序，用于西门子
		 * @tparam T 定义的模版数据
		 * @param data 输入数据指针
		 * @param len 输入数据长度
		*/
		template<typename T>
		inline void SwapByte(T* data, int16_t len)
		{
			if (data == nullptr)
			{
				return;
			}
			const int16_t size = sizeof(T);
			unsigned char bytes[size];
			for (size_t i = 0; i < len; i++)
			{
				std::memcpy(bytes, &data[i], size);
				std::reverse(std::begin(bytes), std::end(bytes));
				std::memcpy(&data[i], bytes, size);
			}

		}


		/**
		 * @brief 根据ID获取错误文本
		 * @param Error 错误ID
		 * @return 返回错误字符窜
		*/ 
		inline std::string GetErrorText(const int32_t Error);



		/*****************************************************************
		* 类名称：连接西门子服务器
		* 功能描述：作为西门子链接PLC
		* 作者：zzx
		* 创建日期：2023.10.22
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class Client
		{
		public:

			Client();

			Client(const char* Address, uint16_t TSAP);

			Client(const char* Address, uint16_t Rack, uint16_t Slot);

			~Client();

			/**
			 * @brief 
			 * @return 返回执行状态 0为成功 
			*/
			int16_t Connect();

			/**
			 * @brief 断开与PLC连接
			 * @return 返回执行状态 0为成功
			*/
			int16_t DisConnect();


			/**
			 * @brief DB数据块读取数据
			 * @param DBNumber DB块编号
			 * @param Start  启始地址
			 * @param Size 长度
			 * @return 返回单精度浮点
			*/
			std::vector<float> Read_Float(DataArea Area,int DBNumber, int Start, int Size, ByteOrder Order);

			/**
			 * @brief DB数据块读取数据
			 * @param DBNumber DB块编号
			 * @param Start  启始地址
			 * @param Size 长度
			 * @return 返回32位整数
			*/
			std::vector<int32_t> Read_Int32(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order);

			/**
			 * @brief DB数据块读取数据
			 * @param DBNumber DB块编号
			 * @param Start  启始地址
			 * @param Size 长度
			 * @return 返回16位整数
			*/
			std::vector<int16_t> Read_Int16(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order);

			/**
			 * @brief DB数据块读取数据字节
			 * @param Area 读取区域
			 * @param DBNumber DB块编号
			 * @param Start 启始地址
			 * @param Size 长度
			 * @param Order 字节顺序
			 * @return 返回字节数组
			*/
			std::vector<int8_t> Read_Byte(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order);


			template<typename T>
			std::vector<T> ReadData(DataArea Area, int DBNumber, int Start, int Size, int length, ByteOrder Order)
			{
				switch (Size)
				{
				case 1:
					int8_t * data = new int8_t[Size];
					Cli_ReadArea(Simens_Cilent, Area, DBNumber, Start, Size, S7WLWord, data);
					if (Order == Big_Endian) {
						SwapByte(data, Size);
					}
					std::vector<int8_t> result(data, data + Size);
					return result;
				default:
					break;
				}
			}

			/**
			 * @brief 写入PLC数据
			 * @tparam T 模版数据
			 * @param Area 需要写入的区域
			 * @param DBNumber DB数据块的编号，仅DB时使用
			 * @param Start 启始地址
			 * @param Size 数组长度
			 * @param Order 字节顺序
			 * @param pUsrData 写入数据指针
			 * @return 返回是否写入成功状态
			*/
			template<typename T>
			int16_t Write(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order, T* pUsrData)
			{
				int16_t len = sizeof(T);
				if (Order == Big_Endian) {

					SwapByte(pUsrData, Size);
				}
				return Cli_WriteArea(Simens_Cilent, Area, DBNumber, Start, Size* len, S7WLByte, pUsrData);
			}


			/**
			 * @brief PLC热启动，暂时不能用
			 * @return 返回启动状态
			*/
			int16_t PlcHotStart();

			/**
			 * @brief PLC冷启动，暂时不能用
			 * @return 返回执行状态
			*/
			int16_t PlcColdStart();

			/**
			 * @brief PLC停止，暂时不能用
			 * @return 返回执行状态
			*/
			int16_t PlcStop();

			/**
			 * @brief 设置连接的IP地址
			 * @param ip 需要设置的IP地址
			*/
			int16_t SetIpAddress(const char* ip);

			/**
			 * @brief 设置机架和槽
			 * @param Rack 机架号
			 * @param Slot 槽号
			 * @return 返回是否设置成功
			*/
			int16_t SetRack(uint16_t Rack,uint16_t Slot);


			/*****************************************************************
			* 获取状态信息函数
			******************************************************************/

			/**
			 * @brief 获取与PLC连接状态
			 * @return 返回连接状态
			*/
			int32_t GetPlcConnect();

			/**
			 * @brief 获取PLC的状态
			 * @return 返回PLC的状态 0x00 未知状态  0x08 运行状态 0x04停止状态
			*/
			int32_t GetPLCStatus();

			/**
			 * @brief 获取最后一个错误
			 * @return 返回最后一个错误代码
			*/
			int32_t GetLastError();


		private:
			//西门子PLC连接服务器
			S7Object Simens_Cilent;
			
			//IP地址
			const char* Address;

			//机架号
			int16_t Rack;

			//插槽号
			int16_t Slot;

			//本地端口
			int16_t LocalTSAP;

			//远程端口
			int16_t RemoteTSAP;


		};

	}
}





// TODO: 在此处引用程序需要的其他标头。
