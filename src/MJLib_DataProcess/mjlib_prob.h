#pragma once



#include "mjlib_dataprocess_global.h"
#include <map>


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
			std::cout << data.size() << std::endl;
			Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>> array(data.data(), data.size());
			return array.mean();
		}


		/**
		 * @brief 计算均方根值	
		 * @param signal 输入信号
		 * @return 返回均方根值
		*/
		template<typename T>
		MJLib_DataProcess_API inline T RMS(std::vector<T>& data)
		{
			Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, 1>> array(data.data(), data.size());
			return std::sqrt(array.squaredNorm() / array.size());
		}


		/**
		 * @brief 计算方差
		 * @param signal 输入信号
		 * @return 返回方差值
		*/
		MJLib_DataProcess_API inline double Var(std::vector<double>& data)
		{
			if (data.empty()) {
				return 0;
			}
			else {
				Eigen::VectorXd arry = Eigen::Map<Eigen::VectorXd>(data.data(), data.size());
				double mean = arry.mean();
				return (arry.array() - mean).square().sum() / (arry.size());;
			}
		}


		/**
		 * @brief 标准差：衡量一组数据分散程度的一个统计指标，表示数据集中的数值与平均数之间的偏差。
		 * @param signal 输入信号
		 * @return 返回标准差
		*/
		MJLib_DataProcess_API inline double SD(std::vector<double>& data)
		{
			return std::sqrt(Var(data));
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
			return ((arry.array() - Mean(data)).pow(3).sum()) / (data.size() * std::pow(SD(data), 3));
		}


		/**
		 * @brief 计算峰度 (1/N) * ∑(x_i - mean)^4 / σ^4 - 3
		 * @param data 输入数据
		 * @return 返回峰度值
		*/
		MJLib_DataProcess_API inline double Kurtosis(std::vector<double>& data)
		{
			Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
			return ((arry.array() - Mean(data)).pow(4).sum()) / (data.size() * std::pow(SD(data), 4)) - 3.0;
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
		 * @brief 时域自相关系数
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
				result(k) = (arry.head(n - k).array() * arry.tail(n - k).array()).sum() / (n - k) / var;
			}

			// 求和
			double acfSum = result.sum();

			return acfSum;
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
		 * @brief 对每个观测值计算其Z得分，将观测值减去均值并除以标准偏差,根据设定的阈值，判断Z得分是否超过阈值，如果超过则被标记为离群点。
		 * @param data 输入数据
		 * @return 返回Z得分数组
		*/
		/*
		MJLib_DataProcess_API inline std::vector<double> Z_Score(std::vector<double>& data)
		{
			std::vector<double> zScores;
			double mean = Mean(data);
			double standardDeviation = SD(data);

			for (const auto& value : data) {
				double zScore = (value - mean) / standardDeviation;
				zScores.push_back(zScore);
			}

		}
		*/

		/**
		 * @brief 计算两个向量之间的欧式距离，欧几里得距离是指在欧几里得空间中两个点之间的直线距离，计算公式 d = √((x2 - x1)² + (y2 - y1)²)
		 * @param data1 计算距离数组1
		 * @param data2 计算距离数组2
		 * @return 返回两数组之间的欧式距离
		*/

		/*
		MJLib_DataProcess_API inline double ED(std::vector<double>& data1, std::vector<double>& data2)
		{
			Eigen::Map <Eigen::VectorXd> arry1(data1.data(), data1.size());
			Eigen::Map <Eigen::VectorXd> arry2(data2.data(), data2.size());
			return (arry1 - arry2).norm();
		}
		*/

		/**
		 * @brief 计算k距离
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回第k近的距离
		*/
		/*
		MJLib_DataProcess_API inline double K_Distance(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
		{
			std::vector<double> distances;
			for (const auto& d : data) {
				distances.push_back(distance(d, point));
			}
			std::sort(distances.begin(), distances.end());
			return distances[k];
		}
		*/


		/**
		 * @brief 计算k领域
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回k领域内的所有点的索引
		*/

		/*
		MJLib_DataProcess_API inline std::vector<int> K_Neighborhood(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
		{
			std::vector<std::pair<double, int>> distances;
			for (size_t i = 0; i < data.size(); ++i) {
				distances.push_back(std::make_pair(distance(data[i], point), i));  // 计算point与data中每个向量之间的距离，并将其与索引一起存储在distances向量中
			}
			std::sort(distances.begin(), distances.end());  // 对距离进行排序
			std::vector<int> neighborhood;
			for (int i = 0; i <= k; ++i) {
				neighborhood.push_back(distances[i].second);  // 将距离最近的k个向量的索引存储在neighborhood向量中
			}
			return neighborhood;  // 返回k领域内的所有点的索引
		}

		*/


		/**
		 * @brief 计算局部可达密度
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回局部可达密度
		*/
		/*
		MJLib_DataProcess_API inline double Local_Reachability_Density(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
		{
			auto k_distance = K_Distance(data, point, k);  // 计算point到数据集中第k近的点的距离
			auto neighborhood = K_Neighborhood(data, point, k);  // 确定point的k领域内的所有点的索引
			double sum = 0.0;
			for (const auto& n : neighborhood) {
				sum += K_Distance(data, data[n], k);  // 计算k领域内每个点到其第k近的点的距离，并求和
			}
			return (k + 1) * k_distance / sum;  // 返回局部可达密度
		}
		*/


		/**
		 * @brief 计算局部异常因子
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回局部异常因子
		*/

		/*
		MJLib_DataProcess_API inline double Local_Outlier_Factor(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
		{
			auto neighborhood = K_Neighborhood(data, point, k);  // 确定point的k领域内的所有点的索引
			double sum = 0.0;
			for (const auto& n : neighborhood) {
				sum += Local_Reachability_Density(data, data[n], k);  // 计算k领域内每个点的局部可达密度，并求和
			}
			return sum / neighborhood.size() / Local_Reachability_Density(data, point, k);  // 返回局部异常因子
		}
		*/
	}



	

	namespace dataclass {


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