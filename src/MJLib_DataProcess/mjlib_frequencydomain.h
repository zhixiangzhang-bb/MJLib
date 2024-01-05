#pragma once


#include "mjlib_dataprocess_global.h"
#include <unsupported/Eigen/FFT>
#include "mjlib_prob.h"





namespace mjlib {

	namespace data {


		
		MJLib_DataProcess_API inline std::vector<double> FFT(std::vector<double> signal, int32_t sampleRate)
		{
			
			//先判断是不是空数组
			if (signal.empty()) {
				return std::vector<double>();
			}


			int size = signal.size();//信号长度

			Eigen::Map< Eigen::Matrix<double, Eigen::Dynamic, 1>> vec(signal.data(), signal.size());
			Eigen::FFT<double> fft; // 创建FFT对象
			Eigen::VectorXcd fft_result;//复数数组
			fft.fwd(fft_result, vec);//快速傅里叶

			int32_t half_N = size / 2;//正频率分量
			Eigen::VectorXd magnitudes(size);//幅值数组
			Eigen::VectorXd phases(half_N);//相位数组

			std::vector<double> rms;

			//计算幅值
			for (size_t i = 0; i < fft_result.size(); i++)
			{				
				magnitudes(i) = (std::sqrt(std::pow(fft_result(i).real(), 2) + std::pow(fft_result(i).imag(), 2)))/RMS(signal);

			}

			std::vector<double> result(magnitudes.data(), magnitudes.data() + magnitudes.size());
			return result;


		}
		
		



		/**
		 * @brief 去除直流分量
		 * @tparam NUM 模版数据类型，只接受数值类型
		 * @param Data 输入数据
		 * @param Xmean 均值
		 * @return 返回去除直流分量后的数据
		*/
		template<typename NUM>
		MJLib_DataProcess_API inline std::vector<NUM> DeleteDC(std::vector<NUM> Data, NUM Xmean)
		{			
			
			Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, 1>> array(Data.data(), Data.size());//内存映射
			Eigen::VectorXd result = array.array() - Xmean;
			return std::vector<NUM>(result.data(), result.data() + result.size());

		}



		/**
		 * @brief 根据采样频率计算功率谱密度
		 * @param signal 输入数组
		 * @param sampleRate 采样频率
		 * @return 返回频率和功率谱密度数组
		*/
		MJLib_DataProcess_API inline std::vector<std::vector<double>>  PSD(std::vector<double>& signal, int sampleRate);


		//窗函数枚举
		enum windowtype {
			HanningWindow,//汉宁窗
			HammingWindow,//汉明窗
			BlackmanWindow
		};


		/**
		 * @brief 创建窗口函数
		 * @param length 窗口长度
		 * @param type 窗口类型
		 * @return 返回窗口数组
		*/
		MJLib_DataProcess_API inline std::vector<double> Window(int32_t length, windowtype type);


		/**
		 * @brief 加窗计算函数
		 * @param data 输入数组
		 * @param type 窗类型
		 * @return 返回加窗后的数组
		*/
		MJLib_DataProcess_API inline std::vector<double>  AddWindow(std::vector<double>& data, windowtype type);
		



	}


}





