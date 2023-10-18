#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>


#ifdef MJLib_DataProcess_EXPORTS
#define MJLib_DataProcess_API __declspec(dllexport)
#else
#define MJLib_DataProcess_API __declspec(dllimport)
#endif




namespace mjlib {


	enum TD_Idex {
		Default,
	};




	/*****************************************************************
	* 类名称：数据处理基类
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：作为所有时域分析的基类并提供接口
	******************************************************************/



	class DataProcess
	{
	public:
		DataProcess() {};

		virtual float ReturnDataProcessResult(std::vector<float>& signal) = 0;


	};



	/*****************************************************************
	* 类名称：频域分析基类
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：作为所有频域处理的基类，并提供接口
	******************************************************************/



	class FrequencyDomain
	{
	public:
		FrequencyDomain() {};

		virtual float ReturnDataProcessResult(std::vector<float>& signal) = 0;

		/**
		 * @brief 傅里叶变换
		 * @param signal 输入信号
		 * @return 返回Eigen实部+虚部数组
		*/
		static Eigen::VectorXcf FFT(std::vector<float>& signal)
		{
			Eigen::VectorXf value = Eigen::Map<Eigen::VectorXf>(signal.data(), signal.size());
			Eigen::FFT<float> fft;// 执行傅里叶变换
			Eigen::VectorXcf spectrum;
			fft.fwd(spectrum, value);
			return spectrum;
		}

	protected:

	};



}