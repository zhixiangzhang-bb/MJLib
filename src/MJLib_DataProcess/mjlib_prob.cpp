
#include "mjlib_prob.h"
#include <numeric>



namespace mjlib {

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



