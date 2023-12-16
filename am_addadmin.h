#ifndef AM_ADDADMIN_H
#define AM_ADDADMIN_H

#include <QWidget>
#include "Classes/Admin.h"

namespace Ui {
class am_AddAdmin;
}

class am_AddAdmin : public QWidget
{
    Q_OBJECT
public:
    explicit am_AddAdmin(QWidget *parent = nullptr);
    ~am_AddAdmin();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:   //信号函数
    void sendAdmin_aa(Admin);
private slots:
    void on_but_ok_clicked();
    void on_but_no_clicked();
    void on_but_ok_2_clicked();
private:   //槽函数
    Ui::am_AddAdmin *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
};

#endif // AM_ADDADMIN_H


//index
