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
    mainWindow = new MainWindow(0,this);
    this->hide();
    mainWindow->show();

    qDebug()<<"Stworzono i pokazano mainWindow";

    connect(mainWindow, SIGNAL(signalBackToMenu()), this, SLOT(back()));

    qDebug()<<"Polonczono nowy powstaly obiekt z oknem powitalnym";
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

    qDebug()<<"Zwolnienie pamieci";
}
