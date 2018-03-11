#ifndef CHESSBOARDCALIBRATION_H
#define CHESSBOARDCALIBRATION_H

#include "calibrate.h"


class ChessboardCalibration : public Calibrate
{
public:
    ChessboardCalibration();

    void setElementDimension(double) override ;
    double getElementDimension() override;
    bool foundAndDraw(cv::Mat&,cv::Mat&, bool)override ;
    bool cameraCalibration(std::vector<cv::Mat>&) override;
    void getChessboardCorners(std::vector<cv::Mat>&, std::vector<std::vector<cv::Point2f>> &);
    void createKnownBoardPosition(std::vector<cv::Point3f>&);

protected:
     double squareEdgeLength = 0.0; // size in millimeters on the side of the square
};

#endif // CHESSBOARDCALIBRATION_H
