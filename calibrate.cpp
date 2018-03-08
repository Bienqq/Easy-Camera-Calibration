#include "calibrate.h"

Calibrate::Calibrate()
{

}

Calibrate::~Calibrate()
{

}


cv::Size Calibrate::getDimensions()
{
    return dimensions;
}

void Calibrate::setHeight(int nHeight)
{
    dimensions.height = nHeight;
}

void Calibrate::setWidth(int nWidth)
{
    dimensions.width = nWidth;
}

QString Calibrate::getDistanceCoefficientsQString()
{
    std::vector<double> params;
    QString distCoeffs;
    uint16_t cols = distanceCoefficients.cols;
    uint16_t rows = distanceCoefficients.rows;
    for(int i = 0 ; i < rows ; i++)
    {
        for(int j = 0 ; j < cols ; j++)
        {
           params.push_back(distanceCoefficients.at<double>(i,j));
        }
    }
    for(std::vector<double>::iterator it = params.begin(); it != params.end(); it++)
    {
        distCoeffs.append( QString::number(*it,'f', 10) + " " );
    }
    return distCoeffs;
}

QString Calibrate::getCameraMatrixQString()
{
    std::vector<double> cameraParameters;
    uint16_t cols = cameraMatrix.cols;
    uint16_t rows = cameraMatrix.rows;
    for(int i = 0 ; i < rows ; i++)
    {
        for(int j = 0 ; j < cols ; j++)
        {
            cameraParameters.push_back(cameraMatrix.at<double>(i,j));
        }
    }
    QString stringCameraParameters;
    for(std::vector<double>::iterator it = cameraParameters.begin() ; it != cameraParameters.end() ; it++)
    {
        stringCameraParameters.append( QString::number(*it, 'f', 10) + " ") ;
    }
    return stringCameraParameters;
}

