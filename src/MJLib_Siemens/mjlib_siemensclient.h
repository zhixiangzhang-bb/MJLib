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

			int ConnectTo();

			int DisConnect();


			int Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData);


			int Write_DBWrite(int DBNumber, int Start, int Size, void* pUsrData);

			/**
			 * @brief 设置连接的IP地址
			 * @param ip 需要设置的IP地址
			*/
			int16_t SetIpAddress(const char* ip);

		private:
			S7Object simens_cilent;

			const char* Address;

			word LocalTSAP;

			word RemoteTSAP;



		};

	}
}





// TODO: 在此处引用程序需要的其他标头。
