#pragma once

#include <iostream>
#include <string.h>
#include <list>
using namespace std;

class Reader{
private:
    long long id;           //读者学号
    string name;            //读者姓名
    int account;            //读者证号（防止重名，提高健壮性）
    string password;        //读者账号密码
    int totalBorrowedBooks; //读者总借书次数
    int curBorrowedBooks;   //读者当前借书数量
public:
    //列表初始化（便于设置读者账号默认密码）
    Reader(long long id, int account, string name, string password="123456",int totalBorrowedBooks = 0, int curBorrowedBooks = 0): id(id), name(name), account(account),password(password), totalBorrowedBooks(totalBorrowedBooks), curBorrowedBooks(curBorrowedBooks) {}
    Reader() {}
    ~Reader() {}
    bool operator==(const Reader &reader)const {         //对"=="进行操作符重载
        if (account == reader.account)
            return true;
        else
            return false;
    }
    long long get_id(){     //获得读者学号
        return id;
    }
    int get_account(){      //获得读书证号
        return account;
    }
    string get_name(){      //获得读者姓名
        return name;
    }
    string get_password(){  //获得读者密码
        return password;
    }
    void set_password(string pas){  //设置读者密码
        password=pas;
    }
    int get_totalBorrowedBooks(){   //获得总共借书的数量
        return totalBorrowedBooks;
    }
    int get_curBorrowedBooks(){     //获得当前借了的书的数量
        return curBorrowedBooks;
    }
    bool Check(string pas){         //判断密码
        return pas==password;
    }
    void BorrowPermitted(){         //借阅通过审核，当前借书数量+1
        curBorrowedBooks++;
    }
    void ReturnPermitted(){         //还书申请通过，当前借书--，总借书++
        curBorrowedBooks--;
        totalBorrowedBooks++;
    }
    bool BorrrowAvailable(){        //检查是否有借书资格（规定借书不超过10本则继续借）
        return curBorrowedBooks<=10;
    }
};

//index
