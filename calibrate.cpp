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

bool Calibrate::getFound()
{
    return found;
}
