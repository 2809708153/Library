#include "readerm.h"
#include "ui_readerm.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"
#include "QMessageBox"
#include "rm_addreader.h"
ReaderM::ReaderM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderM){
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    //这个属性控制窗口的透明度 取值范围是1.0(不透明)至0.0(全透明)。
    animation->setDuration(600);  //设置仿真持续的时间
    animation->setStartValue(0);  //设置初始值
    animation->setEndValue(1); //设置结束值
    animation->start();

    ar=new rm_AddReader;
    mr=new rm_ModifyReader;

    connect(ar,SIGNAL(sendReader_ar(Reader)),this,SLOT(receiveReader_ar(Reader)));
    connect(this,SIGNAL(sendReader_mr(Reader)),mr,SLOT(receiveReader_mr(Reader)));
    connect(mr,SIGNAL(sendReader_mr(Reader,Reader)),this,SLOT(receiveReader_mr(Reader,Reader)));
    //对tablewidget做一些设置
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);            //设置不可编辑
    ui->tableWidget->verticalHeader()->setVisible(false);                           //设置行号不可见
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
    ui->tableWidget->setFrameShape(QFrame::NoFrame);                                //设置无边框
    ui->tableWidget->setShowGrid(false);                                            //设置不显示格子线
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);           //整行选取

    int readerNums=this->rdm.get_ReaderNums();
    for(int i=0;i<readerNums;i++){
        Reader t=this->rdm.get_Reader_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
    }
}


ReaderM::~ReaderM(){
    delete ui;
}

void ReaderM::on_button_add_clicked(){
    ar->show();
}

void  ReaderM::receiveReader_ar(Reader newReader){
    rdm.AddReader(newReader);           //在列表开头加一个
    rdm.OutputReadersToFile();          //把reader信息写入文件
    ui->tableWidget->setRowCount(0);    //清空列表
    int readerNums=this->rdm.get_ReaderNums();
    for(int i=0;i<readerNums;i++){
        Reader t=this->rdm.get_Reader_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
    } //setItem函数：给tablewidget 赋值，行、列、值
}



void ReaderM::on_button_delete_clicked(){  //删除按钮
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();//先选中
    int count=ranges.count();
    for(int i=0;i<count;i++){
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++){
            long long account=ui->tableWidget->item(j,2)->text().toLongLong();
            rdm.DeleteReader(account);//通过remove删除与account匹配的
        }
        rdm.OutputReadersToFile(); //把表里的写入文件
        ui->tableWidget->setRowCount(0);  //清空列表
        int readerNums=this->rdm.get_ReaderNums();
        for(int i=0;i<readerNums;i++){  //删除完之后重新输入一遍
            Reader t=this->rdm.get_Reader_ByIndex(i);
            int rowcount=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
        }
    }
}

void ReaderM::on_button_all_clicked(){
    rdm.InputReadersFromFile();
    ui->tableWidget->setRowCount(0);  //清空列表
    int readerNums=this->rdm.get_ReaderNums();
    for(int i=0;i<readerNums;i++){
        Reader t=this->rdm.get_Reader_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
    }
}

void ReaderM::on_button_modify_clicked(){
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
    int cnt=0;
    int count=ranges.count();
    for(int i=0;i<count;i++){
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++){
            cnt++;
        }
        if(cnt>1){
            QMessageBox::critical(this,"错误","只能选中单一读者进行修改","确认");
        }else{
            int i = ui->tableWidget->currentRow();
            long long account = ui->tableWidget->item(i,2)->text().toLongLong();
            Reader old;
            rdm.FindReader(account,old);
            emit sendReader_mr(old);  //
            mr->show();  //rm_modifyreader
        }
    }
}

void ReaderM::receiveReader_mr(Reader oldReader,Reader newReader){
    rdm.ModifyReader(oldReader,newReader);  //把OLD删掉，NEW添加
    rdm.OutputReadersToFile();
    int readerNums=this->rdm.get_ReaderNums();
    ui->tableWidget->setRowCount(0);  //清空列表
    for(int i=0;i<readerNums;i++){
        Reader t=this->rdm.get_Reader_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
    }
}

void ReaderM::on_button_search_clicked(){//搜完想重新搜要点一下显示全部
    QString rule=ui->searchbox->currentText();
    QString data=ui->searchle->text();
    if(rule=="按姓名"){
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,1)->text().toStdString()==data.toStdString()){
                Reader t;
                rdm.FindReader(ui->tableWidget->item(i,2)->text().toLongLong(),t);//QSTRING转长整型
                ui->tableWidget->setRowCount(0);  //清空列表
                int rowcount=ui->tableWidget->rowCount();//把这行的输出
                ui->tableWidget->insertRow(rowcount);
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
                break;
            }
        }
    }else if(rule=="按学号"){
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(data.toInt()==ui->tableWidget->item(i,0)->text().toInt()){
                long long account= ui->tableWidget->item(i,2)->text().toLongLong();
                Reader t;
                rdm.FindReader(account,t);
                ui->tableWidget->setRowCount(0);  //清空列表
                int rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
                break;
            }
        }
    }else{
        long long account=data.toLongLong();
        Reader t;
        rdm.FindReader(account,t);
        ui->tableWidget->setRowCount(0);  //清空列表
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_totalBorrowedBooks())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_curBorrowedBooks())));
    }
}

void ReaderM::on_button_setpas_clicked()
{
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
    int count=ranges.count();
    for(int i=0;i<count;i++)
    {
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++)
        {
            long long account=ui->tableWidget->item(j,2)->text().toLongLong();
            Reader *t;
            rdm.FindReader(account,&t);
            t->set_password("123456");
        }
        rdm.OutputReadersToFile();
        QMessageBox::information(this,"成功","重置为初始密码成功！",QMessageBox::Yes);
    }
}

//index
