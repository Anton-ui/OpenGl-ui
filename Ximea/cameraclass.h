#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <QDebug>
#include <QRunnable>
#include <memory>

#include <QGraphicsView>
#include "xiApi.h"
#include "xiApiPlusOcv.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core.hpp"

using namespace cv;

struct XimeaData
{
    int exposure = 10000;
    int gain = 8;
    int compression = 50;
};

class XimeaCamera
{

public:
    explicit XimeaCamera();
    void InitCamera(unsigned long in_cam_id = 0, unsigned long in_cam_num = 1);
    void ChangeGain(int gain_value);
    void ChangeCompression(int in_compression_value);
    void ChangeCompressionType(int in_compression_type);

    void ChangeImageType(XI_IMG_FORMAT img_format);
    void ChangeExposure(int exp_value);
    void SetDownsamplingPower(XI_DOWNSAMPLING_VALUE downsamling_power);
    Mat GetMatImage();
    QByteArray GetUcharImage();
    void Start();
    XI_SWITCH Status();
    void Stop();
    void Close();
    XimeaData controlData;
private:

    xiAPIplusCameraOcv cam;
    unsigned long cam_id;
    unsigned long cam_num;
    std::vector<uchar> buf;
    std::vector<int> params;
    int compression_type;
    int compression_value;
    void ChangeCompressionParams();

};

#endif // CAMERACLASS_H
