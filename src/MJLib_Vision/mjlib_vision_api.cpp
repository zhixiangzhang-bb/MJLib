#include "mjlib_vision_api.h"





/**
 * @brief 将labviw图片指针转换成MAT形式
 * @param LVImagePointer  labview图片指针
 * @param lineWidth 带边界的图片宽度
 * @param height 图片高度
 * @param width  图片宽度
 * @param channels 通道数（每个像素几个字节）
 * @return 返回MAT图片指针
*/
extern "C"  uint32_t* LVImagePointer2CVImage(unsigned char* LVImagePointer, int lineWidth, int height, int width, int channels)
{
	cv::Mat image;
	if (channels == 1) {
		image = cv::Mat(height, lineWidth, CV_8UC1, LVImagePointer);
	}
	else if (channels == 3) {
		image = cv::Mat(height, lineWidth, CV_8UC3, LVImagePointer);
	}
	else if (channels == 4) {
		image = cv::Mat(height, lineWidth, CV_8UC4, LVImagePointer);
		cvtColor(image, image, cv::COLOR_BGRA2RGB);
	}

	cv::Rect roi(0, 0, width, height);
	roi = roi & cv::Rect(0, 0, image.cols, image.rows);
	auto src= image(roi);
	return reinterpret_cast <uint32_t*>(&src);
}




/**
 * @brief 截取感兴趣的区域
 * @param image Mat图片指针
 * @param xStrt x轴开始位置
 * @param yStart y轴开始位置
 * @param xEnd x轴结束位置
 * @param yEnd Y轴结束位置
 * @return 返回MAT图片指针
*/
extern "C"  uint32_t * ImageRIO(uint32_t * image, int xStrt, int yStart, int xEnd, int yEnd)
{
	cv::Mat src=*reinterpret_cast <cv::Mat*>(image);
	mjlib::ImageROI* porcess= new mjlib::ImageROI(xStrt, xStrt, yStart, yEnd);
	auto img = porcess->processImage(src);
	auto img_out=reinterpret_cast <uint32_t*>(&src);
	delete porcess;
	return img_out;
}



/**
 * @brief 灰度化
 * @param image MAT图片指针
 * @return 返回MAT图片指针
*/
extern "C"   uint32_t * ImageGray(uint32_t * image)
{
	cv::Mat src = *reinterpret_cast <cv::Mat*>(image);
	mjlib::ImageGray* porcess = new mjlib::ImageGray();
	auto img = porcess->processImage(src);
	auto img_out = reinterpret_cast <uint32_t*>(&src);
	delete porcess;
	return img_out;
}