

#include "mjlib_dataprocess_api.h"



/**
 * @brief 数据处理集合
 * @param value 数据输入
 * @param length 数据长度
 * @param result 结果指针
 * @return 返回状态
*/
extern "C" int CavitationDataProcess(float* value, int length,float* result)
{
	std::vector<float> arry(value, value + length);

	//时域处理队列
	std::vector<mjlib::DataProcess*> timelist;
	timelist.push_back(new mjlib::DataXppm(500, 500));
	timelist.push_back(new mjlib::DataXpp());
	timelist.push_back(new mjlib::ACFsum(96));
	timelist.push_back(new mjlib::DataVar());
	timelist.push_back(new mjlib::DataH());
	timelist.push_back(new mjlib::DataPth(1.5));
	timelist.push_back(new mjlib::DataPsdMSF(20000));
	timelist.push_back(new mjlib::DataPsdMSF(20000));

	//迭代数据处理
	int cout = 0;
	for (auto var : timelist)
	{
		result[cout] = var->ReturnDataProcessResult(arry);
		cout++;
	}


	return 1;
}




/**
 * @brief 返回时域自相关
 * @param value 数组指针
 * @param length 数组长度
 * @return 返回时域自相关
*/
extern "C" float ACFsum(float* value, int length)
{
	//数组长度小于0直接返回错误状态
	if (length<=0)
	{
		return NAN;
	}
	mjlib::ACFsum* acfsum=new  mjlib::ACFsum;
	try
	{
		std::vector<float> array(value, value + length);
		auto result = acfsum->ReturnDataProcessResult(array);
		delete acfsum;
		return result;
	}
	//映射失败或处理失败返回错误状态
	catch (const std::exception&)
	{
		return NAN;
	}

}


/**
 * @brief 计算均值
 * @param value 输入数组指针
 * @param length 输入数组长度
 * @return 返回计算均值
*/
extern "C" float DataMean(float* value, int length)
{
	//数组长度小于0直接返回错误状态
	if (length <= 0)
	{
		return NAN;
	}
	mjlib::DataMean* mean = new  mjlib::DataMean;
	try
	{
		std::vector<float> array(value, value + length);
		auto result = mean->ReturnDataProcessResult(array);
		delete mean;
		return result;
	}
	//映射失败或处理失败返回错误状态
	catch (const std::exception&)
	{
		return NAN;
	}
}