#include "mjlib_cnn.h"



extern "C"
{


	/**
	 * @brief 创建模型资源
	 * @param cut 配置图像是否需要裁剪
	 * @return 返回模型指针
	*/
	uint32_t * CNN_CreateModel()
	{
		auto out = new mjlib::NeuralNetwork();
		return reinterpret_cast<uint32_t*>(out);

	}




	/**
	 * @brief 根据路径加载模型
	 * @param model 模型指针
	 * @param path 模型路径
	 * @return 成功返回1，失败返回0
	*/
	int CNN_LoadModel(uint32_t * model, const char* path)
	{
		auto net = reinterpret_cast<mjlib::NeuralNetwork*>(model);
		try
		{
			auto result = net->LoadModel(path);
			return result;
		}
		catch (const std::exception& e)
		{
			return 0;
		}
	}




	/**
	 * @brief 模型预测并获取结果
	 * @param model 模型指针
	 * @param image 图片指针
	 * @return 返回空化概率
	*/
	float CNN_ReasoningModel(uint32_t * model, uint32_t * image)
	{
		try
		{
			auto net = reinterpret_cast<mjlib::NeuralNetwork*>(model);
			auto a = net->ModelPrediction(*reinterpret_cast<cv::Mat*>(image));
			return a[0];
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}




	/**
	 * @brief 释放模型资源
	 * @param model 模型指针
	 * @return 成功返回1，失败返回0
	*/
	int CNN_DeleteModel(uint32_t * model)
	{
		delete reinterpret_cast<mjlib::NeuralNetwork*>(model);;
		return 1;
	}




}
