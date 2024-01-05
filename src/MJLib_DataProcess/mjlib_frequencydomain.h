#pragma once


#include "mjlib_dataprocess_global.h"
#include <unsupported/Eigen/FFT>






namespace mjlib {

	namespace data {

		template<typename T>
		MJLib_DataProcess_API inline std::vector<std::vector<T>> FFT(std::vector<T>& signal, int32_t sampleRate)
		{
			
			//傅里叶变换需要为双数，当为单数时进行补0操作
			int size = signal.size();
			if (size % 2 != 0) {
				signal.push_back(0);
				size = signal.size();
			}

			std::vector<std::vector<T>> out;
			if (signal.empty()) {
				return std::vector<std::vector<T>>();
			}

			Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>> vec(signal.data(), signal.size());


			size = signal.size(); // 信号长度
			Eigen::FFT<T> fft; // 创建FFT对象
			Eigen::VectorXcd  spectrum; // 存储频域信号数据的向量

			fft.fwd(spectrum, size);

			std::vector<std::vector<double>> result;
			result.push_back(std::vector<double>(spectrum.data(), spectrum.data()+spectrum.size()));
			result.push_back(std::vector<double>(amplitude.data(), amplitude.data()+amplitude.size()));

			return result;

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





