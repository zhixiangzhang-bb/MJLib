#pragma once

#include <iostream>
#include <Eigen/Dense>


#ifdef MJLib_DataProcess_EXPORTS
#define MJLib_DataProcess_API __declspec(dllexport)
#else
#define MJLib_DataProcess_API __declspec(dllexport)
#endif
//__declspec(dllimport)


#define EIGEN_MAP_VECTORXd(vec, data) \
    Eigen::Map<Eigen::VectorXd> vec(data.data(), data.size())


#define PI 3.14159265358979323846 //π（pi）



namespace mjlib {

	namespace data{


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

			virtual double ReturnDataProcessResult(std::vector<double>& signal) = 0;


		};


	}
}