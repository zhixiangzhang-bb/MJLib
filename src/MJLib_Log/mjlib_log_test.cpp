#pragma once


#include "mjlib_log_api.h"



int main()
{
	auto point=CreateLog("sdasd");
	int8_t num[] = {1,0,2,3};
	UpdateStatus(point, num, 4, num, 4, num, 4);
	int8_t num1[] = { 0,1,0,0 };
	UpdateStatus(point, num1, 4, num1, 4, num1, 4);
}	


