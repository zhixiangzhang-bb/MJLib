

#include "include/mjlib_dataprocess_api.h"
#include "mjlib_frequencydomain.h"
#include "mjlib_prob.h"
#include "mjlib_numerical.hpp"



extern "C" {

	/**
	 * @brief 计算离散度
	 * @param data 数组指针
	 * @param length 数组长度
	 * @return 离散度
	 */
	double COD(double* data, int32_t length)
	{
		std::vector<double> vec(data, data + length);
		return mjlib::data::CV(vec);
	}

	/**
	 * @brief 创建判断数据稳定性的对象
	 * @return 返回一个判断数据稳定性的对象指针
	 */
	int32_t* NewZmp()
	{
		return reinterpret_cast<int32_t*>(new mjlib::data::JudgedDataStability(20));
	}

	/**
	 * @brief 添加数据到判断数据稳定性的对象中
	 * @param point 对象指针
	 * @param data 输入数据
	 * @return 执行状态
	 */
	int32_t AddData(int32_t* point, double data)
	{
		if (point == nullptr) {
			return -1;
		}
		reinterpret_cast<mjlib::data::JudgedDataStability*>(point)->ReturnStability(data);
		return 1;
	}


	/**
	 * @brief 设置边界值
	 * @param point 对象指针
	 * @param border 边界值
	 * @return 执行状态
	 */
	int32_t SetBorder(int32_t* point, const double border)
	{
		if (point == nullptr) {
			return -1;
		}
		reinterpret_cast<mjlib::data::JudgedDataStability*>(point)->SetBorder(border);
		return 1;
	}

	/**
	 * @brief 设置窗口长度
	 * @param point 对象指针
	 * @param size 窗口长度
	 * @return 执行状态
	 */
	int32_t SetLength(int32_t* point, const double size)
	{
		if (point == nullptr) {
			return -1;
		}
		reinterpret_cast<mjlib::data::JudgedDataStability*>(point)->SetLength(size);
		return 1;
	}


	/**
	 * @brief 获取评分
	 * @param point 对象指针
	 * @return 
	 */
	double GetScore(int32_t* point)
	{
		return reinterpret_cast<mjlib::data::JudgedDataStability*>(point)->GetScore();
	}

	/**
	 * @brief 获取统计数据
	 * @param point 对象指针
	 * @param data 数据指针
	 * @return 执行状态
	 */
	int32_t GetStatisticData(int32_t* point, double* data)
	{
		if (point == nullptr) {
			return -1;
		}
		auto vec = reinterpret_cast<mjlib::data::JudgedDataStability*>(point)->GetStatisticData();

		for (size_t i = 0; i < 4; i++)
		{
			data[i]=vec[i];
		}
		
		return 1;
	}


	/**
	 * @brief 释放判断数据稳定性的对象
	 * @param point 对象指针
	 * @return 执行状态
	 */
	int32_t DeleteZmp(int32_t* point)
	{
		if (point == nullptr)
		{
			return -1;
		}
		auto zmp=reinterpret_cast<mjlib::data::JudgedDataStability*>(point);
		delete zmp;
		return 1;
	}

}

