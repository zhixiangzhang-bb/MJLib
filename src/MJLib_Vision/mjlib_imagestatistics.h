#pragma once

#include "mjlib_vision_macro.h"




//统计直方图信息
std::tuple<std::vector<double>, std::vector<double>> Statistics(const cv::Mat& image);