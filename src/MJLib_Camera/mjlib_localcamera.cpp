
#include "mjlib_localcamera.h"


namespace mjlib {

    LocalCamera::LocalCamera()
    {

    }

    /**
     * @brief 设置相机ID
     * @param idx 相机ID
    */
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

    /**
     * @brief 获取连接状态
     * @return 返回连接状态
    */
    bool LocalCamera::isConnect()
    {
        return connectstate;
    }


    /**
     * @brief 获取采集状态
     * @return 返回是否正在采集
    */
    bool LocalCamera::isGrap()
    {
        return grapstate;
    }


    /**
     * @brief 获取相机参数
     * @return 返回相机参数
    */
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

    /**
     * @brief 设置FPS值
     * @param fps 需要设置的FPS值
     * @return 返回状态
    */
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


    /**
     * @brief 获取当前相机ID
     * @return 返回相机ID
    */
    int LocalCamera::GetCameraIdx()
    {
        return idx;
    }


    /**
     * @brief 获取FPS
     * @return 返回FPS数值
    */
    int LocalCamera::ReturnFps()
    {
        return fps;
    }


    /**
     * @brief 读取图片
     * @return 返回MAT格式图片
    */
    cv::Mat LocalCamera::ReadImage()
    {
        cv::Mat frame;
        cap >> frame;
        return frame;
    }
}


