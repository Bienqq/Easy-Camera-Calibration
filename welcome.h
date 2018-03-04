#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>



class  MainWindow;


namespace Ui
{
    class Welcome;

}

class Welcome : public QDialog
{
    Q_OBJECT

public:

    explicit Welcome(QWidget *parent = 0);

    ~Welcome();

private slots:

   void on_chessBoardButton_clicked();

   void on_chArucoBoardButton_clicked();

   void on_circlesBoardButton_clicked();

private:

    Ui::Welcome *ui;

    MainWindow *mainWindow;

public slots:

    void back();

};



#endif // WELCOME_H
