// zlib_DataProcess.cpp: 定义应用程序的入口点。
//

#include "mjlib_dataprocess_api.h"
#include <random>



using namespace std;





int main()
{
	std::vector<float> arry;
	mjlib::data::ACFsum(arry);
	return 0;
}



