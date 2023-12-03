// MJLib_Siemens.cpp: 定义应用程序的入口点。
//

#include "mjlib_siemensclient.h"



using namespace std;




namespace mjlib {

	namespace siemens {



		Client::Client()
		{
			simens_cilent = Cli_Create();
			const char* address = "192.168.1.20";
			Cli_SetConnectionParams(simens_cilent, address, 0, 2);
		}




		Client::Client(const char* Address, word LocalTSAP, word RemoteTSAP)
		{

		}


		/**
		 * @brief 析构函数
		*/
		Client::~Client()
		{

		}


		/**
		 * @brief 根据参数连接
		 * @return 返回是否连接成功状态
		*/
		int Client::ConnectTo()
		{
			if (simens_cilent != NULL&& Address!="")
			{
				return Cli_ConnectTo(simens_cilent, Address, LocalTSAP, RemoteTSAP);
			}
		}



		/**
		 * @brief 断开与服务器的连接
		 * @return 返回是否断开成功
		*/
		int Client::DisConnect()
		{
			return Cli_Disconnect(simens_cilent);
		}


		/**
		 * @brief 读取DB块的数据
		 * @param DBNumber DB块编号
		 * @param Start 开始地址
		 * @param Size 读取长度
		 * @param pUsrData 用户数据指针
		 * @return 
		*/
		int Client::Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData)
		{
			return Cli_DBRead(simens_cilent, DBNumber, Start, Size, pUsrData);
		}



		int Client::Write_DBWrite(int DBNumber, int Start, int Size, void* pUsrData)
		{
			return Cli_DBWrite(simens_cilent, DBNumber, Start, Size, pUsrData);
		}

		   
		int16_t Client::SetIpAddress(const char* ip)
		{
			Address = ip;
		}
	}
}

