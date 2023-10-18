#pragma once

#include "mjlib_cnn_macro.h"





namespace mjlib {



    class MJLib_CNN_API NeuralNetwork
    {
    public:

        NeuralNetwork();

        NeuralNetwork(int xStrt, int yStart, int xEnd, int yEnd);

        ~NeuralNetwork();

        //加载模型
        int LoadModel(const std::string& path);

        //模型预测
        std::vector<float> ModelPrediction(const cv::Mat& image);


    private:
        //神经网络模型资源
        cv::dnn::dnn4_v20221220::Net Net;

        int xStrt;

        int yStart;

        int xEnd;

        int yEnd;

    };






}
