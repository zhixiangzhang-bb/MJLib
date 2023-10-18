#include "mjlib_cnn.h"



namespace mjlib {

	NeuralNetwork::NeuralNetwork() :xStrt(900), yStart(400), xEnd(1600), yEnd(1200)
	{

	}


	NeuralNetwork::NeuralNetwork(int xStrt, int yStart, int xEnd, int yEnd):xStrt(xStrt), yStart(yStart), xEnd(xEnd), yEnd(yEnd)
	{

	}


	NeuralNetwork::~NeuralNetwork()
	{

	}



	//加载模型
	int NeuralNetwork::LoadModel(const std::string& path)
	{
		Net = cv::dnn::readNetFromTensorflow(path);
		if (Net.empty())
		{
			return 0;
		}
		else {
			//Net.enableWinograd(false);
			return 1;
		}
	}



	//预测
	std::vector<float> NeuralNetwork::ModelPrediction(const cv::Mat& image)
	{
		//归一化处理
		cv::Mat blob = cv::dnn::blobFromImage(image, 1. / 255, image.size());

		Net.setInput(blob);
		std::vector<float> out;
		out = Net.forward();
		return out;
	}



}