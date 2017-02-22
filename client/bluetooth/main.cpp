#include "mainwindow.h"
#include <QApplication>
//#include "callpy.h"

//#define TEST

int main(int argc, char *argv[])
{
#ifdef TEST
    long Data[] = {0,1,2,3,4,5,6,7,8,9,11};
    CallPy::act("python3 /home/pi/wyo/smartGG/client/post.py  http://192.168.191.2/smartgg/index.php/sgg/update", Data + 1, 10);
    Callpy::act("python3 /home/pi/wyo/smartGG/client/get.py http://192.168.191.2/smartgg/index.php/sgg/moisture");
//  "/tmp/smartgg"
#endif


    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
