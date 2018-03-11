#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCameraInfo>
#include <QList>
#include <QDebug>
#include <QFileDialog>
#include <QDialogButtonBox>


#include "welcome.h"
#include "chessboardcalibration.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "saveloadxml.h"




MainWindow::MainWindow(Calibration::CalibTypes type, QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); //turning off the possibility of changing the dimensions of the window
    ui->setupUi(this);
    ui->tryAgain->hide();       // hiding elements
    ui->noConnected->hide();
    ui->saveFrameButton->hide();
    ui->savedImages->hide();
    ui->savedNumbers->hide();
    ui->savedNumbers->setText(QString::number(savedImagesNumber)); // resetting the photo counter
    tmrTimer = new QTimer(this); //creating new timer


    connect(ui->backToMenu, SIGNAL(clicked()), this, SLOT(on_backToMenu_clicked()));
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));

    if(type == Calibration::CHESSBOARD) // type 0 means Chessboard Patterm
    {
        patternName = "CHESSBOARD";
        CalibrationObject = new ChessboardCalibration();
    }
    else if(type == Calibration::CIRCLESBOARD)
    {
        patternName = "CIRCLESBOARD";
    }
    else
    {
        patternName = "CHARUCOBOARD";
    }
    on_tryAgain_clicked();
}

MainWindow::~MainWindow()
{
    delete CalibrationObject;
    delete ui;
}

void MainWindow::processFrameAndUpdateGUI()
{
    if(!capWebcam.read(matOriginal)) // if cannot read frame
    {
        on_tryAgain_clicked();
        return;
    }
    matOriginal.copyTo(matDrawn);
    // reading frame
    if(calibButtonClicked == true )
    {
        CalibrationObject->foundAndDraw(matDrawn, matDrawn, true);
    }
    if(savedImagesNumber < 15)
    {
        ui->calibrateCameraButton->setDisabled(true);
    }
    //convert Mat to QImage
    cv::cvtColor(matDrawn, matDrawn, CV_BGR2RGB);
    QImage qimgOriginal(matDrawn.data, static_cast<int>(matDrawn.cols), static_cast<int>(matDrawn.rows), static_cast<int>(matDrawn.step), QImage::Format_RGB888);
    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
}

void MainWindow::on_tryAgain_clicked() //counting avaliable cameras
{
    QList<QCameraInfo> cameralist;
    int temp;

    cameralist = QCameraInfo::availableCameras();
    temp = 0;

    foreach(QCameraInfo cam , cameralist)
    {
        temp++;
    }
    MAX_CAMERA_NUMBER = temp;

    // if any camera is avaliable
    if( MAX_CAMERA_NUMBER != 0 )
    {
        capWebcam.open(0);
        cameraWasOpened = true;
        ui->tryAgain->hide();
        ui->noConnected->hide();
        tmrTimer->start(20);
    }
    else  // if not
    {
        cameraWasOpened = false;
        QMessageBox::critical(this, "Critical error", "Cannot open camera. Please check your camera connection.");
        ui->tryAgain->show();
        ui->noConnected->show();
    }
}

bool MainWindow::open_Camera(int camera_index)
{
    if(!capWebcam.open(camera_index))
    {
        on_tryAgain_clicked();
        cameraWasOpened = false;
        return false;
    }
    cameraWasOpened = true;
    return true;
}

void MainWindow::on_nextButton_clicked()
{
    if(MAX_CAMERA_NUMBER != 0 && camera_index < (MAX_CAMERA_NUMBER - 1))
    {
       camera_index++;
       open_Camera(camera_index);
    }
}

void MainWindow::on_previousButton_clicked()
{
    if(MAX_CAMERA_NUMBER != 0 && camera_index >0)
    {
       camera_index--;
       open_Camera(camera_index);
    }
}

void MainWindow::on_backToMenu_clicked()
{
    emit signalBackToMenu();
}

void MainWindow::on_calibrationButton_clicked()
{
    if(calibButtonClicked == false && widthWasSet == true && heightWasSet == true &&
       CalibrationObject->getDimensions().height > 2 && CalibrationObject->getDimensions().width > 2
       && cameraWasOpened == true &&  CalibrationObject->getElementDimension() > 20.0)
    {
        ui->calibrationButton->setText("Stop Calibration");
        ui->saveFrameButton->show();
        ui->savedImages->show();
        ui->savedNumbers->show();
        ui->height->setDisabled(true);
        ui->width->setDisabled(true);
        ui->nextButton->setDisabled(true);
        ui->previousButton->setDisabled(true);
        ui->squareDimensions->setDisabled(true);
        calibButtonClicked = true;
    }
    else if(cameraWasOpened == false)
    {
        QMessageBox::critical(this, "Critical error", "Cannot open camera. Please check your camera connection.");
        ui->tryAgain->show();
        ui->noConnected->show();
    }
    else if(widthWasSet == false || heightWasSet == false)
    {
        QMessageBox::warning(this, "Warning!", "Chessboard dimensions was not set. Please set width and height of your chessboard in order to start calibration process!");
    }
    else if(CalibrationObject->getDimensions().height <= 2 || CalibrationObject->getDimensions().width <= 2)
    {
        QMessageBox::warning(this, "Warning!", "Width and height of the chessboard should be bigger than 2 !");
    }
    else if(CalibrationObject->getElementDimension() <= 20.0)
    {
        QMessageBox::warning(this, "Warning!", "Square edge length should be bigger than 20 mm !");
    }
    else
    {
         ui->calibrationButton->setText("Start Calibration");
         ui->saveFrameButton->hide();
         ui->savedImages->hide();
         ui->savedNumbers->hide();
         ui->height->setEnabled(true);
         ui->width->setEnabled(true);
         ui->previousButton->setEnabled(true);
         ui->nextButton->setEnabled(true);
         ui->squareDimensions->setEnabled(true);
         savedImagesNumber = 0;
         ui->savedNumbers->setText(QString::number(savedImagesNumber));
         calibrationImages.clear();
         calibButtonClicked = false;
    }

}

void MainWindow::on_height_valueChanged(int arg1)
{
    CalibrationObject->setHeight(arg1);
    heightWasSet = true;
}

void MainWindow::on_width_valueChanged(int arg1)
{
    CalibrationObject->setWidth(arg1);
    widthWasSet = true;
}

void MainWindow::on_saveFrameButton_clicked()
{
    if(CalibrationObject->foundAndDraw(matOriginal, matOriginal, false) == true)
    {
        savedImagesNumber++;
        ui->savedNumbers->setText(QString::number(savedImagesNumber));
        calibrationImages.push_back(matOriginal);
        if(savedImagesNumber >= 15)
        {
            ui->calibrateCameraButton->setEnabled(true);
        }
    }
    else
    {
     QMessageBox::information(this, "Info", "Saving images have to contain an image of chessboard");
    }
}

void MainWindow::on_calibrateCameraButton_clicked()
{
    calibButtonClicked = false;
    CalibrationObject->cameraCalibration(calibrationImages);
    ui->calibrationButton->setText("Start Calibration");
    ui->saveFrameButton->hide();
    ui->savedImages->hide();
    ui->savedNumbers->hide();
    ui->height->setEnabled(true);
    ui->width->setEnabled(true);
    ui->previousButton->setEnabled(true);
    ui->nextButton->setEnabled(true);
    ui->squareDimensions->setEnabled(true);
    calibrationImages.clear();
    calibButtonClicked = false;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Info", "Camera calibration process has been successfully completed", QMessageBox::Save | QMessageBox::Cancel);
    if(reply == QDialogButtonBox::Save)
    {
       SaveLoadXML save;
       save.saveData(CalibrationObject, patternName, savedImagesNumber, this);
    }
    savedImagesNumber = 0;
    ui->savedNumbers->setText(QString::number(savedImagesNumber));
}

void MainWindow::on_squareDimensions_valueChanged(double arg1)
{
    CalibrationObject->setElementDimension(arg1);
}
