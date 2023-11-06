#pragma once

#include "mjlib_imageprocess.h"

namespace mjlib {



	/*****************************************************************
	* 类名称：Canny边缘检测
	* 功能描述：Canny边缘检测是一种经典的边缘检测算法，它具有良好的边缘定位和低误检率。它通过多阶段的边缘检测过程，包括高斯滤波、计算梯度幅值和方向、非极大值抑制和双阈值处理。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API Canny :public ImageProcess
	{

	public:
		Canny();

		cv::Mat processImage(const cv::Mat& image) override;

		//设置参数：第一个阈值，第二个阈值，算子的孔径大小
		void SetParam(double threshold1 = 100, double threshold2 = 200, int apertureSize = 3);

		//返回处理名称
		std::string ReturnName() override;

	private:
		// 第一个阈值
		double threshold1;

		// 第二个阈值
		double threshold2;

		// Sobel算子的孔径大小
		int apertureSize;


	};



	/*****************************************************************
	* 类名称：Sobel算子
	* 功能描述：Sobel算子是一种基于梯度的边缘检测算子，它通过计算图像的水平和垂直方向上的梯度来检测边缘。Sobel算子可以分别应用于灰度图像的水平和垂直方向，然后通过组合两个方向上的梯度得到最终的边缘图像。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API Sobel :public ImageProcess
	{

	public:
		Sobel();

		cv::Mat processImage(const cv::Mat& image) override;

		//设置参数：X方向上的差分阶数,Y方向上的差分阶数,Sobel算子的孔径大小,可选的比例因子,可选的增量值,边界填充类型
		void SetParam(int dx, int dy, int ksize, double scale = 1, double delta = 0, int borderType = 0);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//X方向上的差分阶数
		int dx;

		//Y方向上的差分阶数
		int dy;

		//Sobel算子的孔径大小
		int ksize;

		//可选的比例因子
		double scale;

		//可选的增量值
		double delta;

		//边界填充类型
		int borderType;


	};



	/*****************************************************************
	* 类名称：Scharr算子
	* 功能描述：Scharr算子是Sobel算子的改进版本，对于边缘检测来说具有更好的旋转不变性。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API Scharr :public ImageProcess
	{

	public:
		Scharr();

		cv::Mat processImage(const cv::Mat& image) override;

		//设置参数：X方向上的差分阶数,Y方向上的差分阶数
		void SetParam(int dx, int dy, double alpha = 0.5, double beta = 0.5);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//X方向上的差分阶数
		int dx;

		//Y方向上的差分阶数
		int dy;

		//第一张图片的权重系数
		double alpha;

		//第二张图片的权重系数
		double beta;


	};



	/*****************************************************************
	* 类名称：Laplacian算子
	* 功能描述：Laplacian算子是一种基于二阶导数的边缘检测算法，可以检测出图像中的高频变化
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API Laplacian :public ImageProcess
	{

	public:
		Laplacian();

		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;



	private:



	};




	/*****************************************************************
	* 类名称：Roberts算子
	* 功能描述：Roberts算子是一种基于两个2x2的模板进行卷积的边缘检测算法，它对噪声比较敏感，但计算速度较快。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API Roberts :public ImageProcess
	{

	public:
		Roberts();

		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;



	private:



	};


	/*****************************************************************
	* 类名称：SIFT（尺度不变特征变换）
	* 功能描述：SIFT是一种用于检测和描述图像中的稳定特征点的算法。它对图像的尺度、旋转和亮度变化具有很强的不变性。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API SIFT :public ImageProcess
	{
	public:
		//构造函数
		SIFT();

		//SIFT
		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;

	private:



	};




	/*****************************************************************
	* 类名称：SURF（加速稳健特征）
	* 功能描述：SURF是一种类似于SIFT的特征提取器，它使用快速算法来加速特征提取过程。SURF对尺度、旋转和亮度变化具有较好的不变性。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API SURF :public ImageProcess
	{
	public:
		//构造函数
		SURF();

		//SIFT
		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;

	private:



	};




	/*****************************************************************
	* 类名称：BRISK（Binary Robust Invariant Scalable Keypoints）
	* 功能描述：BRISK是一种基于二进制描述符的特征提取器，它结合了尺度不变特征和旋转不变特征。BRISK在保持较高性能的同时，具有较快的速度。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API BRISK :
		public ImageProcess
	{
	public:
		//构造函数
		BRISK();

		//SIFT
		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;

	private:



	};





	/*****************************************************************
	* 类名称：AKAZE（Accelerated-KAZE）
	* 功能描述：AKAZE是一种快速的特征提取器，它基于KAZE算法，并结合了加速算法来提高速度。AKAZE对于尺度、旋转和仿射变换具有较好的不变性。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/





	class MJLib_Vision_API AKAZE :public ImageProcess
	{
	public:
		//构造函数
		AKAZE();

		//SIFT
		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;


	private:



	};



}
