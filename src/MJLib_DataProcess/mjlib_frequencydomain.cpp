
#include "mjlib_frequencydomain.h"



namespace mjlib {

	namespace data {



		/**
		 * @brief 根据采样频率计算功率谱密度
		 * @param signal 输入数组
		 * @param sampleRate 采样频率
		 * @return 返回频率和功率谱密度数组
		*/
		template<typename NUM>
		inline std::vector<std::vector<NUM>>  PSD(std::vector<double>& signal, int sampleRate)
		{

			//傅里叶变换需要为双数，当为单数时进行补0操作
			int size = signal.size();
			if (size % 2 != 0) {
				signal.push_back(0);
				size = signal.size();
			}

			std::vector<std::vector<double>> out;
			if (signal.empty()) {
				return std::vector<std::vector<double>>();
			}

			Eigen::Map<Eigen::VectorXd> vec(signal.data(), signal.size());

			size = signal.size(); // 信号长度
			Eigen::FFT<double> fft; // 创建FFT对象
			Eigen::VectorXcd  spectrum; // 存储频域信号数据的向量

			fft.fwd(spectrum, size);

			// 计算幅值平方得到功率谱密度，且只取前半部分
			Eigen::VectorXd amplitude = spectrum.array().abs2() / size; // 计算幅值平方得到功率谱密度

			// 计算器
			Eigen::VectorXd frequency = Eigen::VectorXd::LinSpaced(size, 0, sampleRate / 2);
			std::vector<double> freqVec(amplitude.data(), amplitude.data() + amplitude.size());
			std::vector<double> powerSpecVec(frequency.data(), frequency.data() + frequency.size());

			out.push_back(freqVec);
			out.push_back(powerSpecVec);
			return out;

		}




		/**
		 * @brief 生成汉宁窗数组
		 * @param length 窗长度
		 * @return 返回汉宁窗数组
		*/
		inline std::vector<double> Window(int32_t length, windowtype type)
		{
			std::vector<double> window(length);

			switch (type)
			{
			//汉宁窗生成
			case HanningWindow:
				for (int i = 0; i < length; ++i) {
					window[i] = 0.54 - 0.46 * std::cos(2 * PI * i / (length - 1));
				}
				break;

			//汉明窗生成
			case HammingWindow:
				for (int i = 0; i < length; ++i)
				{
					window[i] = 0.54 - 0.46 * std::cos(2 * PI * i / (length - 1));
				}
				break;

			case BlackmanWindow:
				for (int i = 0; i < length; ++i)
				{
					window[i] = 0.42 - 0.5 * std::cos(2 * PI * i / (length - 1)) + 0.08 * std::cos(4 * PI * i / (length - 1));
				}
				break;


			default:
				break;
			}

			return window;
		}


		/**
		 * @brief 加窗计算函数
		 * @param data 输入数组
		 * @param type 窗类型
		 * @return 返回加窗后的数组
		*/
		inline std::vector<double>  AddWindow(std::vector<double>& data, windowtype type)
		{
			if (data.empty()) {
				return std::vector<double>();
			}
			
			auto size = data.size();
			std::vector<double> result(size);
			auto win=Window(size, type);
			//内存映射
			Eigen::Map<Eigen::VectorXd> data1(result.data(), size);
			Eigen::Map<Eigen::VectorXd> result1(result.data(), size);
			Eigen::Map<Eigen::VectorXd> win1(win.data(), size);
			result1 = data1 * win1;//两个向量相乘得到结果
			return result;
		}



	}

}