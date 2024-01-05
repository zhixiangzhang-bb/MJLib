
#include "mjlib_net_api.h"
#include "mjlib_net_tcp.h"
#include "mjlib_net_siemensclient.h"



extern "C"
{

	int32_t* WINAPI CreateSimensClient_Port(const char* Address, uint16_t TSAP)
	{
		return reinterpret_cast<int32_t*>(new mjlib::siemens::Client(Address, TSAP));
	}

	int32_t* WINAPI CreateSimensClient_Slot(const char* Address, int32_t Rack, int32_t Slot)
	{
		return reinterpret_cast<int32_t*>(new mjlib::siemens::Client(Address, Rack, Slot));
	}



	int32_t WINAPI Connect(int32_t* Client)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto state=client->Connect();
		auto connected = client->GetPlcConnect();//连接后判断是否连接成功
		if (connected != 0) {
			return state;
		}
		return 0;
	}


	int32_t WINAPI Disconnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->DisConnect();
	}


	int32_t WINAPI Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);

		std::vector<float> data(Size);
		auto status = client->Read_Float(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), data);
		if (data.empty()) {
			return -1;
		}
		memcpy(pUsrData, data.data(), Size * sizeof(float));//交换数据区域
		return status;

	}


	int32_t WINAPI Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData)
	{		
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);

		std::vector<int32_t> data(Size);
		auto status = client->Read_Int32(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), data);
		memcpy(pUsrData, data.data(), Size * sizeof(int32_t));//交换数据区域
		return status;
	}


	int32_t WINAPI Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		std::vector<int16_t> data(Size);
		auto status = client->Read_Int16(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), data);
		memcpy(pUsrData, data.data(), Size * sizeof(int16_t));//交换数据区域
		return status;
	}


	int32_t WINAPI Read_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		std::vector<int8_t> data(Size);
		auto status = client->Read_Byte(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), data);

		memcpy(pUsrData, data.data(), Size * sizeof(int8_t));//交换数据区域
		return status;
	}


	int32_t WINAPI Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), pUsrData);
	}


	int32_t WINAPI Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), pUsrData);
	}


	int32_t WINAPI Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);

		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), pUsrData);
	}

	
	int32_t WINAPI Write_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::net::ByteOrder>(Order), pUsrData);
	}


	int32_t WINAPI GetPlcConnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPlcConnect();
	}


	int32_t WINAPI GetPLCStatus(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPLCStatus();
	}


	int32_t WINAPI GetPLCLastError(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetLastError();
	}


	void WINAPI DeleteSimensClient(int32_t* Client)
	{
		if (Client != nullptr) {
			auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
			delete client;
		}
	}

}