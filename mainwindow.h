#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "calibrate.h"




#include <opencv2/opencv.hpp>

class Welcome;


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (unsigned int CalibType, QWidget *parent = 0);

    ~MainWindow();


private:
    int savedImagesNumber = 0;
    std::vector<cv::Mat> calibrationImages;
    bool widthWasSet = false;
    bool heightWasSet = false;
    bool cameraWasOpened;
    Calibrate *CalibrationObject;
    bool calibButtonClicked = false;
    int MAX_CAMERA_NUMBER;
    cv::VideoCapture capWebcam;
    bool open_Camera(int); // function to openCamera with appropriate index
    Ui::MainWindow *ui;
    cv::Mat matOriginal;   // Mat object in OpenCV style
    cv::Mat matDrawn;
    QImage qimgOriginal;            // Image in Qt stye
    QTimer* tmrTimer;       // timer
    int camera_index = 0;  // currently running camera
    QString patternName;

public slots:
    void processFrameAndUpdateGUI();

    void on_backToMenu_clicked();

signals:

    void signalBackToMenu();

private slots:

    void on_tryAgain_clicked(); //button to re-enable the image from the camera
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_calibrationButton_clicked();
    void on_height_valueChanged(int arg1);
    void on_width_valueChanged(int arg1);
    void on_saveFrameButton_clicked();
    void on_calibrateCameraButton_clicked();
    void on_squareDimensions_valueChanged(double arg1);
};


#endif // MAINWINDOW_H


