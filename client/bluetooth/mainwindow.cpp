//添加setmoisture函数 f
//添加两个按钮 f
//添加ip输入 f
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QDebug>
#include "DataDecoder.h"
#include  "callpy.h"
#include  <fstream>
#include  <iostream>
#include "chttpp.h"

CHttpp httpSender;
bool svrMoistureLast=false;
bool isMoistureOpen(const string & IP);
void syncData(const string & IP,long *);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*打开串口和启动定时器*/
    readTimer = new QTimer(this);
    fSerialPort = open_port("/dev/ttyAMA0");
    //if (fSerialPort == -1) qDebug()<<"Cannot open ferial port.";
    set_port(fSerialPort);
    init_sp(fSerialPort);
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
   // qDebug()<<"Serial Port Is Opened.";
    write(fSerialPort,"linked.",7);
    readTimer->start(500);
    //connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_actionExit_triggered 菜单中退出命令槽函数
 */
void MainWindow::on_actionExit_triggered()
{
    this->close();
}




/**
 * @brief MainWindow::readMyCom 定时读取串口，并解码
 */
void MainWindow::readMyCom()
{
    int len = read(fSerialPort, &datarec, 71);
    //qDebug()<<"TIMER";
    qDebug()<<"svrMoisSt:"<<httpSender.isMoistureOpen();
    if(isIPSet){
        if(httpSender.isMoistureOpen()&&svrMoistureLast==false){
            setMoistifier(true);
            svrMoistureLast=true;
            qDebug()<<"svrMoisSt: ON";
        }else if(httpSender.isMoistureOpen()==false&&svrMoistureLast==true){
            setMoistifier(false);
            svrMoistureLast=false;
            qDebug()<<"svrMoisSt: OFF";
        }
    }

    if(len!=0){
 //       for(int j = 0; j<len;j++){
 //           cout<< hex << (int)datarec[j] <<std::endl;
 //       }
        for(int j = 0; j<len;j++){
            Receive(&datarec[j]);         //将数据data放入receive函数，做判断
            if(decode()){   //进入这个if说明解码成功
                for(int i=1; i<=PACKAGES_NUM;i++ ){
                   // qDebug() << i << ": "<< Data[i];
                }




                /*
                 * 数据一共11个，在数组Data中，下标0没用，从下标1开始计数，其中Data[11]没有用到，单片机会发0
                 * Data[1] 传感器1的模拟信号
                 * Data[2] 传感器1的模拟信号
                 * Data[3] 传感器2的模拟信号
                 * Data[4] 传感器2的模拟信号
                 * Data[5] 传感器3的模拟信号
                 * Data[6] 传感器3的模拟信号
                 * Data[7] 传感器4的模拟信号
                 * Data[8] 传感器4的模拟信号
                 * Data[9] 温度传感器数据
                 * Data[10] 湿度传感器数据
                */

                char str[20];
                sprintf(str,"%d",Data[1]);
                ui->lcdNumber_MQ2->display(str);
                ui->progressBar_MQ2->setValue(Data[1]);
                sprintf(str,"%d",Data[3]);
                ui->lcdNumber_MQ7->display(str);
                ui->progressBar_MQ7->setValue(Data[3]);
                sprintf(str,"%d",Data[5]);
                ui->lcdNumber_MQ4->display(str);
                ui->progressBar_MQ4->setValue(Data[5]);
                sprintf(str,"%d",Data[7]);
                ui->lcdNumber_MQ135->display(str);
                ui->progressBar_MQ135->setValue(Data[7]);
                sprintf(str,"%d",Data[9]);
                ui->lcdNumber_tmpt->display(str);
                sprintf(str,"%d",Data[10]);
                ui->lcdNumber_moi->display(str);
                QPalette Lcdpat = ui->lcdNumber_MQ135->palette();

         //       CallPy::act("python3 /home/pi/wyo/smartGG/client/post.py  http://192.168.191.2/smartgg/index.php/sgg/update", Data + 1, 10);
        //        CallPy::act("python3 /home/pi/wyo/smartGG/client/post.py  http://192.168.191.4/smartgg/index.php/sgg/update", Data + 1, 10);

                if(Data[1]>1000){
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
                     Data[2]=1;
                }else{
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
                     Data[2]=0;
                }
                ui->lcdNumber_MQ2->setPalette(Lcdpat);
                if(Data[3]>1000){
                    Data[4]=1;
                    Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
                }else{
                    Data[4]=0;
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
                }
                ui->lcdNumber_MQ7->setPalette(Lcdpat);
                if(Data[5]>1000){
                    Data[6]=1;
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
                }else{
                    Data[6]=0;
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
                }
                ui->lcdNumber_MQ4->setPalette(Lcdpat);
                if(Data[7]>1000){
                    Data[8]=1;
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
                }else{
                    Data[8]=0;
                     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
                }
                ui->lcdNumber_MQ135->setPalette(Lcdpat);


                if(isIPSet) {
                    httpSender.syncData((int *)(Data+1), 10);
                }

                /**
                    网页通信可以在这里插入
                  */
            }
        }
    }
/*    if(myCom->bytesAvailable() >=8 )
    //如果可用数据大于或等于8字节再读取
    {
        qDebug() << "read: "<<myCom->bytesAvailable()<<"bytes";
        QByteArray temp = myCom->readAll();
        qDebug() << temp;
        ui->lcdNumber_MQ4->display("123");
    }
    //qDebug() << "Polling"<<endl;
    //qDebug() << "read: "<<myCom->bytesAvailable()<<"bytes";
    QByteArray tmp=myCom->readAll();
    QByteArray::iterator ite=tmp.begin();
    for(;ite!=tmp.end();ite++){
        char str[20];
        sprintf(str,"%d",(int)(*ite));
        ui->lcdNumber_MQ135->display(str);
    }
    ui->lcdNumber_MQ4->display("123");
*/

}

/**
 * @brief MainWindow::on_pushButton_clicked 实现开启关闭加湿器
 */

void MainWindow::on_pushButton_clicked()
{
    /*
     QPalette Lcdpat = ui->lcdNumber_MQ135->palette();
     Lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
    ui->lcdNumber_MQ135->display("123");
    ui->lcdNumber_MQ135->setPalette(Lcdpat);
    ui->lcdNumber_MQ135->display("456 ");
    //myCom->write("1234");
    write(fSerialPort,"linked.",7);*/
    setMoistifier(true);
    //QDebug("打开加湿器");
}

void MainWindow::on_pushButton_2_clicked()
{
    setMoistifier(false);
    //QDebug("打开加湿器");
}

/**
 * @brief MainWindow::setMoistifier 实现开启关闭加湿器
 */

void MainWindow::setMoistifier(bool b){
     if(b){
         send_byte(fSerialPort,1);
     }else{
         send_byte(fSerialPort,0);
     }
}



/**
 * @brief MainWindow::on_pushButton_3_clicked 设置IP地址
 */

void MainWindow::on_pushButton_3_clicked()
{
    long Data[] = {0,111,0,331,0,551,0,771,0,99,100};
    IP = ui->lineEdit->text().toStdString(); //地址存入变量IP（std::string）
    httpSender.setIp(IP);
    isIPSet=true;
    svrMoistureLast=httpSender.isMoistureOpen();
}


