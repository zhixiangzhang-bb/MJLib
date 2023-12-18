
#include "mjlib_prob.h"
#include <numeric>



namespace mjlib {

    namespace data {


        inline double ACFsum(std::vector<double>& data, int16_t nlags)
        {
            Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
            int n = arry.size();
            Eigen::VectorXf result(nlags + 1);
            float var = Var(data);
            for (int k = 0; k <= nlags; ++k) {
                result(k) = (arry.head(n - k).array() * arry.tail(n - k).array()).sum() / (n - k) / var;
            }

            // 求和
            float acfSum = result.sum();

            return acfSum;
        }



        inline double Mean(std::vector<double>& data)
        {
            Eigen::Map<Eigen::VectorXd> vec(data.data(), data.size());
            return vec.mean();
        }


        inline double RMS(std::vector<double>& data)
        {
            double sumOfSquares = 0.0;
            for (double value : data) {
                sumOfSquares += value * value;
            }
            return std::sqrt(sumOfSquares / data.size());
        }


        inline double Var(std::vector<double>& data)
        {
            if (data.empty()) {
                return 0;
            }
            else {
                Eigen::VectorXf arry = Eigen::Map<Eigen::VectorXd>(data.data(), data.size());
                double mean = arry.mean();
                return (arry.array() - mean).square().sum() / (arry.size());;
            }
        }

        //计算标准差
        inline double SD(std::vector<double>& data)
        {
            return std::sqrt(Var(data));
        }


        //计算信息熵
        inline double H(std::vector<double>& data)
        {
            std::map<float, int> counter;
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

      
        //计算峰峰值
        inline PP_Data* PP(std::vector<double>& data)
        {
            Eigen::VectorXd vec;
            EIGEN_MAP_VECTORXd(vec, data);
            PP_Data* result = new PP_Data;
            result->max = std::abs(vec.maxCoeff());
            result->min = std::abs(vec.minCoeff());
            return result;
        }

        //计算分位概率
        inline double Pth(std::vector<double>& data, const double& threshold)
        {
            int counts = data.size();
            Eigen::VectorXd arry = Eigen::Map<Eigen::VectorXd>(data.data(), data.size());
            int P43 = (arry.array().abs() > threshold).count();
            float Pth = static_cast<float>(P43) / counts;
            return Pth;
        }

        //计算偏度
        inline double Skewness(std::vector<double>& data)
        {
            Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
            return ((arry.array() - Mean(data)).pow(3).sum()) / (data.size() * std::pow(SD(data), 3));
        }

        //计算峰度
        inline double Kurtosis(std::vector<double>& data)
        {
            Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
            return ((arry.array() - Mean(data)).pow(4).sum()) / (data.size() * std::pow(SD(data), 4)) - 3.0;
        }

        //计算中位数
        inline double Median(std::vector<double>& data)
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


        inline double MAD(std::vector<double>& data)
        {
            Eigen::Map<Eigen::VectorXd> arry(data.data(), data.size());
            double median = Median(data);
            Eigen::VectorXd deviations = (arry.array() - median).abs();
            return deviations.mean();
        }


        inline std::vector<double> Z_Score(std::vector<double>& signal)
        {
            std::vector<double> zScores;
            double mean = Mean(signal);
            double standardDeviation = SD(signal);

            for (const auto& value : signal) {
                double zScore = (value - mean) / standardDeviation;
                zScores.push_back(zScore);
            }

        }

        //计算欧式距离
        inline double ED(std::vector<double>& data1, std::vector<double>& data2)
        {
            Eigen::Map <Eigen::VectorXd> arry1(data1.data(), data1.size());
            Eigen::Map <Eigen::VectorXd> arry2(data2.data(), data2.size());
            return (arry1 - arry2).norm();
        }

        //计算K距离
        double K_Distance(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
        {
            std::vector<double> distances;
            for (const auto& d : data) {
                distances.push_back(distance(d, point));
            }
            std::sort(distances.begin(), distances.end());
            return distances[k];
        }


        //计算k领域
        inline std::vector<int> K_Neighborhood(std::vector<std::vector<double>>& data, std::vector<double>& point, int k) {
            std::vector<std::pair<double, int>> distances;
            for (int i = 0; i < data.size(); ++i) {
                distances.push_back(std::make_pair(distance(data[i], point), i));  // 计算point与data中每个向量之间的距离，并将其与索引一起存储在distances向量中
            }
            std::sort(distances.begin(), distances.end());  // 对距离进行排序
            std::vector<int> neighborhood;
            for (int i = 0; i <= k; ++i) {
                neighborhood.push_back(distances[i].second);  // 将距离最近的k个向量的索引存储在neighborhood向量中
            }
            return neighborhood;  // 返回k领域内的所有点的索引
        }


        //计算局部可达密度
        inline double Local_Reachability_Density(std::vector<std::vector<double>>& data, std::vector<double>& point, int k) {
            auto k_distance = K_Distance(data, point, k);  // 计算point到数据集中第k近的点的距离
            auto neighborhood = K_Neighborhood(data, point, k);  // 确定point的k领域内的所有点的索引
            double sum = 0.0;
            for (const auto& n : neighborhood) {
                sum += K_Distance(data, data[n], k);  // 计算k领域内每个点到其第k近的点的距离，并求和
            }
            return (k + 1) * k_distance / sum;  // 返回局部可达密度
        }

        //计算局部异常因子
        inline double Local_Outlier_Factor(std::vector<std::vector<double>>& data, std::vector<double>& point, int k)
        {
            auto neighborhood = K_Neighborhood(data, point, k);  // 确定point的k领域内的所有点的索引
            double sum = 0.0;
            for (const auto& n : neighborhood) {
                sum += Local_Reachability_Density(data, data[n], k);  // 计算k领域内每个点的局部可达密度，并求和
            }
            return sum / neighborhood.size() / Local_Reachability_Density(data, point, k);  // 返回局部异常因子
        }


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

                Eigen::VectorXf arry = Eigen::Map<Eigen::VectorXd>(signal.data(), signal.size());
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
        double DataVar::ReturnDataProcessResult(std::vector<double>& signal)
        {
            if (signal.empty()) {
                return 0;
            }
            else {
                Eigen::VectorXf arry = Eigen::Map<Eigen::VectorXd>(signal.data(), signal.size());
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
            Eigen::VectorXf data = Eigen::Map<Eigen::VectorXd>(signal.data(), signal.size());
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



