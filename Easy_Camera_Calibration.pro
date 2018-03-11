#-------------------------------------------------
#
# Project created by QtCreator 2018-02-13T15:35:08
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += xml



greaterThan(QT_MAJOR_VERSION, 4): QT +=\
                                     widgets\
                                     multimedia


TARGET = Easy_Camera_Calibration
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    welcome.cpp \
    calibrate.cpp \
    chessboardcalibration.cpp \
    saveloadxml.cpp

HEADERS += \
        mainwindow.h \
    welcome.h \
    calibrate.h \
    chessboardcalibration.h \
    saveloadxml.h

FORMS += \
        mainwindow.ui \
    welcome.ui

INCLUDEPATH += C:\\OpenCV_build\\install\\include

LIBS += -LC:\\OpenCV_build\\install\\x64\\vc15\\lib \
  -lopencv_aruco331d \
  -lopencv_bgsegm331d \
  -lopencv_bioinspired331d \
  -lopencv_calib3d331d \
  -lopencv_ccalib331d \
  -lopencv_core331d \
  -lopencv_datasets331d \
  -lopencv_dnn331d \
  -lopencv_dpm331d \
  -lopencv_face331d \
  -lopencv_features2d331d \
  -lopencv_flann331d \
  -lopencv_fuzzy331d \
  -lopencv_highgui331d \
  -lopencv_img_hash331d \
  -lopencv_imgcodecs331d \
  -lopencv_imgproc331d \
  -lopencv_line_descriptor331d \
  -lopencv_ml331d \
  -lopencv_objdetect331d \
  -lopencv_optflow331d \
  -lopencv_phase_unwrapping331d \
  -lopencv_photo331d \
  -lopencv_plot331d \
  -lopencv_reg331d \
  -lopencv_rgbd331d \
  -lopencv_saliency331d \
  -lopencv_shape331d \
  -lopencv_stereo331d \
  -lopencv_stitching331d \
  -lopencv_structured_light331d \
  -lopencv_superres331d \
  -lopencv_text331d \
  -lopencv_tracking331d \
  -lopencv_video331d \
  -lopencv_videoio331d \
  -lopencv_videostab331d \
  -lopencv_xfeatures2d331d \
  -lopencv_ximgproc331d \
  -lopencv_xobjdetect331d \
  -lopencv_xphoto331d

RESOURCES += \
    resource.qrc
