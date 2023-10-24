
#include "mjlib_dataprocess_api.h"
#include "mjlib_filetxt.h"




int main()
{
	//读取数据文件
	auto arry=mjlib::ReadTxtData2Float("D:/modeltest/waterListen_23-05-30_1415_1.lvm",23);


	for (size_t i = 0; i < 8; i++)
	{
		std::cout << reault[i] << std::endl;
	}


/*
	std::vector<float> test = { 10,20,30,40,-10,-20,-30,-40};

	//频谱转换
	float deltaT = 0.00005;
	//zlib::DataPSD* fft1 = new zlib::DataPSD(1/deltaT);
	//auto test8 = fft1->ReturnDataProcessResult(ary);
	//delete fft1;

	Eigen::Map<Eigen::VectorXf> Psd(test7[0].data(), 52429);
	Eigen::Map<Eigen::VectorXf> f_psd(test7[1].data(), 52429);
	Psd = Psd.array().log10();


	//功率谱均方
	float PsdSum = Psd.sum();

	Eigen::VectorXf f_psd2 = f_psd.array().square();//计算频率的平方
	auto dotProduct = f_psd2.dot(Psd);//计算频率和功率的点积
	auto PsdMSF = dotProduct / PsdSum;
	std::cout  << PsdMSF << std::endl;


	//功率谱重心频率
	float PsdFC = f_psd.dot(Psd)/ PsdSum;
	std::cout << PsdFC << std::endl;
*/


	return 0;
}



