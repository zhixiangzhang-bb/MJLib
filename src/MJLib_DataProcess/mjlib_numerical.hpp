#pragma once


#include "mjlib_dataprocess_global.h"


namespace mjlib {

    namespace data {

        /**
         * @brief 计算数组的和
         * @tparam NUM 只接受数值类型
         * @param arr 输入数组
         * @return 返回数组和
         */
        template<typename NUM>
		MJLib_DataProcess_API inline double ArraySum(const std::vector<NUM>& arr) 
		{
            double sum = 0;
            for (auto& val : arr) {
                sum += val;
            }
            return sum;
        }

		/**
		 * @brief 查找数组最大值
		 * @param signal 输入数组
		 * @return 返回数组最大值
		 */
		inline double FindArrayMax(const std::vector<double>& signal)
		{
			if (signal.empty()) {
				return NAN; // 如果向量为空，返回非法
			}
			auto max_it = std::max_element(signal.begin(), signal.end());
			auto min_it = std::min_element(signal.begin(), signal.end());
			return *max_it;
		}

		/**
		 * @brief 查找数组最小值
		 * @param signal 输入数组
		 * @return 数组最小值
		 */
		inline double FindArrayMin(const std::vector<double>& signal)
		{
			if (signal.empty()) {
				return NAN; // 如果向量为空，返回非法
			}
			auto min_it = std::min_element(signal.begin(), signal.end());
			return *min_it;
		}


		/**
		 * @brief 生成固定间隔的数组
		 * @param size 数组大小
		 * @param start 启始数值
		 * @param interval 间隔数值
		 * @return 返回创建的数组
		 */
		inline std::vector<double> CreateIntervalArray(int32_t size, double start = 0, double interval = 1)
		{
			std::vector<double> arr(size);
			for (int i = 0; i < size; ++i) {
				arr[i] = start + i * interval;
			}
			return arr;
		}


		/**
		 * @brief 两点拟合方法
		 * @param x1 x1
		 * @param y1 y1
		 * @param x2 x2
		 * @param y2 y2
		 * @param x 需要拟合的x值
		 * @return 拟合的y值
		 */
		MJLib_DataProcess_API inline double TowFitting(double x1, double y1, double x2, double y2, double x)
		{
			auto k = (y2 - y1) / (x2 - x1);
			auto b = y1 - k * x1;
			return k * x + b;
		}


		/**
		 * @brief 通过最小二乘法拟合
		 * @param x x数据
		 * @param y y数据
		 * @param order 拟合阶数
		 * @return 每一阶的系数
		 */
		MJLib_DataProcess_API inline std::vector<double> polyfit(const std::vector<double>& x, const std::vector<double>& y, int order)
		{
			// 创建A矩阵
			Eigen::MatrixXd A(x.size(), order + 1);

			for (unsigned int i = 0; i < x.size(); ++i) {  // 遍历所有点

				for (int n = order, dex = 0; n >= 1; --n, ++dex) {  // 遍历N到1阶
					A(i, dex) = std::pow(x[i], n);
				}

				A(i, order) = 1;  //
			}

			// 创建B矩阵
			Eigen::MatrixXd B(y.size(), 1);

			for (unsigned int i = 0; i < y.size(); ++i) {
				B(i, 0) = y[i];
			}

			// 创建矩阵W
			Eigen::MatrixXd coe;
			coe = (A.transpose() * A).inverse() * A.transpose() * B;

			return std::vector<double>(coe.data(), coe.data() + coe.size());
		}






    }

}