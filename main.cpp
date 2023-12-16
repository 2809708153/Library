#include "mainwindow.h"
#include <QApplication>
#include "QMetaType"
#include <QSound>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    //文本文件的路径改为本地文件系统路径
    w.show();
    return a.exec();
}
