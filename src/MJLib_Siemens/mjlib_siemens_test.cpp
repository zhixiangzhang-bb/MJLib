#pragma once


#include "mjlib_siemensclient.h"




int main()
{
	
	auto client = new mjlib::siemens::Client("192.168.1.201",2000,2000);
	auto status=client->Connect();
	auto data = client->Read_Float(mjlib::siemens::DB,3,0,10, mjlib::siemens::Big_Endian);
	float* write = new float[10] {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 400.25};
	status=client->Write(mjlib::siemens::DB, 4, 0, 10, mjlib::siemens::Big_Endian, write);
	delete client;
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << data[i] << std::endl;
	}
	return 0;
}



