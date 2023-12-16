#pragma once

#include "Admin.h"
#include <list>
#include <fstream>       //文件流
#include <QFileDialog>
#include "QTextStream"
using namespace std;

class AdminManagement{
private:
    list<Admin> AdminMgm;       //管理员列表（双向循环链表STL中的list）（数据成员为Admin对象）
    int AdminNums;              //管理员总数
public:
    AdminManagement(){          //从文件构造（文件输入操作）
        InputAdminsFromFile();
        AdminNums=static_cast<int>((AdminMgm.size()));
    }
    int get_AdminNums(){              //返回管理员数
        return AdminNums;
    }
    void AddAdmin(Admin &admin){      //新增管理员
        AdminMgm.push_front(admin);   //STL中list添加
        AdminNums++;
    }
    void DeleteAdmin(int acc){        //删除管理员（按账号查找删除）下面含重载
        Admin temp;
        FindAdmin(acc,temp);
        AdminMgm.remove(temp);
        AdminNums--;
    }
    void DeleteAdmin(Admin &admin){   //删除管理员（按对象删除）
        AdminMgm.remove(admin);
        AdminNums--;
    }
    void ModifyAdmin(Admin &oldAdmin, Admin &newAdmin){  //修改管理员
        DeleteAdmin(oldAdmin);
        AddAdmin(newAdmin);
    }
    bool FindAdmin(int account,Admin &ret){  //按账号查找
        //利用list迭代器遍历
        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            if (it->get_account() == account) {
                ret=*it;
                return true;
            }
        }
        return false;
    }
    bool FindAdmin(int account,Admin **ret){  //按账号查找
        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            if (it->get_account() == account) {
                *ret=&(*it);
                return true;
            }
        }
        return false;
    }
    Admin& get_Admin_ByIndex(int i){         //对管理员按索引访问
        list<Admin>::iterator it=AdminMgm.begin();
        while(i--)
            it++;
        return *it;
    }
    bool LoginAdmin(int acc,string pas){     //管理系统登陆
        Admin AdminToLogin;
        FindAdmin(acc,AdminToLogin);         //查找并赋值
        return AdminToLogin.Check(pas);      //利用对象属性判断
    }
    void ChangePas(Admin& ad,string pas){    //修改密码操作
        Admin newad=ad;
        newad.set_password(pas);
        ModifyAdmin(ad,newad);
    }
    bool OutputAdminsToFile(){               //将数据存储到文件（保存文件操作）
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\admin_data.txt");
        file.open(QIODevice::WriteOnly);     //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){  //Qt文件输出操作
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<Admin>::iterator it;
            for (it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
                stream << it->get_id() << "\t";
                stream << it->get_account() << "\t";
                stream << QString::fromStdString(it->get_name()) << "\t";
                stream << QString::fromStdString(it->get_password()) << "\t";
                stream << endl;
            }
            file.close();
        }
        return true;
    }
    bool InputAdminsFromFile(){              //从文件读取数据
        AdminNums=0;
        AdminMgm.clear();
        QFile file("E:\\Demo\\LibraryManagementByQt-master\\SourceCode\\Classes\\Data\\admin_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            while (!file.atEnd()){  //当文件指针未指向末尾时
                QByteArray line = file.readLine();
                QString data(line);
                //string data=str.toStdString();
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
                Admin newAdmin(temp[0].toInt(), temp[1].toInt(), temp[2].toStdString(), temp[3].toStdString());
                AddAdmin(newAdmin);
            }
            file.close();
        }
        return true;
    }
};

//index

