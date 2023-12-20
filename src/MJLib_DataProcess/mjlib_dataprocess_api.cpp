

#include "mjlib_dataprocess_api.h"




extern "C" {



	/**
	 * @brief 数据处理集合
	 * @param value 数据输入
	 * @param length 数据长度
	 * @param result 结果指针
	 * @return 返回状态
	*/
	int CavitationDataProcess(float* value, int length, float* result)
	{

		std::vector<float> arry(value, value + length);


		//时域处理队列
		std::vector<mjlib::DataProcess*> timelist;
		timelist.push_back(new mjlib::dataclass::DataXppm(500, 500));
		timelist.push_back(new mjlib::dataclass::DataXpp());
		timelist.push_back(new mjlib::dataclass::ACFsum(96));
		timelist.push_back(new mjlib::dataclass::DataVar());
		timelist.push_back(new mjlib::dataclass::DataH());
		timelist.push_back(new mjlib::dataclass::DataPth(1.5));

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
	 * @brief 创建时域自相关类，用于数据处理队列方法
	 * @return 返回类指针
	*/
	uint32_t* CreateACFsum()
	{
		mjlib::data::ACFsum* acfsum = new  mjlib::data::ACFsum;
		return reinterpret_cast<uint32_t*>(acfsum);
	}



	/**
	 * @brief 返回时域自相关
	 * @param value 数组指针
	 * @param length 数组长度
	 * @return 返回时域自相关
	*/
	float ACFsum(float* value, int length)
	{
		//数组长度小于0直接返回错误状态
		{
			return NAN;
		}
		try
		{
			mjlib::data::ACFsum* acfsum = new mjlib::data::ACFsum;
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
	 * @brief 创建功率谱密度重心频率
	 * @return 返回处理指针
	*/
	uint32_t* CreatePsdMSF()
	{
		mjlib::data::DataPsdMSF* PsdMSF = new mjlib::data::DataPsdMSF;
		return reinterpret_cast<uint32_t*>(PsdMSF);
	}




	/**
	 * @brief 计算频率的均方值
	 * @param value 数据指针
	 * @param length 数组长度
	 * @return 返回均方频率
	*/
	float DataPsdMSF(float* value, int length)
	{
		if (length <= 0) {
			return NAN;
		}
		try
		{
			mjlib::data::DataPsdMSF* PsdMsf = new mjlib::data::DataPsdMSF;
			std::vector<float> array(value, value + length);
			auto result = PsdMsf->ReturnDataProcessResult(array);
			delete PsdMsf;
			return result;
		}
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
	float DataMean(float* value, int length)
	{
		//数组长度小于0直接返回错误状态
		if (length <= 0)
		{
			return NAN;
		}
		mjlib::data::DataMean* mean = new  mjlib::data::DataMean;
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




	/**
	 * @brief 计算均方根值
	 * @param value 数据指针
	 * @param length 数据长度
	 * @return 
	*/
	float DataRMS(float* value, int length)
	{
		
		if (length <= 0) {
			return NAN;
		}
		try
		{
			mjlib::data::DataRMS* RMS = new mjlib::data::DataRMS;
			std::vector<float> array(value, value + length);
			auto result = RMS->ReturnDataProcessResult(array);
			delete RMS;
		}
		catch (const std::exception& e)
		{
		return NAN;
	}

	}



}

