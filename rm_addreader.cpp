#include "rm_addreader.h"
#include "ui_rm_addreader.h"
#include "QPropertyAnimation"
#include "QMouseEvent"

rm_AddReader::rm_AddReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rm_AddReader){
    ui->setupUi(this);
    QPalette pa(this->palette());
    QImage img = QImage(":/image/image/broad.jpg");
    img = img.scaled(this->size());
    QBrush *pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setAutoFillBackground(true);
    this->setPalette(pa);                           //设置背景
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
    this->setWindowFlags(Qt::FramelessWindowHint);  //去掉标题栏
    isMove=false;
}

rm_AddReader::~rm_AddReader(){
    delete ui;
}

void rm_AddReader::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();//获取的鼠标位置是鼠标偏离电脑屏幕左上角（x=0, y=0）的位置。Qpoint类型
        windowPoint = this->frameGeometry().topLeft();//获取包括了标题栏客户区的左上角的点位置
    }
}

void rm_AddReader::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void rm_AddReader::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        isMove = false;                       //改变移动状态
    }
}


void rm_AddReader::on_but_ok_clicked(){
    QString name=ui->lename->text();
    QString id=ui->leid->text();
    QString account=ui->leacc->text();
    Reader newReader(id.toLongLong(),account.toInt(),name.toStdString());//给reader赋值
    //QString转换长整形数据时会使用
    emit sendReader_ar(newReader);//发送信号signal
    ui->lename->clear();//textedit
    ui->leid->clear();
    ui->leacc->clear();
    this->close();
}

void rm_AddReader::on_but_no_clicked(){
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    this->close();
}

void rm_AddReader::on_create_clicked(){  //随机生成读者证号
    QString str;
    QString account;
    int* shu = new int[7];//动态创建数组
            for (int i = 0; i < 6; i++){
                *(shu + i) = rand() % 9+1; //随机生成七位
                QString str=QString::number(*(shu + i));
                account+=str;
            }

            delete[] shu;//释放
     ui->leacc->setText(account);
}


//index
