
#include "mjlib_prob.h"
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>


namespace mjlib {

    namespace data {


        /*****************************************************************
        * 类名称：判断数据平稳性
        * 功能描述：
        * 作者：zzx
        * 创建日期：2025.1.16
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/



        JudgedDataStability::JudgedDataStability():size(0), confidence_level(0.95), strategy(Weight)
            , statistic_data(std::vector<double>(4,0)),border(2),score(0),data(std::vector<double>())
        {
            cv::Ptr<cv::ml::RTrees> rf = cv::ml::RTrees::create();
            rf->setMaxDepth(10);
            rf->setMinSampleCount(2);
            rf->setMaxCategories(2);
            rf->setRegressionAccuracy(0.0);
            rf->setUseSurrogates(false);
        }


        JudgedDataStability::JudgedDataStability(int32_t size):size(size), confidence_level(0.95), strategy(Weight)
            , statistic_data(std::vector<double>(4, 0)), border(2), score(0), data(std::vector<double>())
        {

        }

        /**
         * @brief 设置长度
         * @param size 长度
         */
        void JudgedDataStability::SetLength(int32_t size)
        {
            this->size = size;
        }

        /**
         * @brief 设置边界
         * @param border 边界
         */
        void JudgedDataStability::SetBorder(double border)
        {
            this->border = border;
        }

        /**
         * @brief 输入数据到队列中
         * @param signal 输入数据
         * @return 评分
         */
        double JudgedDataStability::ReturnStability(double signal)
        {
            // 当数据的大小大于或等于指定大小时，移除最早的数据
            while (data.size() >= size) {
                data.erase(data.begin());
            }
            data.push_back(signal);
            Judge();
            return score;
        }

        /**
         * @brief 返回评分
         * @return 评分
         */
        double JudgedDataStability::GetScore()
        {
            return score;
        }

        /**
         * @brief 获取统计数据
         * @return 统计数据数组
         */
        std::vector<double> JudgedDataStability::GetStatisticData()
        {
            return statistic_data;
        }


        /**
         * @brief 
         * @param signal 
         * @return 
         */
        std::vector<double> JudgedDataStability::ReturnStability(std::vector<double>& signal)
        {
            std::vector<double> result;
            if (signal.size() <= 0) {
                return result;
            }
            auto midpoint = signal.size()/2;
            std::vector<double> left(signal.begin(), signal.begin() + midpoint);
            std::vector<double> right(signal.begin() + midpoint, signal.end());
            result.push_back(mjlib::data::Mean(signal));
            result.push_back(mjlib::data::Mean(left));
            result.push_back(mjlib::data::Mean(right));
            result.push_back(mjlib::data::Var(signal));
            result.push_back(mjlib::data::Var(left));
            result.push_back(mjlib::data::Var(right));
            result.push_back(mjlib::data::STDEV(signal));
            result.push_back(mjlib::data::polyfit(CreateIntervalArray(signal.size()), signal, 1)[0]);//按一次拟合取斜率
            return result;
        }

        /**
         * @brief 根据边界评估数据
         * @param data 输入数据
         * @param border 边界
         * @return 评估结果
         */
        double JudgedDataStability::Evaluation(double data, double border)
        {
            if (data == 0.0) {
                return 100;
            }
            return std::abs(data/border);
        }


        /**
         * @brief 稳定性判断
         */
        void JudgedDataStability::Judge()
        {
            if (data.size() <= 0) {
                return;
            }

            //计算数据相关性
            std::vector<double> result(4,0);
            result[0]=mjlib::data::CV(data);//计算相关系数
            result[1]=mjlib::data::Mean(data);///计算均值
            result[2]=mjlib::data::STDEV(data);//计算标准差
            //拟合曲线，取斜率
            result[3]=mjlib::data::polyfit(CreateIntervalArray(data.size()), data, 1)[0];

            //计算各参数差值变化
            auto cv = (result[0] - statistic_data[0]) / statistic_data[0];
            auto mean = (result[1] - statistic_data[1]) / statistic_data[1];
            auto stdev = (result[2] - statistic_data[2]) / statistic_data[2];
            auto slope = result[3];
            statistic_data = std::move(result);

            //根据策略计算评分
            double kds = 0;
            if (statistic_data[0] > border|| statistic_data[0] < 0) {
                kds = 0;
            }
            else {
                kds = mjlib::data::TowFitting(0, 100, border, 0, statistic_data[0]);
            }
    

            //将各参数差值变化加入队列
            while (score_data.size() >= 5) {
                score_data.erase(score_data.begin());
            }
            score_data.push_back(kds);

            //最后计算均值评分
            score = mjlib::data::Mean(score_data);


        }


        void JudgedDataStability::MaxStrategy()
        {
            
        }


        void JudgedDataStability::MinStrategy()
        {
            
        }


        void JudgedDataStability::MeanStrategy()
        {
            
        }


        /*****************************************************************
        * 类名称：时域自相关和
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.18
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/


        ACFsum::ACFsum() :nlags(1)
        {

        }


        ACFsum::ACFsum(int nlags) :nlags(nlags)
        {

        }


        double ACFsum::ReturnDataProcessResult(std::vector<double>& signal)
        {
            return data::ACFsum(signal, nlags);
        }


        void ACFsum::SetConfig(int nlags)
        {
            this->nlags = nlags;
        }




        /*****************************************************************
        * 类名称：均值
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.18
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/


        DataMean::DataMean()
        {

        }



        double DataMean::ReturnDataProcessResult(std::vector<double>& signal)
        {
            return data::Mean(signal);
        }



        /*****************************************************************
        * 类名称：队列均值
        * 功能描述：
        * 作者：zzx
        * 创建日期：2024.4.9
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/



        DataQueMean::DataQueMean()
        {

        }


        void DataQueMean::SetQueNum(int32_t num)
        {
            size = num;
        }


        double DataQueMean::ReturnDataProcessResult(std::vector<double>& signal)
        {
            //如果队列满了执行出队列
            if (que.size() >= size) {
                que.pop();
            }
            que.push(data::Mean(signal));
            std::queue<double> fu = que;//建立队列副本
            std::vector<double> data;
            for (size_t i = 0; i < fu.size(); i++)
            {
                data.push_back(fu.front());
                fu.pop();
            }
            return data::Mean(data);

        }




        /*****************************************************************
        * 类名称：均方根值
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.18
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/



 
        DataRMS::DataRMS()
        {

        }


    
        double DataRMS::ReturnDataProcessResult(std::vector<double>& signal)
        {
            return data::RMS(signal);
        }



        /*****************************************************************
        * 类名称：信息熵
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.18
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/





        DataH::DataH()
        {

        }



        /**
         * @brief 计算一组数信息熵
         * @param signal 输入信号数组
         * @return 返回信息熵
        */
        double DataH::ReturnDataProcessResult(std::vector<double>& signal)
        {
            
            return data::H(signal);
 
        }



        /*****************************************************************
        * 类名称：峰峰值
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.18
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/




        DataXpp::DataXpp()
        {

        }



        double DataXpp::ReturnDataProcessResult(std::vector<double>& signal)
        {
            Eigen::Map<Eigen::VectorXd> vec(signal.data(), signal.size());

            return std::max(std::abs(vec.maxCoeff()), std::abs(vec.minCoeff()));
        }




        /*****************************************************************
        * 类名称：均值峰峰值
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.25
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/




        DataXppm::DataXppm() : top_num(1), bottom_num(1)
        {

        }


        DataXppm::DataXppm(int top_num, int bottom_num) :top_num(top_num), bottom_num(bottom_num)
        {

        }


        /**
         * @brief 处理峰峰值结果
         * @param signal 输入数组
         * @return 返回0为失败
        */
        double DataXppm::ReturnDataProcessResult(std::vector<double>& signal)
        {

            if (signal.empty()) {
                return 0;
            }


            if (signal.size() > top_num && signal.size() > bottom_num) {

                Eigen::Map<Eigen::VectorXd> arry(signal.data(), signal.size());
                Eigen::VectorXd top = arry.topRows(top_num);
                Eigen::VectorXd bottom = arry.bottomRows(bottom_num);
                auto max = top.mean();
                auto min = bottom.mean();
                return std::max(top.mean(), -bottom.mean());
            }

        }



        /**
         * @brief 设置最大最小计算元素数量，大部分时间两个元素应该是相等的
         * @param top_num 最大元素数量
         * @param bottom_num 最小元素数量
        */
        void DataXppm::SetConfig(int top_num, int bottom_num)
        {
            this->top_num = top_num;
            this->bottom_num = bottom_num;
        }




        /*****************************************************************
        * 类名称：方差
        * 功能描述：计算一组数的方差
        * 作者：zzx
        * 创建日期：2023.9.25
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/




        DataVar::DataVar()
        {

        }



        /**
         * @brief 计算方差
         * @param signal 输入数组
         * @return 返回0为失败
        */
        double DataVar::ReturnDataProcessResult(std::vector<double>& signal)
        {
            if (signal.empty()) {
                return 0;
            }
            else {
                Eigen::VectorXd arry = Eigen::Map<Eigen::VectorXd>(signal.data(), signal.size());
                double mean = arry.mean();
                return (arry.array() - mean).square().sum() / (arry.size());;
            }
        }




        /*****************************************************************
        * 类名称：分位概率
        * 功能描述：
        * 作者：zzx
        * 创建日期：2023.9.25
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/



        DataPth::DataPth() :threshold(0)
        {

        }



        DataPth::DataPth(float threshold) :threshold(threshold)
        {

        }



        /**
         * @brief
         * @param signal
         * @return 返回0为失败
        */
        double DataPth::ReturnDataProcessResult(std::vector<double>& signal)
        {
            int counts = signal.size();
            Eigen::VectorXd data = Eigen::Map<Eigen::VectorXd>(signal.data(), signal.size());
            int P43 = (data.array().abs() > threshold).count();
            float Pth = static_cast<float>(P43) / counts;
            return Pth;
        }



        /**
         * @brief 设置阈值
         * @param threshold 阈值
        */
        void DataPth::SetConfig(float threshold)
        {
            this->threshold = threshold;
        }


    }

}



