#pragma once

#include "mjlib_dataprocess_macro.h"



namespace mjlib {

	/**
	 * @brief 根据采样频率计算功率谱密度
	 * @param signal 输入数组
	 * @param sampleRate 采样频率
	 * @return 返回频率和功率谱密度数组
	*/
	MJLib_DataProcess_API std::vector<std::vector<float>>  PSD(std::vector<float>& signal, int sampleRate);
	


	/*****************************************************************
	* 类名称：均方频率
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_DataProcess_API DataPsdMSF :public DataProcess
	{

	public:

		DataPsdMSF();

		DataPsdMSF(int sampleRate);

		float ReturnDataProcessResult(std::vector<float>& signal) override;

		void SetConfig(int sampleRate);


	private:
		//采样频率
		int sampleRate;



	};








}





