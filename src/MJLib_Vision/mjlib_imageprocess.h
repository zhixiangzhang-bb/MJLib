﻿#pragma once

#include "mjlib_vision_macro.h"




namespace mjlib {


	/*****************************************************************
	* 类名称：图像处理接口类
	* 功能描述：提供所有图像接口
	* 作者：zzx
	* 创建日期：2023.6.20
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：提供所有图像处理的接口
	******************************************************************/




	class  MJLib_Vision_API ImageProcess
	{

	public:
		ImageProcess() {};


		virtual cv::Mat processImage(const cv::Mat& image) = 0;


		virtual std::string ReturnName() = 0;


	protected:
		std::string name;



	};




	/*****************************************************************
	* 类名称：截取图像
	* 功能描述：通过x轴y轴范围定位
	* 作者：zzx
	* 创建日期：2023.9.22
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/


	class MJLib_Vision_API ImageROI :public ImageProcess
	{

	public:
		ImageROI();

		ImageROI(int xStrt, int yStart, int xEnd, int yEnd);

		cv::Mat processImage(const cv::Mat& image) override;

		std::string ReturnName() override;

		//设置参数
		void SetConfig(int xStrt, int yStart, int xEnd, int yEnd);

	private:
		int xStrt;

		int yStart;

		int xEnd;

		int yEnd;

	};





	/*****************************************************************
	* 类名称：灰度化
	* 功能描述：输入图像灰度化，返回灰度化图像
	* 作者：zzx
	* 创建日期：2023.7.20
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/





	class MJLib_Vision_API ImageGray :public ImageProcess
	{

	public:
		//构造函数
		explicit ImageGray();

		//灰度化重写处理流程
		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;



	};



	/*****************************************************************
	* 类名称：二值化
	* 功能描述：输入图像二值化
	* 作者：zzx
	* 创建日期：2023.7.20
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/





	class MJLib_Vision_API ImageBinaryzation :public ImageProcess
	{

	public:
		explicit ImageBinaryzation();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double thresholdValue, double max, int thresholdType);

		//返回处理名称
		std::string ReturnName() override;

	private:

		double thresholdValue;

		int thresholdType;

		double max;



	};


	/*****************************************************************
	* 类名称：均值模糊
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.7.23
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API ImageMeanFilter :
		public ImageProcess
	{
	public:
		explicit ImageMeanFilter();

		cv::Mat processImage(const cv::Mat& image) override;

		//设置参数：滤波器大小，描点位置，边界处理方式	
		void SetParam(int sizex, int sizey, int mdx, int mdy, int borderType);

		//返回处理名称
		std::string ReturnName() override;

	private:
		int sizex;

		int sizey;

		int mdx;

		int mdy;

		int borderType; // 边界处理方式	


	};




	/*****************************************************************
	* 类名称：高斯模糊
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.7.22
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API ImageGaussianFilter :
		public ImageProcess
	{
	public:
		explicit ImageGaussianFilter();

		cv::Mat processImage(const cv::Mat& image) override;

		void SetParam(int sizex, int sizey, double sigmaX, double sigmaY, int borderType);

		//返回处理名称
		std::string ReturnName() override;

	private:
		// 高斯核的大小
		int sizex;

		int sizey;

		// X方向的标准差
		double sigmaX;

		// Y方向的标准差（默认为0，表示与X方向的标准差相同）
		double sigmaY;

		// 边界模式
		int borderType;


	};



	/*****************************************************************
	* 类名称：中值滤波
	* 功能描述：使用图像中每个像素周围邻域内的中值来替代该像素的值，从而实现去除椒盐噪声或其他离群像素的效果
	* 作者：zzx
	* 创建日期：2023.7.22
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API ImageMedianFilter :
		public ImageProcess
	{
	public:
		explicit ImageMedianFilter();

		cv::Mat processImage(const cv::Mat& image) override;

		void SetParam(int ksize);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//领域大小
		int ksize;


	};



	/*****************************************************************
	* 类名称：双边滤波
	* 功能描述：在保持边缘清晰的同时，对图像进行平滑处理。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/




	class MJLib_Vision_API ImageBilateralFilter :
		public ImageProcess
	{
	public:
		explicit ImageBilateralFilter();

		cv::Mat processImage(const cv::Mat& image) override;

		void SetParam(int d, double sigmaColor, double sigmaSpace, int borderType);

		//返回处理名称
		std::string ReturnName() override;

	private:
		// 邻域直径
		int d;

		// 颜色相似性权重
		double sigmaColor;

		// 空间相似性权重
		double sigmaSpace;

		//模式
		int borderType;

	};



	/*****************************************************************
	* 类名称：亮度调节
	* 功能描述：根据亮度增益因子调节亮度
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API Bright :public ImageProcess
	{

	public:
		explicit Bright();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double alpha = 1.5);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//亮度增益
		double alpha;

		//


	};



	/*****************************************************************
	* 类名称：对比度调整
	* 功能描述：根据亮度增益因子调节亮度
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API Contrast :public ImageProcess
	{

	public:
		explicit Contrast();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double beta = 50);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//对比度增益因子
		double beta;


	};





	/*****************************************************************
	* 类名称：饱和度调整
	* 功能描述：根据亮度增益因子调节亮度
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API NTSC :public ImageProcess
	{

	public:
		explicit NTSC();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double alpha = 1.5);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//饱和度增益因子
		double alpha;


	};




	/*****************************************************************
	* 类名称：色温调整
	* 功能描述：根据亮度增益因子调节亮度
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API CCT :public ImageProcess
	{

	public:
		explicit CCT();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double temperature = 5000);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//色温值
		double temperature;


	};



	/*****************************************************************
	* 类名称：色阶调整
	* 功能描述：根据亮度增益因子调节亮度
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API Levels :public ImageProcess
	{

	public:
		explicit Levels();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double gamma = 1.5);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//色阶增益因子
		double gamma;


	};




	/*****************************************************************
	* 类名称：直方图均衡化
	* 功能描述：直方图均衡化是一种用于增强图像对比度的方法。它通过重新分布图像的像素值来扩展原始图像的动态范围，从而使图像的亮度分布更均匀。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API HistogramEqualization :public ImageProcess
	{

	public:
		explicit HistogramEqualization();

		cv::Mat processImage(const cv::Mat& image) override;

		//返回处理名称
		std::string ReturnName() override;

	private:



	};


	/*****************************************************************
	* 类名称：膨胀
	* 功能描述：通过将结构元素与图像进行卷积，将图像中的边界点逐渐扩张，使白色区域变大。膨胀操作可以用来填充小的黑色空洞或者连接两个相邻的物体。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API Expand :public ImageProcess
	{

	public:
		explicit Expand();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(int kernel = 3);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//卷积核
		int kernel;


	};



	/*****************************************************************
	* 类名称：腐蚀
	* 功能描述：通过将结构元素与图像进行卷积，将图像中的边界点逐渐侵蚀掉，使白色区域变小。腐蚀操作可以用来消除小的白色噪点或者分离两个相邻的物体。
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API Corrosion :public ImageProcess
	{

	public:
		explicit Corrosion();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(int kernel = 3);

		//返回处理名称
		std::string ReturnName() override;

	private:
		//卷积核大小
		int kernel;


	};




	/*****************************************************************
	* 类名称：频谱转换
	* 功能描述：转换成频域图片
	* 作者：zzx
	* 创建日期：2023.7.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	class MJLib_Vision_API SpectrumAnalysis :public ImageProcess
	{

	public:
		explicit SpectrumAnalysis();

		cv::Mat processImage(const cv::Mat& image) override;

		void setThreshold(double thresholdValue, int thresholdType);

		//返回处理名称
		std::string ReturnName() override;

	private:



	};


}