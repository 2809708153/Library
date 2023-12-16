#include "mythread.h"
#include <QDebug>
#include <QThread>
#include <QSound>

int counter = 0;
myThread::myThread(QObject *parent) : QObject(parent){

}
void myThread::startThreadSlot(){
    QSound *startsound=new QSound("C:\\Users\\Lenovo\\Desktop\\bk.wav",this);
    startsound->play();//
    startsound->setLoops(-1);//循环次数，-1代表一致循环
}

