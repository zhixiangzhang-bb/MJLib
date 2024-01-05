#pragma once


#include "mjlib_net_siemensclient.h"
#include "mjlib_net_api.h"



int main()
{
	auto point=CreateSimensClient_Slot("192.168.0.100", 0, 1);
	
	Connect(point);

	std::vector<float> result(75);
	Read_Float(point, mjlib::siemens::DB, 2, 0, 75, mjlib::net::Big_Endian, result.data());


	for (int i = 0; i < result.size(); i++)
	{
		std::cout << result[i] << std::endl;
	}

	return 0;
}


