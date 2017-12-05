#ifndef RECORDCLASS_H
#define RECORDCLASS_H

class Record
{
public:
    //10.30 构造函数更改
    Record(char*bookid1, char*cardid1, int Year, int Month, int Day, char flag11, char flag22);
    Record(char*cardid1, int Year, int Month, int Day, int flag11);
    //刘峰同学需要的构造函数啦啦~~
    Record(char*bookid1, char*cardid1, int Year, int Month, int Day, char flag11, char flag22, int Order);
    //默认构造函数
    Record();
    //复制构造函数
    Record(Record &R);

    void bookLendRecord(int flag);//借书记录
    void bookReturnRecord();//还书记录
    void bookOrderRecord();//预约记录
    void bookRenewRecord();//续借记录
    void bookOrderCancelRecord();//取消预约记录
    void bookOrderNoRecord_new();//失效情况下取消预约记录，专门用于update_order函数里
    void bookOrderNoRecord();//预约失效记录
    void signInRecord();//登陆记录
    void signOutRecord();//注销记录
    void signUpRecord();//注册记录
    void admininchangestorage();//管理员改变库存记录
    void admininaddbook();//管理员增加新书记录
    void alter_Date(int addday);//增加一个日期变化的函数

    char getflag1();
    void setflag1(char newflag1);
    int getyear();
    void setyear(int newyear);
    int getmonth();
    void setmonth(int newmonth);
    int getday();
    void setday(int newday);
    char getflag2();
    void setflag2(char newflag2);
    int getorder();
    void setorder(int neworder);
    char *getBookid();
    char *getCardid();

private:
    char flag1;  //a借书 b还书 c预约 d续借 e取消预约 f预约失效 g注册记录 h注销记录 i登陆记录 j管理员增加书 k管理员更改库存 l管理员注册
    char bookid[10];
    char cardid[10];
    int year;
    int month;
    int day;
    char flag2;//用于缓冲区   1对预约记录表示此预约失效并且已经写入记录文件 1对续借记录表示该书已续借
    int order;//标识第几本书
};

#endif // RECORDCLASS_H
