#ifndef COPYPROCESSOR_H
#define COPYPROCESSOR_H

#include "videoprocessor.h"
#include <QString>
#include <QJsonArray>

class CopyProcessor : public VideoProcessor
{
public:
    CopyProcessor();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    cv::Mat processCurve(cv::Mat image, int hue, int saturation, int value, int threshold);
    int calibrateHue(cv::Mat image);
    int getArea(cv::Mat input, int hue);
    QJsonArray JSONData;
    int hue, sat, val, trsh, filter, calibrationValue;
    bool calibration, getData;
};

#endif // COPYPROCESSOR_H
