#pragma once



#include "mjlib_dataprocess_macro.h"




namespace mjlib {




	/*****************************************************************
	* 类名称：时域自相关和
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API ACFsum :public DataProcess
	{
	public:
		ACFsum();

		ACFsum(int nlags);

		float ReturnDataProcessResult(std::vector<float>& signal) override;

		void SetConfig(int nlags);


	private:
		int nlags;


	protected:

	};





	/*****************************************************************
	* 类名称：均值
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API DataMean :public DataProcess
	{
	public:
		DataMean();

		float ReturnDataProcessResult(std::vector<float>& signal) override;


	};




	/*****************************************************************
	* 类名称：均方根值
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API DataRMS :public DataProcess
	{
	public:
		DataRMS();

		float ReturnDataProcessResult(std::vector<float>& signal) override;


	};




	/*****************************************************************
	* 类名称：信息熵
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API DataH :public DataProcess
	{
	public:
		DataH();

		float ReturnDataProcessResult(std::vector<float>& signal) override;


	};



	/*****************************************************************
	* 类名称：峰峰值
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.18
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_DataProcess_API DataXpp :public DataProcess
	{
	public:
		DataXpp();

		float ReturnDataProcessResult(std::vector<float>& signal) override;


	};




	/*****************************************************************
	* 类名称：均值峰峰值
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：	
	******************************************************************/





	class MJLib_DataProcess_API DataXppm :public DataProcess
	{
	public:
		DataXppm();

		DataXppm(int top_num, int bottom_num);

		float ReturnDataProcessResult(std::vector<float>& signal) override;

		//设置最大最小参数
		void SetConfig(int top_num, int bottom_num);

	private:
		//最大的元素数量
		int top_num;

		//最小的元素数量
		int bottom_num;
	};




	/*****************************************************************
	* 类名称：方差
	* 功能描述：计算一组数的方差
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API DataVar :public DataProcess
	{
	public:
		DataVar();

		float ReturnDataProcessResult(std::vector<float>& signal) override;


	};




	/*****************************************************************
	* 类名称：分位概率
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_DataProcess_API DataPth :public DataProcess
	{
	public:
		DataPth();

		DataPth(float threshold);

		float ReturnDataProcessResult(std::vector<float>& signal) override;

		//设置阈值参数
		void SetConfig(float threshold);

	private:
		//阈值参数
		float threshold;

	};





}