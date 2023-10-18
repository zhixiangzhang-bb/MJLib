// MJLib_Siemens.cpp: 定义应用程序的入口点。
//

#include "mjlib_siemensclient.h"



using namespace std;




namespace mjlib {



	Client::Client()
	{
		S7Object Cilent = Cli_Create();
		const char* address = "192.168.1.20";
		Cli_SetConnectionParams(simens_cilent, address, 0, 2);
	}




	Client::Client(const char* Address, word LocalTSAP, word RemoteTSAP)
	{

	}




	int Client::ConnectTo()
	{
		Cli_ConnectTo(simens_cilent,Address, LocalTSAP, RemoteTSAP);
	}




	int Client::DisConnect()
	{
		Cli_Disconnect(simens_cilent);
	}




	int Client::Read_DBRead(int DBNumber, int Start, int Size, void* pUsrData)
	{
		Cli_DBRead(simens_cilent, DBNumber, Start, Size, pUsrData);
	}


}

