

#include "MJLib_DataProcess/include/mjlib_dataprocess_api.h"
#include <vector>
#include <random>



int main()
{
    std::vector<double> data(20,100);
    std::vector<double> time={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    std::random_device rd;
    std::mt19937 gen(rd());  // 使用Mersenne Twister算法
    std::uniform_real_distribution<> dis(-0.5, 0.5);  // 生成范围在 -1 到 1 之间的随机数


    
    // 添加高斯噪声
    for (auto& x : data) {
        x = x + dis(gen);
    }
    
    auto result=mjlib::data::JudgedDataStability::ReturnStability(data);
    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << "The stability of data[" << i << "] is " << result[i] << std::endl;
    }


    
	return 0;
}



