
#include "mjlib_timedomain.h"
#include <numeric>



namespace mjlib {


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



    float ACFsum::ReturnDataProcessResult(std::vector<float>& signal)
    {
        Eigen::Map<Eigen::VectorXf> data(signal.data(), signal.size());
      

        int n = data.size();
        Eigen::VectorXf result(nlags + 1);
        std::shared_ptr< DataVar> Var(new DataVar);
        float var= Var->ReturnDataProcessResult(signal);
        for (int k = 0; k <= nlags; ++k) {
            result(k) = (data.head(n - k).array() * data.tail(n - k).array()).sum() / (n - k) / var;
        }


        // 求和
        float acfSum = result.sum();

        return acfSum;
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



    float DataMean::ReturnDataProcessResult(std::vector<float>& signal)
    {
        Eigen::Map<Eigen::VectorXf> vec(signal.data(), signal.size());

        return vec.mean();
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



    float DataRMS::ReturnDataProcessResult(std::vector<float>& signal)
    {
        float sumOfSquares = 0.0;
        for (float value : signal) {
            sumOfSquares += value * value;
        }
        return std::sqrt(sumOfSquares / signal.size());
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
    float DataH::ReturnDataProcessResult(std::vector<float>& signal)
    {

        std::map<float, int> counter;
        int size = signal.size();

        // 统计每个元素的出现次数
        for (int i = 0; i < size; ++i) {
            if (counter.find(signal[i]) != counter.end()) {
                counter[signal[i]]++;// 如果元素已经在 map 中存在，则将其次数加1
            }
            else {
                counter[signal[i]] = 1;// 否则将元素添加到 map 中，初始次数为1
            }
        }
        double entropy = 0.0;
        float acfsum = 0.0;


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



    float DataXpp::ReturnDataProcessResult(std::vector<float>& signal)
    {
        Eigen::Map<Eigen::VectorXf> vec(signal.data(), signal.size());

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




    DataXppm::DataXppm(): top_num(1), bottom_num(1)
    {

    }


    DataXppm::DataXppm(int top_num, int bottom_num):top_num(top_num), bottom_num(bottom_num)
    {

    }


    /**
     * @brief 处理峰峰值结果
     * @param signal 输入数组
     * @return 返回0为失败
    */
    float DataXppm::ReturnDataProcessResult(std::vector<float>& signal)
    {
        
        if (signal.empty()) {
            return 0;
        }


        if(signal.size() > top_num && signal.size() > bottom_num){

            Eigen::VectorXf arry = Eigen::Map<Eigen::VectorXf>(signal.data(), signal.size());
            Eigen::VectorXf top = arry.topRows(top_num); 
            Eigen::VectorXf bottom = arry.bottomRows(bottom_num);
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
    float DataVar::ReturnDataProcessResult(std::vector<float>& signal)
    {
        if (signal.empty()) {
            return 0;
        }
        else {
            Eigen::VectorXf arry = Eigen::Map<Eigen::VectorXf>(signal.data(), signal.size());
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



    DataPth::DataPth():threshold(0)
    {

    }



    DataPth::DataPth(float threshold):threshold(threshold)
    {

    }



    /**
     * @brief 
     * @param signal 
     * @return 返回0为失败
    */
    float DataPth::ReturnDataProcessResult(std::vector<float>& signal)
    {
        int counts = signal.size();
        Eigen::VectorXf data = Eigen::Map<Eigen::VectorXf>(signal.data(), signal.size());
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



