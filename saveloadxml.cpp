#include "saveloadxml.h"
#include "calibrate.h"
#include <QFileDialog>
#include <QDir>
#include <QDialogButtonBox>
#include <QDebug>
#include <QtXml>

SaveLoadXML::SaveLoadXML()
{

}

SaveLoadXML::~SaveLoadXML()
{

}

void SaveLoadXML::saveData(Calibrate *CalibrationObject, QString patternName, int savedImagesNumber, QWidget *parent)
{
    QString filter = "XML File (*.xml)";
    QString fileName = QFileDialog::getSaveFileName(parent, "Save a XML file", QDir::homePath(), filter);
    if(fileName.isNull())
    {
        return;
    }
    QFile fileXML(fileName);
    fileXML.open(QIODevice ::WriteOnly);
    QXmlStreamWriter xmlWriter(&fileXML);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeTextElement("Used Calibration Pattern","Used Calibration Pattern", patternName);
    xmlWriter.writeTextElement("Board dimensions", "Board dimensions","(" + QString::number(CalibrationObject->getDimensions().width) + ","+ QString::number(CalibrationObject->getDimensions().height)+")");
    xmlWriter.writeTextElement("Number of frames","Number of frames", QString::number(savedImagesNumber));
    xmlWriter.writeStartElement("Camera Parameters");
    xmlWriter.writeTextElement("Camera Parameters","Camera Matrix", CalibrationObject->getCameraMatrixQString());
    xmlWriter.writeTextElement("Camera Parameters","DistanceCoefficients", CalibrationObject->getDistanceCoefficientsQString());
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    fileXML.close();
}
