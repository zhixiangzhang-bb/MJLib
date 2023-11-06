#ifndef IMAGEFILEIO_H
#define IMAGEFILEIO_H

#include "mjlib_imageprocess.h"
#include "mjlib_vision_macro.h"




namespace mjlib {

    /*****************************************************************
    * 类名称：视频保存类
    * 功能描述：将处理的视频写入文件
    * 作者：zzx
    * 创建日期：2023.7.8
    * 最后修改：zzx
    * 最后修改日期：
    * 备注：默认路径在程序主目录下，自定义目录需要先设置
    ******************************************************************/


    class   MJLib_Vision_API ImageSaveVideo : public ImageProcess
    {

    public:
        //视频编码格式枚举
        enum  VideoStyle {
            MJPG,
            MP4V,
            XVID,
            H264,
        };


        explicit ImageSaveVideo();

        /**
         * @brief 析构函数
        */
        ~ImageSaveVideo();

        /**
        * @brief 设置视频参数
        * @param Path 保存路径
        * @param Vdostyle 视频类型
        * @param fps FPS
        * @param frame_width 图片宽度
        * @param frame_height 图片高度
        */
        void SetVideoParam(const std::string& Path, VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height);


        /**
         * @brief 重写图像处理逻辑作为保存的过程
         * @param image 需要保存的图片流
         * @return 返回图片
        */
        cv::Mat processImage(const cv::Mat& image) override;


        /**
         * @brief 停止录制视频
        */
        void StopSaveVideo();


        /**
         * @brief 加载视频
         * @param path 保存路径
        */
        void LoadVideo(std::string path);


        /**
         * @brief 加载视频
         * @param path 保存路径
        */
        std::string ReturnName() override;

    private:
        int frame_width;

        int  frame_height;

        bool SaveVideoState;

        bool LoadVideoState;

        cv::VideoWriter VideoIO;



    };


    /*****************************************************************
    * 类名称：图片快照实现类
    * 功能描述：有两种模式：自动化采集和单次保存
    * 作者：zzx
    * 创建日期：2023.6.20
    * 最后修改：zzx
    * 最后修改日期：
    * 备注：
    ******************************************************************/



    class   MJLib_Vision_API ImageSnapImage : public ImageProcess
    {

    public:
        //图片格式枚举
        enum  ImageStyle {
            JPEG,//有损压缩格式，适用于存储照片和彩色图像
            PNG,//无损压缩格式，适用于存储图形和图标等带有透明背景的图像
            BMP, //无压缩格式，适用于存储位图图像
            TIFF,//支持多页和多通道的格式，适用于存储高质量的图像
        };



        explicit ImageSnapImage(ImageProcess* parent = nullptr);

        //保存图像
        cv::Mat processImage(const cv::Mat& image) override;


        void SetImageParam(const std::string& Path, ImageStyle Imgstyle, int frame_width, int  frame_height);

        //设置保存路径
        void SetImagePath(std::string& Path);

        //设置自动化采集
        void SetAuto(bool autocu);

        //返回处理名称
        std::string ReturnName() override;

    private:
        uint num;

        std::string path;

        std::string format;

        int frame_width;

        int  frame_height;

        bool autocu;


    };



    /*****************************************************************
    * 类名称：打开图片类
    * 功能描述：提供打开图片文件的接口
    * 作者：zzx
    * 创建日期：2023.7.17
    * 最后修改：zzx
    * 最后修改日期：
    * 备注：
    ******************************************************************/



    class   MJLib_Vision_API OpenImageFile
    {
    public:
        explicit OpenImageFile(ImageProcess* parent = nullptr);

        //根据路径打开图片
        cv::Mat OpenImage(std::string& Path);

    private:
        std::string path;


    };


}
#endif // IMAGEFILEIO_H
