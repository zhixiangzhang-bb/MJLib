
#include "mjlib_siemens_api.h"
#include "mjlib_siemensclient.h"




extern "C"
{

	int32_t* CreateSimensClient_Port(const char* Address, uint16_t TSAP)
	{
		return reinterpret_cast<int32_t*>(new mjlib::siemens::Client(Address, TSAP));
	}

	int32_t* CreateSimensClient_Slot(const char* Address, int32_t Rack, int32_t Slot)
	{
		return reinterpret_cast<int32_t*>(new mjlib::siemens::Client(Address, Rack, Slot));
	}



	int32_t Connect(int32_t* Client)
	{
		reinterpret_cast<mjlib::siemens::Client*>(Client)->Connect();
		return 1;
	}


	int32_t Disconnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->DisConnect();
	}


	int32_t Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData)
	{
		if (Start < 0 && Size < 0) {
			return 0;
		}
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Float(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order));
		if (data.empty()) {
			return 0;
		}
		memcpy(pUsrData, data.data(), Size * sizeof(float));//交换数据区域
		return 1;
	}


	int32_t Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData)
	{
		if (Start < 0 && Size < 0) {
			return 0;
		}
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Int32(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order));
		if (data.empty()) {
			return 0;
		}
		memcpy(pUsrData, data.data(), Size * sizeof(int32_t));//交换数据区域
		return 1;
	}


	int32_t Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData)
	{
		if (Start < 0 && Size < 0) {
			return 0;
		}
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Int16(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order));
		if (data.empty()) {
			return 0;
		}
		memcpy(pUsrData, data.data(), Size * sizeof(int16_t));//交换数据区域
		return 1;
	}


	int32_t Read_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData)
	{
		if (Start < 0 && Size < 0){
			return 0;
		}
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto area = static_cast<mjlib::siemens::DataArea>(Area);
		auto order = static_cast<mjlib::siemens::ByteOrder>(Order);
		auto data = client->Read_Byte(area, DBNumber, Start, Size, order);
		if (data.empty()) {
			return 0;
		}
		memcpy(pUsrData, data.data(), Size * sizeof(int8_t));//交换数据区域
		return 1;
	}


	int32_t Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, float* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order), pUsrData);
	}


	int32_t Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int32_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order), pUsrData);
	}


	int32_t Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int16_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, static_cast<mjlib::siemens::ByteOrder>(Order), pUsrData);
	}

	//
	int32_t Write_Byte(int32_t* Client, int Area, int DBNumber, int Start, int Size, int Order, int8_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto area = static_cast<mjlib::siemens::DataArea>(Area);
		auto order = static_cast<mjlib::siemens::ByteOrder>(Order);
		return client->Write(area, DBNumber, Start, Size, order, pUsrData);
	}


	int32_t GetPlcConnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPlcConnect();
	}


	int32_t GetPLCStatus(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPLCStatus();
	}


	int32_t GetPLCLastError(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetLastError();
	}


	void DeleteSimensClient(int32_t* Client)
	{
		if (Client != nullptr) {
			auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
			delete client;
		}
	}

}