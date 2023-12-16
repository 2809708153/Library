#pragma once

#include "Reader.h"
#include <list>
#include <fstream>
#include "QFile"
#include "QTextStream"
using namespace std;

class ReaderManagement{
private:
    list<Reader> ReaderMgm;      //STL中的list双向链表
    int ReaderNums;              //读者总数
public:
    ReaderManagement() {         //构造函数文件输入
        InputReadersFromFile();
        ReaderNums=static_cast<int>(ReaderMgm.size());
    }
    int get_ReaderNums(){        //获得读者数量
        return ReaderNums;
    }
    void AddReader(Reader &reader){     //增加读者
        ReaderMgm.push_front(reader);
        ReaderNums++;
    }
    void DeleteReader(Reader &reader){  //根据Reader对象删除读者
        ReaderMgm.remove(reader);
        ReaderNums--;
    }
    void DeleteReader(long long account){//通过账号删除读者
        Reader reader;
        FindReader(account,reader);
        ReaderMgm.remove(reader);
        ReaderNums--;
    }
    void ModifyReader(Reader &oldReader, Reader &newReader){//修改读者信息
        DeleteReader(oldReader);
        AddReader(newReader);
    }
    bool LoginReader(int acc,string pas){            //检索账号是否存在及密码是否正确
        Reader readerToLogin;
        FindReader(acc,readerToLogin);
        return readerToLogin.Check(pas);
    }
    bool FindReader(long long account,Reader& ret){  //通过账号查找读者
        for (list<Reader>::iterator it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            if (it->get_account() == account) {
                ret= *it;
                return true;
            }
        }
        return false;
    }
    bool FindReader(long long account,Reader** ret){  //通过账号查找读者
        for (list<Reader>::iterator it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            if (it->get_account() == account) {
                *ret= &(*it);
                return true;
            }
        }
        return false;
    }
    bool FindReader_ById(int id,Reader** ret){        //通过id（学号）查询读者
        for (list<Reader>::iterator it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            if (it->get_id() == id) {
                *ret= &(*it);
                return true;
            }
        }
        return false;
    }
    Reader& get_Reader_ByIndex(int i){                //通过索引返回读者
        list<Reader>::iterator it=ReaderMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    void ChangePas(Reader& rd,string pas){             //修改读者密码
        Reader newrd=rd;
        newrd.set_password(pas);
        ModifyReader(rd,newrd);
    }
    bool OutputReadersToFile(){                        //文件保存
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\reader_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<Reader>::iterator it;
            for (it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
                stream << it->get_id() << "\t";
                stream << it->get_account() << "\t";
                stream << QString::fromStdString(it->get_name()) << "\t";
                stream << QString::fromStdString(it->get_password()) << "\t";
                stream << it->get_totalBorrowedBooks() << "\t";
                stream << it->get_curBorrowedBooks() << "\t";
                stream << endl;
            }
            file.close();
            return true;
        }
        return false;
    }
    bool InputReadersFromFile(){                         //通过文件输入
        ReaderNums=0;
        ReaderMgm.clear();
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\reader_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            while (!file.atEnd()){
                QByteArray line = file.readLine();
                QString str(line);
                string data=str.toStdString();
                string temp[20];
                int j = 0;
                for (int i = 0; data[i] != '\0'; i++) {
                    if (data[i] != '\t') {
                        temp[j] += data[i];
                    } else {
                        j++;
                        continue;
                    }
                }
                Reader newReader(atoll(temp[0].c_str()), atoi(temp[1].c_str()), temp[2], temp[3],atoi(temp[4].c_str()), atoi(temp[5].c_str()));
                AddReader(newReader);
            }
            file.close();  
        }
        return true;
    }
};


//index
