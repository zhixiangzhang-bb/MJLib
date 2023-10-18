
#include "mjlib_svm_api.h"



/**
 * @brief 在堆上创建内存，对象周期由调用者管理
 * @return 返回一个模型指针
*/
extern "C"   uint32_t * CreateModel()
{
	try
	{
		zlib::SVM* svm = new zlib::SVM();
		return reinterpret_cast<uint32_t*>(svm);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}

}



/**
 * @brief 根据路径加载模型
 * @param modelin 模型指针输入
 * @param path 模型加载的路径
 * @return 0为运行失败，1为运行成功
*/
extern "C"   int LoadModel(uint32_t * modelin, const char* path)
{
	if (modelin != nullptr) {
		zlib::SVM* model = reinterpret_cast<zlib::SVM*>(modelin);
		return model->LoadModel(path);
	}
	else {
		return 0;
	}
}



/**
 * @brief 绑定数据指针，这种方式思路是共享内存，但是在labview中无法使用，这里只作为纯C接口使用
 * @param modelin 模型指针输入
 * @param input_data 输入数据指针
 * @param input_length 输入数据长度
 * @return 0为运行失败，1为运行成功
*/
extern "C"   int CreateData(uint32_t * modelin, float* input_data, int64_t input_length)
{
	if (modelin != nullptr) {
		zlib::SVM* model = reinterpret_cast<zlib::SVM*>(modelin);
		try
		{
			model->CreateData(input_data, input_length);
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
		return 1;
	}
	else {
		return 0;
	}
}



/**
 * @brief 运行模型
 * @param modelin 模型指针输入
 * @param input 输入数据指针
 * @param input_length 输入数据长度
 * @param output 
 * @return 0为运行失败，1为运行成功
*/
extern "C"   int RunModel(uint32_t * modelin,float* input,int64_t input_length,float* output)
{	
	auto model = reinterpret_cast<zlib::SVM*>(modelin);
	if (model->CreateData(input, input_length) == 1)
	{
		auto ary = model->ModelRun();
		if (!ary.empty()) {
			output[0] = std::move(ary[0]);
			output[1] = std::move(ary[1]);
			output[2] = std::move(ary[2]);
			output[3] = std::move(ary[3]);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}



/**
 * @brief 给调用者使用，用于释放模型内存，任务完成时必须释放资源，否则会导致内存泄漏
 * @param modelin 模型指针输入
 * @return 0为运行失败，1为运行成功
*/
extern "C"   int  DeleteModel(uint32_t* modelin)
{
	try
	{
		delete reinterpret_cast<zlib::SVM*>(modelin);
		return 1;
	}
	catch (const std::exception&)
	{
		return 0;
	}
}


/**
 * @brief 返回输入数组的大小，这里只考虑一维，也就是元素数量
 * @param modelin 模型指针输入
 * @return 返回数量
*/
extern "C"   int GetModelInputSize(uint32_t * modelin)
{
	return reinterpret_cast<zlib::SVM*>(modelin)->GetInputSize();
}




/**
 * @brief 返回输出数组的尺寸，常规清苦这里只考虑一维
 * @param modelin 模型指针输入
 * @return 返回数量
*/
extern "C"   int GetModelOutputSize(uint32_t * modelin)
{
	return reinterpret_cast<zlib::SVM*>(modelin)->GetOutputSize();
}




/**
 * @brief 返回输入节点数量
 * @param modelin 模型指针输入
 * @return 返回节点数量
*/
extern "C"   int GetModelInputCount(uint32_t * modelin)
{
	return reinterpret_cast<zlib::SVM*>(modelin)->GetInputCount();
}



/**
 * @brief 返回输出节点数量
 * @param modelin 模型指针输入
 * @return 返回节点数量
*/
extern "C"   int GetModelOutputCount(uint32_t * modelin)
{
	return reinterpret_cast<zlib::SVM*>(modelin)->GetOutputCount();
}