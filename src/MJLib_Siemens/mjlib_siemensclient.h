// MJLib_Siemens.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once



#include <iostream>
#include "mjlib_siemens_global.h"






namespace mjlib {

	namespace siemens {

		/*****************************************************************
		* 类名称：连接西门子服务器
		* 功能描述：作为西门子链接PLC这个
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

			Client(const char* Address, word LocalTSAP, word RemoteTSAP);

			~Client();

			/**
			 * @brief 
			 * @return 返回执行状态 0为成功 
			*/
			int Connect();

			/**
			 * @brief 断开与PLC连接
			 * @return 返回执行状态 0为成功
			*/
			int DisConnect();

			/**
			 * @brief DB数据块读取数据
			 * @param DBNumber 
			 * @param Start 
			 * @param Size 
			 * @param pUsrData 
			 * @return 返回读取状态
			*/
			int Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData);

			/**
			 * @brief DB数据块里写入数据
			 * @param DBNumber DB数据块的编号
			 * @param Start 开始地址
			 * @param Size 长度
			 * @param pUsrData 数据指针区域
			 * @return 
			*/
			int Write_DBWrite(int DBNumber, int Start, int Size, void* pUsrData);

			/**
			 * @brief 设置连接的IP地址
			 * @param ip 需要设置的IP地址
			*/
			int16_t SetIpAddress(const char* ip);

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
