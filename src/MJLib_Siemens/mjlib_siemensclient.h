// MJLib_Siemens.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once



#include <iostream>
#include "mjlib_siemens_macro.h"






namespace mjlib {

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

		int ConnectTo();
		
		int DisConnect();


		int Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData);

	private:
		S7Object simens_cilent;

		char* Address;

		word LocalTSAP;

		word RemoteTSAP;



	};

}





// TODO: 在此处引用程序需要的其他标头。
