#include "copyprocessor.h"
#include <QDebug>
#include <QJsonDocument>

using namespace cv;
using namespace std;

CopyProcessor::CopyProcessor()
{

}

// wird vor dem ersten Videoframe aufgerufen
void CopyProcessor::startProcessing(const VideoFormat& format){
    filter = 3;
    hue = 104;
    sat = 80;
    val = 60;
    trsh = 10;
    calibrationValue = hue;
    calibration = false;
}

// wird für jedes Videoframe aufgerufen
Mat CopyProcessor::process(const Mat&source){
    Mat copyOfSource;
    source.copyTo(copyOfSource);

    if(calibration) {
        calibrationValue = calibrateHue(copyOfSource);
        calibration = false;
    }

    copyOfSource = processCurve(copyOfSource, hue, sat, val, trsh);

    return copyOfSource;
}

int CopyProcessor::calibrateHue(Mat input) {
    Mat output;
    cvtColor(input, output, CV_BGR2HSV);
    int maxHue = 0;
    int maxArea = 0;
    for(int i = 0;i<180;i++) { // 0..180
        int area = getArea(output, i);
        if(area >= maxArea) {
            maxArea = area;
            maxHue = i;
        }
    }
    hue = maxHue;
    return maxHue;
}

int CopyProcessor::getArea(Mat input, int hue) {
    inRange(input, Scalar(hue-5, 100, 0), Scalar(hue+5, 255, 255), input);

    // find all regions
    vector<vector<Point>> contours;
    findContours(input, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // find index of largest region
    int maxArea = 0;
    int maxAreaIndex = 0;
    for(int i = 0; i < contours.size(); i++){
        vector<Point> contour = contours[i];
        int area = contourArea(contour);
        if (maxArea < area){
            maxArea = area;
            maxAreaIndex = i;
        }
    }
    return maxAreaIndex;
}

Mat CopyProcessor::processCurve(Mat image, int hue, int saturation, int value, int threshold) {
    // Umwandung in HSV-Farbraum - cvtColor()
    Mat filterArray[4]; // to store diferent views
    Mat curve;
    cvtColor(image, curve, CV_BGR2HSV);

    // Umwandlung in 8-Bit-Werte: 0...360 -> 0...180
    int hueLowerThreshold = hue-threshold;
    int hueUpperThreshold = hue+threshold;
    int saturationThreshold = saturation;

    inRange(curve, Scalar(hueLowerThreshold, saturationThreshold, value), Scalar(hueUpperThreshold, 255, 255), curve);

    Mat colorFilter;
    curve.copyTo(colorFilter);

    // find all regions
    vector<vector<Point>> contours;
    findContours(curve, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // find index of largest region
    int maxArea = 0;
    int maxAreaIndex = 0;
    for(int i = 0; i < contours.size(); i++){
        vector<Point> contour = contours[i];
        int area = contourArea(contour);
        if (maxArea < area){
            maxArea = area;
            maxAreaIndex = i;
        }
    }
    //qDebug() << "maxArea: " << maxArea << "maxAreaIndex: " << maxAreaIndex;

    // fill smaller regions with black
    for (int i = 0; i < contours.size(); i++){
        if (i != maxAreaIndex){
            drawContours(curve, contours, i, Scalar(0,0,0,0), CV_FILLED);
        }
    }

    Mat regionFilter;
    curve.copyTo(regionFilter);

    if(maxArea > 2000) {

        // get bounding box
        int max_x = 0;
        int min_x = 255;
        int max_y = 0;
        int min_y = 255;
        for(int x = 0; x < curve.cols; x++){
            for(int y = 0; y < curve.rows; y++){
                if(curve.at<uchar>(y, x) > 0) {
                    if(x > max_x) max_x = x;
                    if(y > max_y) max_y = y;
                    if(x < min_x) min_x = x;
                    if(y < min_y) min_y = y;
                }
            }
        }

        //qDebug() << "max_x: " << max_x << " min_x: " << min_x << " max_y: " << max_y << " min_y: " << min_y;

        // remove frame
        // for(int x = min_x; x <= max_x; x++){
        //     for(int y = min_y; y <= max_y; y++){
        //         if(x < min_x+4 || x > max_x-4 || y < min_y+4 || y > max_y-4) {
        //             curve.at<uchar>(y, x) = 0;
        //         }
        //     }
        // }

        Mat frameFilter;
        curve.copyTo(frameFilter);


        if(getData) JSONData = {};


        int last_x = 0;
        int count_y = 0;
        int sum_y = 0;
        for(int x = min_x; x <= max_x; x++){
            for(int y = min_y; y <= max_y; y++){
                if(curve.at<uchar>(y, x) > 0) {
                    if(x > last_x) {
                        if(sum_y != 0 && count_y != 0){
                            //qDebug() << "sum: " << sum_y << "count: " << count_y << " new X: " << last_x << " new Y: " << int(sum_y / count_y);
                            curve.at<uchar>(int(sum_y / count_y), last_x) = 255;

                            int val_x = last_x;
                            int val_y = int(sum_y / count_y);

                            // ToDo: fill Array here
                            if(getData) {
                                //qDebug() << "X: " << val_x << " Y: " << val_y;
                                if(val_x != 0 && val_y != 0) JSONData.prepend(val_y);
                            }

                        }
                        last_x = x;
                        sum_y = 0;
                        count_y = 0;
                    }

                    sum_y = sum_y + y;
                    count_y++;
                    curve.at<uchar>(y, x) = 0;
                }
            }
        }

        if(getData) {
            QJsonDocument doc;
            doc.setArray(JSONData);
            QString dataToString(doc.toJson());
            //qDebug() << dataToString;
            getData = false;
        }

        Mat curveFilter;
        curve.copyTo(curveFilter);

        filterArray[2] = frameFilter;
        filterArray[3] = curveFilter;

    } else {
        Mat frameFilter;
        Mat curveFilter;
        filterArray[2] = frameFilter;
        filterArray[3] = curveFilter;
    }

    // ToDo: send to WebChannel


    filterArray[0] = colorFilter;
    filterArray[1] = regionFilter;


    return filterArray[filter];
}
