#include "mjlib_imagefileio.h"



namespace mjlib {

    /**
     * @brief 构造函数
     * @param parent 父类指针
    */
    ImageSaveVideo::ImageSaveVideo():
        SaveVideoState(false), 
        LoadVideoState(false), 
        frame_width(-1), 
        frame_height(-1)
    {

    }


    /**
     * @brief 析构函数
    */
    ImageSaveVideo::~ImageSaveVideo()
    {
        StopSaveVideo();
    }



    /**
     * @brief 设置视频参数
     * @param Path 保存路径
     * @param Vdostyle 视频类型
     * @param fps FPS
     * @param frame_width 图片宽度
     * @param frame_height 图片高度
    */
    void ImageSaveVideo::SetVideoParam(const std::string& Path, VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height)
    {
        this->frame_width = frame_width;
        this->frame_height = frame_height;
        switch (Vdostyle)
        {
        case ImageSaveVideo::MJPG:
            SaveVideoState = VideoIO.open(Path + ".avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
            break;
        case ImageSaveVideo::MP4V:
            SaveVideoState = VideoIO.open(Path + ".mp4", cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, cv::Size(frame_width, frame_height));
            break;
        case ImageSaveVideo::XVID:
            SaveVideoState = VideoIO.open(Path + ".avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, cv::Size(frame_width, frame_height));
            break;
        case ImageSaveVideo::H264:
            SaveVideoState = VideoIO.open(Path + ".mp4", cv::VideoWriter::fourcc('H', '2', '6', '5'), fps, cv::Size(frame_width, frame_height));
            break;
        default:
            break;
        }
    }


    /**
     * @brief 重写图像处理逻辑作为保存的过程
     * @param image 需要保存的图片流
     * @return 返回图片
    */
    cv::Mat ImageSaveVideo::processImage(const cv::Mat& image)
    {
        if (SaveVideoState) {
            cv::Mat proimage;
            cv::resize(image, proimage, cv::Size(frame_width, frame_height));
            VideoIO.write(proimage);
        }
        return image;
    }


    /**
     * @brief 停止录制视频
    */
    void ImageSaveVideo::StopSaveVideo()
    {
        VideoIO.release();
    }


    /**
     * @brief 加载视频
     * @param path 保存路径
    */
    void ImageSaveVideo::LoadVideo(std::string path)
    {
        cv::VideoCapture video(path);
        if (!video.isOpened()) {
            LoadVideoState = false;
            return;
        }
        else {
            LoadVideoState = true;
            double fps = video.get(cv::CAP_PROP_FPS);
            cv::Mat frame;
            while (true) {
                // 逐帧读取视频
                if (!video.read(frame)) {
                    video.release();
                    break;
                }
                //QImage img=ImageProcess::MatImageToQt(frame);
                //emit ReturnLoadVideo(img);

                cv::waitKey(1000 / fps);
            }
        }
    }




    /**
     * @brief 获取处理名称
     * @return 返回处理名称
    */
    std::string ImageSaveVideo::ReturnName()
    {
        return "保存视频";
    }



    /*

    图片采集逻辑

    */





    ImageSnapImage::ImageSnapImage(ImageProcess* parent) :num(0), autocu(false)
    {

    }



    //根据配置设置图片保存类型
    void ImageSnapImage::SetImageParam(const std::string& Path, ImageStyle Imgstyle, int frame_width, int  frame_height)
    {
        this->path = Path;
        this->frame_width = frame_width;
        this->frame_height = frame_height;
        switch (Imgstyle) {
        case JPEG:
            format = ".jpeg";
            break;
        case PNG:
            format = ".png";
            break;
        case BMP:
            format = ".bmp";
            break;
        case TIFF:
            format = ".tiff";
            break;
        default:
            break;
        }
    }



    //设置保存路径
    void ImageSnapImage::SetImagePath(std::string& Path)
    {
        this->path = Path;
    }



    //设置自动化采集
    void ImageSnapImage::SetAuto(bool autocu)
    {
        this->autocu = autocu;
        num = 0;
    }



    //执行一次写入一次
    cv::Mat ImageSnapImage::processImage(const cv::Mat& image)
    {
        cv::Mat proimage;
        std::string pathstr;
        if (autocu) {
            pathstr = path + std::to_string(num) + format;
            num++;
        }
        cv::resize(image, proimage, cv::Size(frame_width, frame_height));
        cv::imwrite(pathstr, image);
        return image;
    }


    //返回处理名称
    std::string ImageSnapImage::ReturnName()
    {
        return "采集图片";
    }




    /*
    打开图片逻辑分隔
    */





    OpenImageFile::OpenImageFile(ImageProcess* parent)
    {

    }



    cv::Mat OpenImageFile::OpenImage(std::string& Path)
    {
        cv::Mat image = cv::imread(cv::String(Path.begin(), Path.end()));
        if (!image.empty()) {
            cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
            return image;
        }
        else {
            return cv::Mat();
        }
    }


}