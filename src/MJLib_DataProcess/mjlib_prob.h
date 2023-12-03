#pragma once



#include "mjlib_dataprocess_global.h"




namespace mjlib {


	namespace data {

		/**
		 * @brief 时域自相关系数
		 * @param signal 输入信号
		 * @param nlags 
		 * @return 返回
		*/
		inline double ACFsum(std::vector<double>& data, int16_t nlags);


		/**
		 * @brief 计算均值
		 * @param signal 输入信号
		 * @return 返回均值
		*/
		inline double Mean(std::vector<double>& data);

		/**
		 * @brief 计算均方根值	
		 * @param signal 输入信号
		 * @return 返回均方根值
		*/
		inline double RMS(std::vector<double>& data);

		/**
		 * @brief 计算方差
		 * @param signal 输入信号
		 * @return 返回方差值
		*/
		inline double Var(std::vector<double>& data);

		/**
		 * @brief 标准差：衡量一组数据分散程度的一个统计指标，表示数据集中的数值与平均数之间的偏差。
		 * @param signal 输入信号
		 * @return 返回标准差
		*/
		inline double SD(std::vector<double>& data);

		/**
		 * @brief 信息熵：量化信息的不确定性的一个度量。
		 * @param signal 输入信号
		 * @return 返回信息熵
		*/
		inline double H(std::vector<double>& data);

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
		inline PP_Data* PP(std::vector<double>& data);


		/**
		 * @brief 计算分位概率
		 * @param signal 输入信号
		 * @param threshold 分位阈值
		 * @return 返回分位概率值
		*/
		inline double Pth(std::vector<double>& data, const double& threshold);

		/**
		 * @brief 计算偏度
		 * @param data 输入数据
		 * @return 返回偏度值
		*/
		inline double Skewness(std::vector<double>& data);


		/**
		 * @brief 计算峰度 (1/N) * ∑(x_i - mean)^4 / σ^4 - 3
		 * @param data 输入数据
		 * @return 返回峰度值
		*/
		inline double Kurtosis(std::vector<double>& data);

		/**
		 * @brief 计算中位数
		 * @param data 输入数据
		 * @return 返回中位数
		*/
		inline double Median(std::vector<double>& data);


		/**
		 * @brief 通过计算每个数据点与数据集的中位数之间的绝对差异来计算MAD。这种方法可以帮助您找到可能存在的离群点，即与其他数据点相比差异很大的数据点。
		 MAD的值越高，表示数据集的离散程度越大，也就是说离群点的可能性也就越大
		 * @param data 输入数据
		 * @return 
		*/
		inline double MAD(std::vector<double>& data);

		/**
		 * @brief 对每个观测值计算其Z得分，将观测值减去均值并除以标准偏差,根据设定的阈值，判断Z得分是否超过阈值，如果超过则被标记为离群点。
		 * @param data 输入数据
		 * @return 返回Z得分数组
		*/
		inline std::vector<double> Z_Score(std::vector<double>& data);

		/**
		 * @brief 计算K距离，某一点p的k距离（k-distance），就是点p和距离点p第k近的点之间距离（不包括点p）
		 * @param data 输入数组
		 * @param queryPoint 待查询的点是你希望找到最近邻点的参考点
		 * @param k 表示要找出的最近邻点的数量
		 * @return 最近的 k 个点与待查询点的距离
		*/
		inline std::vector<double> K_Distance(std::vector<double>& data, double queryPoint, int k);

		/**
		 * @brief 计算两个向量之间的欧式距离，欧几里得距离是指在欧几里得空间中两个点之间的直线距离，计算公式 d = √((x2 - x1)² + (y2 - y1)²)
		 * @param data1 计算距离数组1
		 * @param data2 计算距离数组2
		 * @return 返回两数组之间的欧式距离
		*/
		inline double ED(std::vector<double>& data1, std::vector<double>& data2);

		/**
		 * @brief 计算k距离
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回第k近的距离
		*/
		inline double K_Distance(std::vector<std::vector<double>>& data, std::vector<double>& point, int k);


		/**
		 * @brief 计算k领域
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回k领域内的所有点的索引
		*/
		inline std::vector<int> K_Neighborhood(std::vector<std::vector<double>>& data, std::vector<double>& point, int k);


		/**
		 * @brief 计算局部可达密度
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回局部可达密度
		*/
		inline double Local_Reachability_Density(std::vector<std::vector<double>>& data, std::vector<double>& point, int k);


		/**
		 * @brief 计算局部异常因子
		 * @param data 数据集
		 * @param point 样本数据
		 * @param k 表示要找出的最近邻点的数量
		 * @return 返回局部异常因子
		*/
		inline double Local_Outlier_Factor(std::vector<std::vector<double>>& data, std::vector<double>& point, int k);


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


		template<typename Data>
		float Mean(const std::vector<float>& signal)
		{
			Eigen::Map vec(signal.data(), signal.size());
			return vec.mean();
		}



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