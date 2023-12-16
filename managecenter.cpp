#include "managecenter.h"
#include "ui_managecenter.h"
#include "qpropertyanimation.h"
#include "mainwindow.h"
#include "QMessageBox"

ManageCenter::ManageCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCenter){
    ui->setupUi(this);
    ui->stackedWidget->setParent(this);
    bm=new BookM(this);
    ui->stackedWidget->addWidget(bm);
    ai=new AdminInfo;
    ui->stackedWidget->addWidget(ai);
    rm=new ReaderM;
    ui->stackedWidget->addWidget(rm);
    blm=new BorrowListM;
    ui->stackedWidget->addWidget(blm);
    adm=new AdminM;
    ui->stackedWidget->addWidget(adm);
    rlm=new ReturnListM;
    ui->stackedWidget->addWidget(rlm);

    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
    this->setWindowFlags(Qt::FramelessWindowHint);         //设置无边框窗口
}

void ManageCenter::closeEvent(QCloseEvent *event){
    int button;
    button = QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("确认退出程序?")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
          event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
          event->accept();  //接受退出信号，程序停止运行
    }
}

ManageCenter::~ManageCenter(){
    delete ui;
}

void ManageCenter::receiveAdmin(Admin ad){
    loger=ad;
}

void ManageCenter::on_btn_book_clicked(){
    ui->stackedWidget->setCurrentWidget(bm);
}

void ManageCenter::on_btn_logout_clicked(){
    this->close();
}

void ManageCenter::on_btn_personal_clicked(){
    ai->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(ai);
}

void ManageCenter::on_btn_reader_clicked(){
    ui->stackedWidget->setCurrentWidget(rm);
}

void ManageCenter::on_btn_borrow_clicked(){
    blm->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(blm);
}

void ManageCenter::on_btn_admin_clicked(){
    ui->stackedWidget->setCurrentWidget(adm);
}

void ManageCenter::on_btn_return_clicked(){
    rlm->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(rlm);
}


//index
