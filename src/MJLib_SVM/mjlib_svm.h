#pragma once

#include "mjlib_svm_macro.h"


namespace zlib {



	/*****************************************************************
	* 类名称：svm类
	* 功能描述：主要用于svm推理
	* 作者：zzx
	* 创建日期：2023.9.20
	* 最后修改：zzx
	* 最后修改日期：2023.9.20
	* 备注：
	******************************************************************/


	class MJLib_SVM_API SVM
	{
	public:

		SVM();


		~SVM();

		//创建模型
		int LoadModel(const std::string& path);

		//传递数据指针和输入参数
		int CreateData(float* input_data, int64_t length);

		//执行模型
		std::vector<float>  ModelRun();

		//返回输出数组大小
		int GetInputSize();

		//返回输出数组大小
		int GetOutputSize();

		//返回模型输入节点数量
		int GetInputCount();

		//返回模型输出节点数量
		int GetOutputCount();

	private:
		//模型加载器
		Ort::Session session;

		//onnx内存分配器
		Ort::AllocatorWithDefaultOptions allocator;

		//内存信息
		const Ort::MemoryInfo memory_info;

		//输入数据张量,SVM采用一维数据
		Ort::Value input_tensor;

		//节点输入名称数组
		std::vector<const char*> input_names;

		//节点输出名称数组
		std::vector<const char*> output_names;

		//输入数据尺寸
		int64_t inputdata_size;

		//输出数据尺寸
		int64_t outputdata_size;
	};


}

