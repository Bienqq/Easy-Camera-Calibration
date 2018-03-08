#include "welcome.h"
#include "ui_welcome.h"
#include "mainwindow.h"
#include <QDebug>


Welcome::Welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::on_chessBoardButton_clicked()
{
    mainWindow = new MainWindow(CHESSBOARD,this);
    this->hide();
    mainWindow->show();
    connect(mainWindow, SIGNAL(signalBackToMenu()), this, SLOT(back()));
}

void Welcome::on_chArucoBoardButton_clicked()
{

}

void Welcome::on_circlesBoardButton_clicked()
{

}

void Welcome::back()
{
    mainWindow->close();
    this->show();
    delete mainWindow;
}
