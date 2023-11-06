#include "mjlib_edgedetection.h"
#include <opencv2/xfeatures2d.hpp>

namespace mjlib {


	Canny::Canny() :threshold1(100), threshold2(200), apertureSize(3)
	{

	}



	cv::Mat Canny::processImage(const cv::Mat& image)
	{
		cv::Mat edges;
		cv::Canny(image, edges, threshold1, threshold2, apertureSize);
		return edges;
	}




	void Canny::SetParam(double threshold1, double threshold2, int apertureSize)
	{
		this->threshold1 = threshold1;
		this->threshold2 = threshold2;
		this->apertureSize = apertureSize;

	}


	//返回处理名称
	std::string Canny::ReturnName()
	{
		return "Canny算子边缘检测";
	}




	/*

	逻辑分隔：Sobel算子

	*/





	Sobel::Sobel() :dx(1), dy(1), ksize(1), scale(1), delta(0), borderType(0)
	{

	}



	cv::Mat Sobel::processImage(const cv::Mat& image)
	{
		if (image.channels() == 1) {
			// 应用Sobel算子进行边缘检测
			cv::Mat sobelX, sobelY;
			cv::Sobel(image, sobelX, CV_16S, dx, 0, ksize, scale, delta, borderType); // 在X方向上计算梯度
			cv::Sobel(image, sobelY, CV_16S, 0, dy, ksize, scale, delta, borderType); // 在Y方向上计算梯度

			// 转换为灰度图像
			cv::Mat sobelXAbs, sobelYAbs;
			cv::convertScaleAbs(sobelX, sobelXAbs);
			cv::convertScaleAbs(sobelY, sobelYAbs);

			// 合并X和Y方向的梯度
			cv::Mat sobel;
			cv::addWeighted(sobelXAbs, 0.5, sobelYAbs, 0.5, 0, sobel);
			return sobel;
		}
		else {
			//不是灰度图像返回原图像
			return image;
		}
	}




	void Sobel::SetParam(int dx, int dy, int ksize, double scale, double delta, int borderType)
	{
		this->dx = dx;
		this->dy = dy;
		this->ksize = ksize;
		this->scale = scale;
		this->delta = delta;
		this->borderType = borderType;
	}


	//返回处理名称
	std::string Sobel::ReturnName()
	{
		return "Sobel算子边缘检测";
	}



	/*

	逻辑分隔：Scharr算子

	*/





	Scharr::Scharr() :dx(1), dy(1), alpha(0.5), beta(0.5)
	{

	}



	cv::Mat Scharr::processImage(const cv::Mat& image)
	{
		if (image.channels() == 1) {
			// 应用Scharr算子进行边缘检测
			cv::Mat gradient_x, gradient_y;
			cv::Scharr(image, gradient_x, CV_16S, dx, 0);  // 在x方向上计算梯度
			cv::Scharr(image, gradient_y, CV_16S, 0, dy);  // 在y方向上计算梯度

			// 转换为灰度图像
			cv::Mat sobelXAbs, sobelYAbs;
			cv::convertScaleAbs(gradient_x, sobelXAbs);
			cv::convertScaleAbs(gradient_y, sobelYAbs);

			// 合并梯度结果
			cv::Mat gradient;
			cv::addWeighted(sobelXAbs, alpha, sobelYAbs, beta, 0, gradient);

			return gradient;
		}
		else {
			return image;
		}

	}




	void Scharr::SetParam(int dx, int dy, double alpha, double beta)
	{
		this->dx = dx;
		this->dy = dy;
		this->alpha = alpha;
		this->beta = beta;
	}

	//返回处理名称
	std::string Scharr::ReturnName()
	{
		return "Scharr算子边缘检测";
	}



	/*


	逻辑分隔：Laplacian算子


	*/





	Laplacian::Laplacian()
	{

	}



	cv::Mat Laplacian::processImage(const cv::Mat& image)
	{
		if (image.channels() == 1) {
			// 应用Laplacian边缘检测
			cv::Mat edges;
			cv::Laplacian(image, edges, CV_8U);

			return edges;
		}
		else {
			return image;
		}

	}


	//返回处理名称
	std::string Laplacian::ReturnName()
	{
		return "Laplactian算子边缘检测";
	}


	/*


	逻辑分隔：Roberts算子


	*/





	Roberts::Roberts()
	{

	}



	cv::Mat Roberts::processImage(const cv::Mat& image)
	{
		if (image.channels() == 1) {
			// 创建输出图像
			cv::Mat edges;

			// Roberts算子边缘检测
			cv::Mat robertsX, robertsY;
			cv::Mat kernelX = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
			cv::Mat kernelY = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);
			cv::filter2D(image, robertsX, -1, kernelX);
			cv::filter2D(image, robertsY, -1, kernelY);
			cv::magnitude(robertsX, robertsY, edges);
			return edges;
		}
		else {
			return image;
		}

	}


	//返回处理名称
	std::string Roberts::ReturnName()
	{
		return "Robert算子边缘检测";
	}


	SIFT::SIFT()
	{

	}


	cv::Mat SIFT::processImage(const cv::Mat& image)
	{
		// 创建SIFT对象
		cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

		// 检测关键点并计算描述符
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		sift->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

		// 在图像上绘制关键点
		cv::Mat outputImage;
		cv::drawKeypoints(image, keypoints, outputImage);

		return outputImage;
	}


	//返回处理名称
	std::string SIFT::ReturnName()
	{
		return "SIFT特征查找";
	}





	/*






	*/




	SURF::SURF()
	{

	}


	cv::Mat SURF::processImage(const cv::Mat& image)
	{
		
		// 创建SURF对象
		cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create();

		// 检测关键点和计算描述符
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		surf->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

		// 在图像上绘制关键点
		cv::Mat image_with_keypoints;
		cv::drawKeypoints(image, keypoints, image_with_keypoints);

		return image_with_keypoints;

	}

	//返回处理名称
	std::string SURF::ReturnName()
	{
		return "SURF特征查找";
	}


	/*






	*/



	BRISK::BRISK()
	{

	}


	cv::Mat BRISK::processImage(const cv::Mat& image)
	{
		// 创建SURF对象
		cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create();

		// 检测关键点和计算描述符
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		surf->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

		// 在图像上绘制关键点
		cv::Mat image_with_keypoints;
		cv::drawKeypoints(image, keypoints, image_with_keypoints);

		return image_with_keypoints;
	
	}


	//返回处理名称
	std::string BRISK::ReturnName()
	{
		return "BRISK特征查找";
	}




	/*






	*/



	AKAZE::AKAZE()
	{

	}


	cv::Mat AKAZE::processImage(const cv::Mat& image)
	{
		// 创建AKAZE特征提取器对象
		cv::Ptr<cv::AKAZE> akaze = cv::AKAZE::create();

		// 检测和描述图像中的特征点
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		akaze->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

		// 在图像上绘制特征点
		cv::Mat image_with_keypoints;
		cv::drawKeypoints(image, keypoints, image_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		return image_with_keypoints;
	}


	//返回处理名称
	std::string AKAZE::ReturnName()
	{
		return "AKAZE特征查找";
	}



}