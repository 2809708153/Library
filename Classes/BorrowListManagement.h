#pragma once

#include "BorrowList.h"
#include <fstream>
#include <list>
#include "BookManagement.h"
#include "Book.h"
#include "Classes/tm.h"

class BorrowListManagement{
private:
    list<BorrowList> BorrowListMgm;//借书表单
    int BorrowListNums;            //借阅总数
public:
    BorrowListManagement(){        //文件输入
        InputBorrowListsFromFile();
        BorrowListNums=static_cast<int>(BorrowListMgm.size());
    }
    int get_BorrowListNums(){      //返回借阅总数
        return BorrowListNums;
    }
    void AddBorrowList(BorrowList &BorrowList){   //添加借阅书
        BorrowListMgm.push_front(BorrowList);
        BorrowListNums++;
    }
    void DeleteBorrowList(BorrowList &BorrowList){//删除函数
        BorrowListMgm.remove(BorrowList);
        BorrowListNums--;
    }
    void ModifyBorrowList(BorrowList &oldBorrowList, BorrowList &newBorrowList){ //修改
        DeleteBorrowList(oldBorrowList);
        AddBorrowList(newBorrowList);
    }
   bool FindBorrowList(int id,BorrowList** bl){    //按id查找
        for (list<BorrowList>::iterator it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
            if (it->get_borrowListId() == id) {
                *bl = &(*it);
                return true;
            }
        }
        return false;
    }
    BorrowList& get_BorrowList_ByIndex(int i){      //通过索引返回书目
        list<BorrowList>::iterator it=BorrowListMgm.begin();
        while(i--)
            it++;
        return *it;
    }
    void PullBorrowRequest(long long ISBN,int borrowerId){  //借书请求操作
        time_t timeNow;
        time(&timeNow);
        tm time=*(localtime(&timeNow));
        BorrowList newBl(BorrowListNums+100001,borrowerId,ISBN,time);
        AddBorrowList(newBl);
    }
    bool OutputBorrowListsToFile(){                  //输出文件保存（类似于其他类）
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\borrowlist_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<BorrowList>::iterator it;
            for (it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
                stream << it->get_borrowListId() << "\t";
                stream << it->get_borrowerId() << "\t";
                stream << it->get_bookISBN() << "\t";
                stream << it->get_adminId() << "\t";
                stream << it->IsReturned() << "\t";
                stream << QString::fromStdString(it->get_borrowTime());
            }
            file.close();
            return true;
        }
        return false;
    }
    bool InputBorrowListsFromFile(){             //借书时间表单导入
        BorrowListNums=0;
        BorrowListMgm.clear();
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\borrowlist_data.txt");

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!file.atEnd()){
                QByteArray line = file.readLine();
                QString data(line);
                QString temp[20];
                int j = 0;
                for (int i = 0; data[i] != '\0'; i++) {
                    if (data[i] != '\t') {
                        temp[j] += data[i];
                    } else {
                        j++;
                        continue;
                    }
                }
                tm time;
                strptime(temp[5].toStdString().c_str(), "%a %b %d %H:%M:%S %Y", &time); //Windows的time标准库中没有该函数 tm.h 中重写（来自Linux gcc标准库）
                BorrowList newBorrowList(temp[0].toInt(), temp[1].toInt(),temp[2].toLongLong(),time,temp[3].toInt(),temp[4].toInt());
                AddBorrowList(newBorrowList);
            }
            file.close();
        }
        return true;
    }
};


//index
