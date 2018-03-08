#ifndef CALIBRATE_H
#define CALIBRATE_H

#include "opencv2/highgui.hpp"
#include <QtXml>




class Calibrate
{

public:

    cv::Size getDimensions();
    void setWidth(int);
    void setHeight(int);
    QString getDistanceCoefficientsQString();
    QString getCameraMatrixQString();

    ~Calibrate();
    Calibrate();
    virtual double getElementDimension() = 0;
    virtual void setElementDimension(double) = 0;
    virtual bool foundAndDraw(cv::Mat&,cv::Mat&, bool) = 0;
    virtual bool cameraCalibration(std::vector<cv::Mat>&) = 0;

protected:
    cv::Size dimensions;
    std::vector<cv::Vec2f> foundPoints;
    std::vector<cv::Mat> rVectors, tVectors;
    cv::Mat distanceCoefficients = cv::Mat::zeros(8, 1, CV_64F);
    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat drawToFrame; //frame with chessboard pattern

};

#endif // CALIBRATE_H
