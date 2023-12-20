
#include "mjlib_siemens_api.h"
#include "mjlib_siemensclient.h"



extern "C"
{

	int32_t* CreateSimensClient(const char* Address, int32_t LocalTSAP, int32_t RemoteTSAP)
	{
		return reinterpret_cast<int32_t*>(new mjlib::siemens::Client(Address, LocalTSAP, RemoteTSAP));
	}


	int32_t Connect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->Connect();
	}


	int32_t Disconnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->DisConnect();
	}


	int32_t Read_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, float* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Float(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian);
		if (data.empty()) {
			return 0;
		}
		pUsrData = data.data();
		return 1;
	}


	int32_t Read_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int32_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Int32(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian);
		if (data.empty()) {
			return 0;
		}
		pUsrData = data.data();
		return 1;
	}

	int32_t Read_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int16_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		auto data = client->Read_Int16(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian);
		if (data.empty()) {
			return 0;
		}
		pUsrData = data.data();
		return 1;
	}


	int32_t Write_Float(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, float* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian, pUsrData);
	}


	int32_t Write_Int32(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int32_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian, pUsrData);
	}


	int32_t Write_Int16(int32_t* Client, int Area, int DBNumber, int Start, int Size, mjlib::siemens::ByteOrder Order, int16_t* pUsrData)
	{
		auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
		return client->Write(static_cast<mjlib::siemens::DataArea>(Area), DBNumber, Start, Size, mjlib::siemens::Big_Endian, pUsrData);
	}


	int32_t GetPlcConnect(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPlcConnect();
	}


	int32_t GetPLCStatus(int32_t* Client)
	{
		return reinterpret_cast<mjlib::siemens::Client*>(Client)->GetPLCStatus();
	}


	void DeleteSimensClient(int32_t* Client)
	{
		if (Client != nullptr) {
			auto client = reinterpret_cast<mjlib::siemens::Client*>(Client);
			delete client;
		}
	}
}