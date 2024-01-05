// MJLib_Siemens.cpp: 定义应用程序的入口点。
//



#include "mjlib_siemensclient.h"
#include <vector>





namespace mjlib {

	namespace siemens {


		std::string GetErrorText(const int32_t Error)
		{
			char* text=new char[200];
			int32_t len=200;
			Cli_ErrorText(Error, text, len);
			std::string str(text);
			return str;
		}


		Client::Client():Address("192,168,0,1"), LocalTSAP(4226), RemoteTSAP(4226), Simens_Cilent(Cli_Create()),Rack(0),Slot(1)
		{
			
		}



		Client::Client(const char* Address, uint16_t TSAP):Address(Address), 
			LocalTSAP(TSAP), RemoteTSAP(TSAP), Simens_Cilent(Cli_Create()),
			Rack(0), Slot(1)

		{
			
		}

		Client::Client(const char* Address, uint16_t Rack, uint16_t Slot):Address(Address),
			LocalTSAP(4226),RemoteTSAP(4226), Simens_Cilent(Cli_Create()),
			Rack(Rack), Slot(Slot)
		{

		}


		Client::~Client()
		{
			Cli_Destroy(Simens_Cilent);
		}


		//连接PLC
		int16_t Client::Connect()
		{
			if (Address!="")
			{				
				return Cli_ConnectTo(Simens_Cilent, Address, Rack, Slot);
			}
			return 0;
		}


		//断开PLC连接
		int16_t Client::DisConnect()

		{
			return Cli_Disconnect(Simens_Cilent);
		}


		//读取数据块返回浮点数据
		std::vector<float> Client::Read_Float(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order)
		{
			float* data = new float[Size];
			auto sta=Cli_ReadArea(Simens_Cilent, Area, DBNumber, Start, Size, S7WLReal, data);
			if (Order == Big_Endian) {
				SwapByte(data, Size);
			}
			std::vector<float> result(data, data+ Size);
			return result;

		}

		//读取数据块32位整数
		std::vector<int32_t> Client::Read_Int32(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order)
		{
			int32_t* data=new int32_t[Size];
			Cli_ReadArea(Simens_Cilent, Area, DBNumber, Start, Size, S7WLDWord, data);
			if (Order == Big_Endian) {
				SwapByte(data, Size);
			}
			std::vector<int32_t> result(data, data + Size);
			return result;
		}


		//读取数据块16位整数
		std::vector<int16_t> Client::Read_Int16(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order)
		{
			int16_t* data = new int16_t[Size];
			Cli_ReadArea(Simens_Cilent, Area, DBNumber, Start, Size, S7WLWord, data);
			if (Order == Big_Endian) {
				SwapByte(data, Size);
			}
			std::vector<int16_t> result(data, data + Size);
			return result;
		}

		//读取字节
		std::vector<int8_t> Client::Read_Byte(DataArea Area, int DBNumber, int Start, int Size, ByteOrder Order)
		{
			int8_t* data = new int8_t[Size];
			Cli_ReadArea(Simens_Cilent, Area, DBNumber, Start, Size, S7WLWord, data);
			if (Order == Big_Endian) {
				SwapByte(data, Size);
			}
			std::vector<int8_t> result(data, data + Size);
			return result;
		}



		//PLC热启动
		int16_t Client::PlcHotStart()
		{
			return Cli_PlcHotStart(Simens_Cilent);
		}

		//PLC冷启动
		int16_t Client::PlcColdStart()
		{
			return Cli_PlcColdStart(Simens_Cilent);
		}

		//PLC停止
		int16_t Client::PlcStop()
		{
			return Cli_PlcStop(Simens_Cilent);
		}

		//设置IP地址   
		int16_t Client::SetIpAddress(const char* ip)
		{
			Address = ip;
			return 1;
		}

		//设置机架号和槽号
		int16_t Client::SetRack(uint16_t Rack, uint16_t Slot)
		{
			this->Rack = Rack;
			this->Slot = Slot;
			return 1;
		}

		/*****************************************************************
		* 获取状态的函数组
		******************************************************************/

		//获取连接状态
		int32_t Client::GetPlcConnect()
		{
			int32_t status;
			Cli_GetConnected(Simens_Cilent, status);
			return status;
		}

		//获取CPU状态
		int32_t Client::GetPLCStatus()
		{
			int32_t status;
			Cli_GetPlcStatus(Simens_Cilent,status);
			return status;
		}

		//获取最后一个错误
		int32_t Client::GetLastError()
		{	
			int32_t error;
			Cli_GetLastError(Simens_Cilent, error);
			return error;
		}


	}
}

