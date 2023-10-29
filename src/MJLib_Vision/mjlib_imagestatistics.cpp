
#include "mjlib_imagestatistics.h"




/**
 * @brief 统计灰度级
 * @param image opencv图像类型
 * @return X为像素 Y为灰度数量
*/
std::tuple<std::vector<double>, std::vector<double>> Statistics(const cv::Mat& image)
{
    cv::Mat gray;
    if (image.channels() == 1) {
        gray = image;
    }
    else {
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    }
    int histSize = 256;  // 直方图的大小
    float range[] = { 0, 256 };  // 像素值范围
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    cv::Mat hist;
    cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    std::vector<double> xData(histSize), yData(histSize);
    for (int i = 0; i < histSize; ++i) {
        xData[i] = i;
        yData[i] = hist.at<float>(i);
    }
    //std::vector<std::vector<double>> result;
    //result.push_back(std::move(xData));
    //result.push_back(std::move(yData));
    return std::make_tuple(xData, yData);
}






