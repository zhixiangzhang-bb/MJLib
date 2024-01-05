#pragma once



#include "mjlib_dataprocess_global.h"
#include "mjlib_numerical.hpp"
#include <map>
#include <queue>


namespace mjlib {


	namespace data {


	
		/**
		 * @brief 计算均值
		 * @tparam T m模版数据类型
		 * @param data 输入信号
		 * @return 返回均值
		*/
		template<typename T>
		MJLib_DataProcess_API inline T Mean(std::vector<T>& data)
		{
			Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>> array(data.data(), data.size());
			return array.mean();
		}


		/**
		 * @brief 计算均方根值	
		 * @param signal 输入信号
		 * @return 返回均方根值
		*/
		template<typename NUM>
		MJLib_DataProcess_API inline NUM RMS(std::vector<NUM>& data)
		{
			Eigen::Map<Eigen::Matrix<NUM, Eigen::Dynamic, 1>> array(data.data(), data.size());
			return std::sqrt(array.squaredNorm() / array.size());
		}



		/**
		 * @brief 计算方差
		 * @param signal 输入信号
		 * @return 返回方差值
		*/
		template<typename NUM>
		MJLib_DataProcess_API inline NUM Var(std::vector<NUM>& data)
		{
			if (data.empty()) {
				return 0;
			}
			else {
				Eigen::VectorX<NUM> arry = Eigen::Map<Eigen::VectorX<NUM>>(data.data(), data.size());
				double mean = arry.mean();
				return (arry.array() - mean).square().sum() / (arry.size());;
			}
		}


		/**
		 * @brief 标准差：衡量一组数据分散程度的一个统计指标，表示数据集中的数值与平均数之间的偏差。
		 * @param signal 输入信号
		 * @return 返回标准差
		*/
		MJLib_DataProcess_API inline double STDEV(std::vector<double>& data)
		{
			return std::sqrt(Var(data));
		}

		/**
		 * @brief 变异系数：衡量一组数据离散程度的一个统计指标，表示数据集中数值偏离平均数的程度。
		 * @param data 输入信号
		 * @return 离散系数
		 */
		MJLib_DataProcess_API inline double CV(std::vector<double>& data)
		{
			return STDEV(data) / Mean(data) * 100;
		}


		/**
		 * @brief 二次稳定度算法
		 * @param data 输入数据
		 * @param A1 一次阈值
		 * @param A2 二次阈值
		 * @param S1 一次概率阈值
		 * @param S2 二次概率阈值
		 * @return 稳定度
		 */
		MJLib_DataProcess_API inline double Ts(std::vector<double>& data, double A1, double A2, double S1, double S2)
		{
			//如果是空数据，返回NAN
			if (data.empty()) {
				return NAN;
			}

			//计算均值
			auto mean = Mean(data);
			auto a1max = mean + mean * A1;
			auto a1min = mean - mean * A1;

			const auto size = data.size();
			//一次稳定度判断
			double count = 0;
			for (size_t i = 0; i < size; i++)
			{
				if (data[i] >= a1min && data[i] <= a1max) {
					count+=1;
				}
			}
			double P1 = 100 * count / size;
			if (P1 < S1) {
				return 0;
			}

			//二次稳定度判断
			auto a2max = mean + mean * A2;
			auto a2min = mean - mean * A2;
			count = 0;
			for (size_t j = 0; j < size; j++)
			{
				if (data[j] >= a2min && data[j] <= a2max) {
					count += 1;
				}
			}
			double P2 = 100 * count / size;
			if (P2 < S1) {
				return 0;
			}
			return mjlib::data::TowFitting(S1, 0, S2, 100, P2);
		}


		/**
		 * @brief 信息熵：量化信息的不确定性的一个度量。
		 * @param signal 输入信号
		 * @return 返回信息熵
		*/
		MJLib_DataProcess_API inline double H(std::vector<double>& data)
		{
			std::map<double, int> counter;
			int size = data.size();

			// 统计每个元素的出现次数
			for (int i = 0; i < size; ++i) {
				if (counter.find(data[i]) != counter.end()) {
					counter[data[i]]++;// 如果元素已经在 map 中存在，则将其次数加1
				}
				else {
					counter[data[i]] = 1;// 否则将元素添加到 map 中，初始次数为1
				}
			}
			double entropy = 0.0;
			double acfsum = 0.0;


			// 计算每个元素的概率
			std::map<int, float> elementProbability;
			for (const auto& pair : counter) {
				float probability = static_cast<float>(pair.second) / size;
				elementProbability[pair.first] = probability;
				entropy = -(probability * log2(probability));
				acfsum += entropy;
			}


			return acfsum;
		}

		


		/**
		 * @brief 峰峰值结果
		*/
		struct PP_Data
		{
			double max;
			double min;

		};

		/**
		 * @brief 计算峰峰值
		 * @param signal 输入信号
		 * @return 返回峰峰值
		*/
		MJLib_DataProcess_API inline PP_Data* PP(std::vector<double>& data)
		{
			Eigen::Map<Eigen::VectorXd> vec(data.data(), data.size());
			PP_Data* result = new PP_Data;
			result->max = std::abs(vec.maxCoeff());
			result->min = std::abs(vec.minCoeff());
			return result;
		}

		/**
		 * @brief 计算分位概率
		 * @param signal 输入信号
		 * @param threshold 分位阈值
		 * @return 返回分位概率值
		*/
		MJLib_DataProcess_API inline double Pth(std::vector<double>& data, const double& threshold)
		{
			int counts = data.size();
			Eigen::VectorXd arry = Eigen::Map<Eigen::VectorXd>(data.data(), data.size());
			int P43 = (arry.array().abs() > threshold).count();
			float Pth = static_cast<float>(P43) / counts;
			return Pth;
		}


		/**
		 * @brief 计算偏度
		 * @param data 输入数据
		 * @return 返回偏度值
		*/
		MJLib_DataProcess_API inline double Skewness(std::vector<double>& data)
		{
			Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
			return ((arry.array() - Mean(data)).pow(3).sum()) / (data.size() * std::pow(STDEV(data), 3));
		}




		/**
		 * @brief 计算峰度 (1/N) * ∑(x_i - mean)^4 / σ^4 - 3
		 * @tparam NUM 只接受数值类型
		 * @param data 输入数据
		 * @return 返回峰度值
		*/
		template<typename NUM>
		MJLib_DataProcess_API inline NUM Kurtosis(std::vector<NUM>& data)
		{
			Eigen::Map<Eigen::VectorX<NUM>> arry(data.data(), data.size());
			return ((arry.array() - Mean(data)).pow(4).sum()) / (data.size() * std::pow(EFF(data), 4)) - 3.0;
		}


		/**
		 * @brief 计算中位数
		 * @param data 输入数据
		 * @return 返回中位数
		*/
		MJLib_DataProcess_API inline double Median(std::vector<double>& data)
		{
			Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
			std::sort(arry.data(), arry.data() + arry.size());
			double median;
			if (arry.size() % 2 == 0) {
				median = (arry(arry.size() / 2 - 1) + arry(arry.size() / 2)) / 2.0;
			}
			else {
				median = arry(arry.size() / 2);
			}
			return median;
		}



		/**
		 * @brief 时域自相关系数 可以描述一个信号在某一时刻与它在其他时刻的相似度
		 * @param signal 输入信号
		 * @param nlags
		 * @return 返回
		*/
		MJLib_DataProcess_API inline double ACFsum(std::vector<double>& data, int16_t nlags)
		{
			Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
			int n = arry.size();
			Eigen::VectorXd result(nlags + 1);
			auto var = Var(data);
			for (int k = 0; k <= nlags; ++k) {
				if (k == 0) {
					result(k) = 1.0;
				}
				else if (k == 1) {
					result(k) = (arry.head(n - 1).array() * arry.tail(n - 1).array()).sum() / (n - 1) / var;
				}
			}

			// 求和
			return result.sum();
		}


		/**
		 * @brief 通过计算每个数据点与数据集的中位数之间的绝对差异来计算MAD。这种方法可以帮助您找到可能存在的离群点，即与其他数据点相比差异很大的数据点。
		 MAD的值越高，表示数据集的离散程度越大，也就是说离群点的可能性也就越大
		 * @param data 输入数据
		 * @return 
		*/
		MJLib_DataProcess_API inline double MAD(std::vector<double>& data)
		{
			Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
			double median = Median(data);
			Eigen::VectorXd deviations = (arry.array() - median).abs();
			return deviations.mean();
		}

		
		/**
		 * @brief 计算标准偏差
		 * @tparam NUM 模版数据类型
		 * @param data 输入数据
		 * @return 返回标准偏差值
		*/
		template<typename NUM>
		MJLib_DataProcess_API inline NUM SD(std::vector<NUM>& data)
		{
			
			auto var = Var(data);
			return std::sqrt(var);
		}


		/*****************************************************************
		* 类名称：判断数据平稳性
		* 功能描述：
		* 作者：zzx
		* 创建日期：2025.1.16
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/
		

		class MJLib_DataProcess_API JudgedDataStability
		{
		public:
			enum StrategyType {
				Max,
				Min,
				Weight,
			};


			JudgedDataStability();


			JudgedDataStability(int32_t size);

			/**
			 * @brief 设置长度
			 * @param size 长度
			 */
			void SetLength(int32_t size);

			/**
			 * @brief 设置边界
			 * @param border 边界
			 */
			void SetBorder(double border);

			/**
			 * @brief 计算信号的稳定性
			 * @param signal 输入信号
			 * @return 返回稳定性值
			 */
			double ReturnStability(double signal);

			/**
			 * @brief 返回评分
			 * @return 评分
			 */
			double GetScore();

			/**
			 * @brief 获取统计数据
			 * @return 统计数据数组
			 */
			std::vector<double> GetStatisticData();


			/**
			 * @brief 计算信号的稳定性
			 * @param signal 输入信号
			 * @return 返回稳定性值
			 */
			static std::vector<double> ReturnStability(std::vector<double>& signal);


		private:

			/**
			 * @brief 时序数据队列
			 */
			std::vector<double> data;

			/**
			 * @brief 统计结果数组
			 */
			std::vector<double> statistic_data;

			/**
			 * @brief 评估数据数组
			 */
			std::vector<double> score_data;

			/**
			 * @brief 时序队列大小
			 */
			int32_t size;

			/**
			 * @brief 置信度水平
			 */
			double confidence_level;

			/**
			 * @brief 判断边界数据
			 */
			double border;

			/**
			 * @brief 预测策略
			 */
			StrategyType strategy;

			/**
			 * @brief 评分
			 */
			double score;

			/**
			 * @brief 稳定性判断
			 */
			void Judge();


			/**
			 * @brief 稳定后最大值策略
			 */
			void MaxStrategy();

			/**
			 * @brief 稳定后最小值策略
			 */
			void MinStrategy();

			/**
			 * @brief 稳定后均值策略
			 */
			void MeanStrategy();


			static double Evaluation(double data, double border);
		};

	


		/*****************************************************************
		* 类名称：时域自相关和
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.18
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/

		class MJLib_DataProcess_API ACFsum :public DataProcess
		{
		public:

			ACFsum();


			ACFsum(int nlags);

			double ReturnDataProcessResult(std::vector<double>& signal) override;


			void SetConfig(int nlags);

		private:
			int nlags;


		protected:

		};

		



		/*****************************************************************
		* 类名称：均值
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.18
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataMean :public DataProcess
		{
		public:
			DataMean();

			double ReturnDataProcessResult(std::vector<double>& signal) override;


		};



		/*****************************************************************
		* 类名称：队列均值
		* 功能描述：
		* 作者：zzx
		* 创建日期：2024.4.9
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataQueMean :public DataProcess
		{
		public:
			DataQueMean();

			void SetQueNum(int32_t num);

			double ReturnDataProcessResult(std::vector<double>& signal) override;
		

		private:
			std::queue<double> que;

			int32_t size;
		};




		/*****************************************************************
		* 类名称：均方根值
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.18
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataRMS :public DataProcess
		{
		public:
			DataRMS();

			double ReturnDataProcessResult(std::vector<double>& signal) override;


		};




		/*****************************************************************
		* 类名称：信息熵
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.18
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataH :public DataProcess
		{
		public:
			DataH();

			double ReturnDataProcessResult(std::vector<double>& signal) override;


		};



		/*****************************************************************
		* 类名称：峰峰值
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.18
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/


		class MJLib_DataProcess_API DataXpp :public DataProcess
		{
		public:
			DataXpp();

			double ReturnDataProcessResult(std::vector<double>& signal) override;


		};




		/*****************************************************************
		* 类名称：均值峰峰值
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.25
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/




		class MJLib_DataProcess_API DataXppm :public DataProcess
		{
		public:
			DataXppm();

			DataXppm(int top_num, int bottom_num);

			double ReturnDataProcessResult(std::vector<double>& signal) override;

			//设置最大最小参数
			void SetConfig(int top_num, int bottom_num);

		private:
			//最大的元素数量
			int top_num;

			//最小的元素数量
			int bottom_num;
		};




		/*****************************************************************
		* 类名称：方差
		* 功能描述：计算一组数的方差
		* 作者：zzx
		* 创建日期：2023.9.25
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataVar :public DataProcess
		{
		public:
			DataVar();

			double ReturnDataProcessResult(std::vector<double>& signal) override;


		};




		/*****************************************************************
		* 类名称：分位概率
		* 功能描述：
		* 作者：zzx
		* 创建日期：2023.9.25
		* 最后修改：zzx
		* 最后修改日期：
		* 备注：
		******************************************************************/



		class MJLib_DataProcess_API DataPth :public DataProcess
		{
		public:
			DataPth();

			DataPth(float threshold);

			double ReturnDataProcessResult(std::vector<double>& signal) override;

			//设置阈值参数
			void SetConfig(float threshold);

		private:
			//阈值参数
			float threshold;

		};







	}
	

}