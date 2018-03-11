#include "chessboardcalibration.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include <QThread>

ChessboardCalibration::ChessboardCalibration()
    :Calibrate()
{


}


bool ChessboardCalibration::foundAndDraw(cv::Mat& frame, cv::Mat& outputFrame, bool showResult)
{
    bool found = cv::findChessboardCorners(frame, dimensions, foundPoints, CV_CALIB_CB_FAST_CHECK);
    if(showResult == true)
    {
        cv::drawChessboardCorners(frame, dimensions, foundPoints, found); // drawing corners
    }
    if (found == true)
    {
        cv::putText(frame, "Chessboard was found", cv::Point2i(20,40), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0x00, 0xff, 0x00), 3);
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
    for (std::vector<cv::Mat>::iterator iter = images.begin(); iter != images.end(); iter++)
    {
        cv::cvtColor(*iter, *iter, CV_BGR2GRAY);
        std::vector<cv::Point2f> pointBuf;
        cv::findChessboardCorners(*iter,dimensions, pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        // to provide better accuracy calling cornerSubPix
        cv::cornerSubPix(*iter, pointBuf, cv::Size(11,11), cv::Size(-1,-1),
        cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1)); // calibration criteria taken from OpenCV source code
        allFoundCorners.push_back(pointBuf);
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

bool ChessboardCalibration::cameraCalibration(std::vector<cv::Mat> &calibrationImages)
{
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<std::vector<cv::Point3f>> objectPoints(1);
    getChessboardCorners(calibrationImages, imagePoints);
    createKnownBoardPosition(objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);
    cv::calibrateCamera(objectPoints, imagePoints, dimensions, cameraMatrix, distanceCoefficients, rVectors, tVectors);
    return true;
}

double ChessboardCalibration::getElementDimension()
{
    return squareEdgeLength;
}

void ChessboardCalibration::setElementDimension(double newSquareEdgeLength)
{
    squareEdgeLength = newSquareEdgeLength;
}



