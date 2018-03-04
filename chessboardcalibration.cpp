#include "chessboardcalibration.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include <QDebug>


ChessboardCalibration::ChessboardCalibration()
    :Calibrate()
{


}


bool ChessboardCalibration::foundAndDraw(cv::Mat& frame, cv::Mat& outputFrame)
{

    found = cv::findChessboardCorners(frame, dimensions, foundPoints, CV_CALIB_CB_FAST_CHECK |CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE );
    drawChessboardCorners(frame, dimensions, foundPoints, found); // drawing corners
    qDebug()<<"found:"<<found;
    if (found)
    {
        cv::putText(frame,"Chessboard was found", cv::Point2i(20,40), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0x00, 0xff, 0x00), 3);
        outputFrame = frame;
        return true;
    }
    else
    {
        cv::putText(frame, "No chessboard found", cv::Point2i(20,40), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0x00, 0x00, 0xff), 3);
        outputFrame = frame ;
        return false;
    }
}

void ChessboardCalibration::getChessboardCorners(std::vector<cv::Mat>& images,  std::vector<std::vector<cv::Point2f>>& allFoundCorners)
{
    bool ok = false;
    qDebug()<<"Capacity:"<<images.capacity();
    for (std::vector<cv::Mat>::iterator iter = images.begin(); iter != images.end(); iter++)
    {
        std::vector<cv::Point2f> pointBuf;
        //iter->convertTo(*iter, CV_8UC3);
        qDebug()<<"iter->empty()"<<iter->empty();


        qDebug()<<"wykonanie funkcji findChessboardCorners"<<cv::findChessboardCorners(*iter,dimensions, pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        //cv::cornerSubPix(*iter, pointBuf, cv::Size(11,11), cv::Size(-1,-1),
       //cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
       // qDebug()<<"ok:"<<ok;
        if(ok) allFoundCorners.push_back(pointBuf);

    }
}

void ChessboardCalibration::createKnownBoardPosition( std::vector<cv::Point3f>& corners)
{
    for (int i = 0; i < dimensions.height; i++)
    {
        for (int j = 0; j < dimensions.width; j++)
        {
            corners.push_back(cv::Point3f(j * squareEdgeLength, i * squareEdgeLength, 0.0f));
        }
    }
}

void ChessboardCalibration::cameraCalibration(std::vector<cv::Mat> &calibrationImages)
{
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<std::vector<cv::Point3f>>	objectPoints(1);
    getChessboardCorners(calibrationImages, imagePoints);

    createKnownBoardPosition(objectPoints[0]);

    objectPoints.resize(imagePoints.size(), objectPoints[0]);
    qDebug()<<"Calibration startet";
    qDebug()<< objectPoints.empty();
    cv::calibrateCamera(objectPoints, imagePoints, dimensions, cameraMatrix, distanceCoefficients, rVectors, tVectors);
    qDebug()<<"Calibration finished";
}

double ChessboardCalibration::getElementDimension()
{
    return squareEdgeLength;
}

void ChessboardCalibration::setElementDimension(double newSquareEdgeLength)
{
    squareEdgeLength = newSquareEdgeLength;
}



