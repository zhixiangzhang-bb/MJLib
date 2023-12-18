// MJLib_Siemens.cpp: 定义应用程序的入口点。
//

#include "mjlib_siemensclient.h"



using namespace std;




namespace mjlib {

	namespace siemens {



		Client::Client():Address("0,0,0,0"), LocalTSAP(0), RemoteTSAP(0), Simens_Cilent(Cli_Create())
		{
			
		}



		Client::Client(const char* Address, word LocalTSAP, word RemoteTSAP):Address(Address), LocalTSAP(LocalTSAP), RemoteTSAP(RemoteTSAP), Simens_Cilent(Cli_Create())
		{

		}


		Client::~Client()
		{
			Cli_Destroy(Simens_Cilent);
		}


		//连接PLC
		int Client::Connect()
		{
			if (Address!=""&& Cli_ConnectTo(Simens_Cilent, Address, Rack, Slot))
			{				
				return Cli_Connect(Simens_Cilent);
			}
		}



		//断开PLC连接
		int Client::DisConnect()
		{
			return Cli_Disconnect(Simens_Cilent);
		}

		//读取数据块
		int Client::Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData)
		{
			return Cli_DBRead(Simens_Cilent, DBNumber, Start, Size, pUsrData);
		}

		//写入数据块
		int Client::Write_DBWrite(int DBNumber, int Start, int Size, void* pUsrData)
		{
			return Cli_DBWrite(Simens_Cilent, DBNumber, Start, Size, pUsrData);
		}

		//设置IP地址   
		int16_t Client::SetIpAddress(const char* ip)
		{
			Address = ip;
			return 1;
		}


	}
}

