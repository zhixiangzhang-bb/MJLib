#include "mjlib_filetxt.h"
#include <Windows.h>
#include <string>



namespace mjlib {


    std::vector<float> ReadTxtData2Float(const std::string& path, int startline)
	{

        HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        //打开失败返回空数组
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to open file." << std::endl;
            return std::vector<float>();
        }

        //获取文件大小失败返回空数组
        DWORD fileSizeHigh = 0;
        DWORD fileSizeLow = GetFileSize(hFile, &fileSizeHigh);
        if (fileSizeLow == INVALID_FILE_SIZE && GetLastError() != NO_ERROR) {
            std::cerr << "Failed to get file size." << std::endl;
            CloseHandle(hFile);
            return std::vector<float>();
        }


        //创建文件映射，失败则返回空数组
        HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        if (hFileMapping == NULL) {
            std::cerr << "Failed to create file mapping." << std::endl;
            CloseHandle(hFile);
            return std::vector<float>();
        }


        //将文件映射到内存，失败返回空数组并且关闭句柄
        char* fileData = reinterpret_cast<char*>(MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0));
        if (fileData == NULL) {
            std::cerr << "Failed to map file into memory." << std::endl;
            CloseHandle(hFileMapping);
            CloseHandle(hFile);
            return std::vector<float>();
        }


        //根据尺寸移位
        LONGLONG fileSize = static_cast<LONGLONG>(fileSizeHigh) << 32 | fileSizeLow;


        // 计算文件中行的起始位置
        int lineStart = 0;
        int lineCount = 1;
        for (int i = 0; i < fileSize; ++i) {
            if (fileData[i] == '\n') {
                if (++lineCount > startline) {
                    lineStart = i + 1;
                    break;
                }
            }
        }
        

        // 从设定开始解析每行内容为浮点数
        std::vector<float> numbers;
        char* lineEnd;
        float number;
        while (lineStart < fileSize) {
            number = strtof(fileData + lineStart, &lineEnd);
            if (lineStart == static_cast<int>(lineEnd - fileData))
                break;  // 行结束，不再有可以解析的浮点数

            numbers.push_back(number);

            lineStart = static_cast<int>(lineEnd - fileData);  // 更新下一行的起始位置
        }

        UnmapViewOfFile(fileData);
        CloseHandle(hFileMapping);
        CloseHandle(hFile);

        return numbers;

	}



    //template<typename T>
    std::vector<float> IntervalSampling(const std::vector<float>& input, int interval)
    {
        std::vector<float> sampledData;
        for (int i = 0; i < input.size(); i += interval)
        {
            sampledData.push_back(input[i]);
        }
        return sampledData;
    }


}