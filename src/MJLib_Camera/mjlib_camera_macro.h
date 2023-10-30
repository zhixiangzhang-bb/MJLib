#pragma once


#include <opencv2/opencv.hpp>



#ifdef MJLib_Camera_EXPORTS
#define MJLib_Camera_API __declspec(dllexport)
#else
#define MJLib_Camera_API __declspec(dllimport)
#endif



/*****************************************************************
* 类名称：相机基类
* 功能描述：为所有相机的基类，给后续不同相机提供相同接口
* 作者：zzx
* 创建日期：2023.6.10
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



class MJLib_Camera_API ICamera
{

public:

    //相机状态枚举
    enum  CameraState {
        SUCCESS,//成功
        ERROR,//错误
        ERR_RESOURCE_IN_USE,//资源被占用 
        ACCESS_DENIED,//无法访问
        INVALID_ID,//ID错误
        FILE_IO//I/O错误
    };


    //相机信息结构体
    struct  Message {
        uint idx = -1;
        std::string ModelName;
        std::string ipAddr;
        std::string MAC;
        std::string SN;
    };


    //相机类型枚举
    enum  CameraType {
        No,
        Local_Camera,
        MV_Camera,
    };


    explicit ICamera(): idx(-1), fps(30) , connectstate(false), grapstate(false),Type(No){}

    Message Mess;

    virtual void setidx(uint idx) = 0;

    virtual uint search() = 0;

    virtual void MVSetDefaultParameters() = 0;

    virtual bool isConnect() = 0;

    virtual bool isGrap() = 0;

    virtual bool CameraSetSheet() = 0;

    virtual bool open() = 0;

    virtual bool close() = 0;

    virtual Message gainmessage() = 0;

    virtual bool startGrap() = 0;

    virtual bool stopGrap() = 0;

    virtual bool setFPS(uint fps) = 0;

    virtual int GetCameraIdx() = 0;

    virtual int ReturnFps() = 0;


protected:
    //相机ID
    uint idx;

    //相机类型
    CameraType Type;

    //相机连接状态
    bool connectstate;

    //相机采集状态
    bool grapstate;

    //相机fps
    int fps;



};

