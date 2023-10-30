
#include "mjlib_localcamera.h"



LocalCamera::LocalCamera()
{

}


void LocalCamera::setidx(uint idx)
{
    this->idx = idx;
}



bool LocalCamera::open()
{
    cap.open(idx);
    if (cap.isOpened()) {
        connectstate = true;
        return 0;
    }
    else {
        return 1;
    }
}


bool LocalCamera::close()
{
    connectstate = false;

    //如果在采集先结束采集任务
    if (grapstate = true) {
        grapstate = false;
    }

    if (!cap.isOpened())
    {
        cap.release();
        return false;
    }
    else
    {
        return true;
    }
}


//开始采集
bool LocalCamera::startGrap()
{
    grapstate = true;
    return grapstate;
}


//停止采集
bool LocalCamera::stopGrap()
{
    grapstate = false;
    return 1;
}

//正在连接状态
bool LocalCamera::isConnect()
{
    return connectstate;
}


//正在采集状态
bool LocalCamera::isGrap()
{
    return grapstate;
}



ICamera::Message LocalCamera::gainmessage()
{
    cap.open(idx);
    if (cap.isOpened()) {
        Mess.idx = idx;
        Mess.ModelName = "本地相机" + std::to_string(idx);//型号用图片宽度代替
        Mess.ipAddr = std::to_string(cap.get(cv::CAP_PROP_FRAME_WIDTH));//型号用图片宽度代替
        Mess.MAC = std::to_string(cap.get(cv::CAP_PROP_FRAME_HEIGHT));//IP地址用图片高度代替
        Mess.SN = std::to_string(cap.get(cv::CAP_PROP_FPS));//MAC地址用分辨率代替
        cap.release();
    }
    return Mess;
}



uint LocalCamera::search()
{
    return 0;
}


void LocalCamera::MVSetDefaultParameters()
{

}



void LocalCamera::ReadIamge()
{
    cv::Mat image;
    cap.read(image);
}




bool LocalCamera::setFPS(uint fps)
{
    if (!cap.isOpened()) {
        open();
    }
    cap.set(cv::CAP_PROP_FPS, fps);
    double fpst = cap.get(cv::CAP_PROP_FPS);
    cap.release();
    if (fpst == fps) {
        return 0;
    }
    else {
        return 1;
    }
}


bool LocalCamera::CameraSetSheet()
{
    return 0;
}


//获取相机ID
int LocalCamera::GetCameraIdx()
{
    return idx;
}


//返回相机ID
int LocalCamera::ReturnFps()
{
    return fps;
}

