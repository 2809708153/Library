#ifndef ADMININFO_H  //如果ADMININFO_H还没有被定义过
#define ADMININFO_H  //定义ADMININFO_H

#include <QWidget>
#include "Classes/AdminManagement.h"

namespace Ui {    //命名空间 Ui
class AdminInfo;  //声明 AdminInfo 类
}

class AdminInfo: public QWidget{  //类AdminInf继承QWidget
    Q_OBJECT  //使用Qt的宏，允许使用信号和槽等特性
public:
    explicit AdminInfo(QWidget *parent = nullptr);
    ~AdminInfo();
    void set_loger(Admin ad);
private slots:
    void on_but_ok_clicked();  //声明槽函数
private:
    Ui::AdminInfo *ui;         //声明Ui::AdminInfo类型的指针变量ui
    Admin loger;
    AdminManagement adm;
};

#endif  // 结束条件编译指令


//index
