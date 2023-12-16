#include "returnbook.h"
#include "ui_returnbook.h"
#include "QPropertyAnimation"
#include "QMessageBox"

ReturnBook::ReturnBook(QWidget *parent) ://还书界面，输入借书单号和归还按钮
    QWidget(parent),
    ui(new Ui::ReturnBook){
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    //这个属性控制窗口的透明度 取值范围是1.0(不透明)至0.0(全透明)。
    animation->setDuration(600); //设置仿真持续的时间
    animation->setStartValue(0); //设置初始值
    animation->setEndValue(0.91);//设置结束值
    animation->start();
}

ReturnBook::~ReturnBook(){
    delete ui;
}

void ReturnBook::on_but_ok_clicked(){   //点击归还按钮
    int id=ui->line_bid->text().toInt();
    if(!rlm.PullReturnRequest(id)){
        QMessageBox::critical(this,"错误","未查询到该书目，请核对后重新输入","确认");
    }else{
        rlm.OutputReturnListsToFile();
        QMessageBox::information(this,"成功","申请成功！");
    }
}

//index


