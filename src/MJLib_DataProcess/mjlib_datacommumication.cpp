#include "DataCommumication.h"



DataCommumication::DataCommumication(QObject *parent)
	: QObject(parent), DatIf(new DataInterface)
{   

}


DataCommumication::~DataCommumication()
{

}


//执行ping命令
bool DataCommumication::Ping(const char* ipAddress)
{
    // 构建ping命令
    std::string pingCommand = "ping -c 4 " + std::string(ipAddress);

    // 执行ping命令
    return  system(pingCommand.c_str());
}


//返回UI界面
DataInterface* DataCommumication::ReturnUI()
{
    return DatIf.get();
}



//写入数据接口
void DataCommumication::WirteDataPort()
{

}


//返回选择的数据指针
std::string* DataCommumication::ReturnDataSting()
{
    return DatIf->ReturnDataStr();
}
