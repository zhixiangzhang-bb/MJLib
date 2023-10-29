
#include "mjlib_frequencydomain.h"



namespace mjlib {



	/**
	 * @brief 根据采样频率计算功率谱密度
	 * @param signal 输入数组
	 * @param sampleRate 采样频率
<<<<<<<<< Temporary merge branch 1
	 * @return 返回频率和功率谱密度数组
	*/
	std::vector<std::vector<float>>  PSD(std::vector<float>& signal, int sampleRate)
	{
=========
	 * @return 返回频率和功率谱密度数组，可内联
	*/
	inline std::vector<std::vector<float>>  PSD(std::vector<float>& signal, int sampleRate)
	{			
		
		//傅里叶变换需要为双数，当为单数时进行补0操作
		int size=signal.size();	
		if (size % 2 != 0){
			signal.push_back(0);
			size = signal.size();
		}

		std::vector<std::vector<float>> out;
		if (signal.empty()) {
			return std::vector<std::vector<float>>();
		}

		Eigen::Map<Eigen::VectorXf> vec(signal.data(), signal.size());

		int size = signal.size(); // 信号长度
		Eigen::FFT<float> fft; // 创建FFT对象
		Eigen::VectorXcf  spectrum; // 存储频域信号数据的向量
		spectrum=fft.fwd(vec); // 进行傅里叶变换

		Eigen::VectorXf amplitude = spectrum.array().abs2() / size; // 计算幅值平方得到功率谱密度

=========
		Eigen::FFT<float> fft; // 创建FFT对象
		Eigen::VectorXcf  spectrum; // 存储频域信号数据的向量

		// 进行傅里叶变换，这里现在有点问
		fft.fwd(spectrum,vec);

		// 计算幅值平方得到功率谱密度，且只取前半部分
		Eigen::VectorXf amplitude = spectrum.array().abs2() / size; // 计算幅值平方得到功率谱密度

		// 计算器
		Eigen::VectorXf frequency = Eigen::VectorXf::LinSpaced(size, 0, sampleRate / 2);
		std::vector<float> freqVec(amplitude.data(), amplitude.data() + amplitude.size());
		std::vector<float> powerSpecVec(frequency.data(), frequency.data() + frequency.size());

<<<<<<<<< Temporary merge branch 1
=========

>>>>>>>>> Temporary merge branch 2
		out.push_back(freqVec);
		out.push_back(powerSpecVec);
		return out;

	}





	/*****************************************************************
	* 类名称：傅里叶变换
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.25
	* 最后修改：zzx
	* 最后修改日期：
	* 备注：
	******************************************************************/



	DataPsdMSF::DataPsdMSF():sampleRate(1)
	{


	}



	DataPsdMSF::DataPsdMSF(int sampleRate):sampleRate(sampleRate)
	{

	}
	


	/**
	 * @brief 进行傅里叶变换
	 * @param signal 输入信号数组
	 * @return 返回频率和幅值的二维数组，0为频率，1为幅值
	*/
	float DataPsdMSF::ReturnDataProcessResult(std::vector<float>& signal)
	{
		std::vector<std::vector<float>> out;
		if (signal.empty()) {
			return NAN;
		}
		else {
			auto psdarry = PSD(signal, sampleRate);
			Eigen::Map<Eigen::VectorXf> Psd(psdarry[0].data(), 52429);
			Eigen::Map<Eigen::VectorXf> f_psd(psdarry[1].data(), 52429);
			Psd = Psd.array().log10();//取10为底的对数

			float PsdSum = Psd.sum();

			Eigen::VectorXf f_psd2 = f_psd.array().square();//计算频率的平方
			auto dotProduct = f_psd2.dot(Psd);//计算频率和功率的点积
			auto PsdMSF = dotProduct / PsdSum;//点积除和得到均方
			return PsdMSF;

		}

	}




	/**
	 * @brief 设置采样频率
	 * @param sampleRate  频率
	*/
	void DataPsdMSF::SetConfig(int sampleRate)
	{
		this->sampleRate = sampleRate;
	}




}