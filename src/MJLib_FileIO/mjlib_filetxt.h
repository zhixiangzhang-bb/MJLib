

#pragma once



#include "mjlib_fileio_macro.h"
#include <vector>







namespace mjlib {

	/**
	 * @brief 读取txt文件并转换
	 * @param path 文本路径
	 * @param line 从第几行开始读取
	 * @return 返回浮点数组
	*/
	MJLib_FileIO_API std::vector<float> ReadTxtData2Float(const std::string& path,int line);


	
	MJLib_FileIO_API std::vector<float> IntervalSampling(const std::vector<float>& input, int interval);
}


