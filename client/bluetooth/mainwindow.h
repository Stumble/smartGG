#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "posix_qextserialport.h"
#include "SPort.h"
#include <QTimer>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_pushButton_clicked();
    void readMyCom();
    void setMoistifier(bool);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
   // Posix_QextSerialPort *myCom;
    int fSerialPort;
    QTimer *readTimer;
    string IP;
    bool isIPSet=false;
};

#endif // MAINWINDOW_H
