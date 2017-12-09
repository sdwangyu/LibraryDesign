#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <QWidget>

struct so_1
{
    int a;//记录长度or相似度
    int b;//记录数组下标
};
struct so_2
{
    double a;
    int b;
};
bool comp_1(const so_1 &x, const so_1 &y);
bool comp_2(const so_2 &x, const so_2 &y);
int isLeapYear(int year); //判断是否是闰年,返回1为闰年，返回0不是闰年
int compareDate(int year1, int month1, int day1, int year2, int month2, int day2);
int getDayInYear(int year, int month, int day) ;

class QPushButton;
class QLineEdit;

class Book//构造函数 复制构造函数
{
public:
    friend class Administrator;
    friend class Record;
    Book(char BookID[10], char BookName[100], char Author[50], char Publisher[50], char BOOKISBN[20], short Storage);
    Book();
    Book(Book &book); //复制构造函数
    char *getbookID();
    void setbookID(char newbookID[10]);
    char *getbookName();
    void setbookName(char newbookName[100]);
    char *getauthor();
    void setauthor(char newauthor[50]);
    char *getpublisher();
    void setpublisher(char newpublisher[50]);
    char *getbookisbn();
    void setbookisbn(char BOOKISBN[20]);
    short getstorage();
    void setstorage(short newstorage);
    void addstorage(short newstorage);
    short getbookMan();
    void setbookMan(short newbookMan);
    short gettStorage();
    void settStorage(short newStorage);
    char getflag();
    void setflag(char newflag);
    char *getBooks();
    //11.10 新增修改Books[i]的函数
    void setBooksI(int i, char newbooksi); //i表示第i本书，newbooksi表示新的Books[i]的值

private:
    char bookID[10];//图书编号
    char bookName[100];//书名
    char author[50];//作者
    char publisher[50];//出版商
    char bookisbn[20];
    short storage; //库存
    short bookMan; //预约人数
    short tStorage;  //临时库存
    char flag;  //图书是否存在
    char books[21]; //数组中每一项用来表示具体某一本的状态，0：损坏 1：可借 2：借出 3.表示初始化值，这本书还不可以用
    //动态开辟存储空间?
    //书籍库存上限为20
};

class Card//构造函数  复制构造函数
{
public:
    friend class Record;
    Card(char CardID[10], char CPassword[20], char CardHolder[10], double Balance, char CID[19], char CPhone[12]);
    Card(Card &card);//复制构造函数
    Card();
    char *getcardID();
    void setcardID(char newcardID[10]);
    char *getcPassword();
    void setcPassword(char newcPassword[20]);
    short getlendedCount();
    void setlendedCount(short newlendedCount);
    short getlendingCount();
    void setlendingCount(short newlendingCount);
    char *getcardHolder();
    void setcardHolder(char newcardHolder[10]);
    char getcardState();
    void setcardState(char newcardState);
    double getbalance();
    void setbalance(double newbalance);
    double getoweMoney();
    void setoweMoney(double newoweMoney);
    short getbookedCount();
    void setbookedCount(short newbookedCount);
    char *getcID();
    void setcID(char newcID[19]);
    char *getcPhone();
    void setcPhone(char newcPhone[12]);

private:
    char cardID[10];//卡号
    char cPassword[20];//密码
    short lendedCount;//已借本数（不能超过10）
    short lendingCount;//可借本数   （10-已借本数）
    char cardHolder[10];//持卡人姓名
    char cardState;   //账号冻结状态
    double balance;//余额
    double oweMoney;   //违约金
    short bookedCount;//已经预约的本数
    char cID[19];  //身份证号
    char cPhone[12];//持卡人手机号
};


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


class Administrator
{
public:
    //11.1构造函数
    Administrator(char Account[5], char APassword[20], char AccountHolder[10], char AID[19], char APhone[12]);//构造函数
    Administrator();
    //复制构造函数
    Administrator(Administrator &administrator);

    void setaccount(char newaccount[5]);
    void setaPassword(char newaPassword[20]);
    void setaccountHolder(char newaccountHolder[10]);
    void setaID(char newaID[19]);
    void setaPhone(char newaaPhone[12]);
    char *getaccount();
    char *getaPassword();
    char *getaccountHolder();
    char *getaID();
    char *getaPhone();

    int addBook(Book book);//增加书

    //void deleteBook(Book book);老师说不要删书
    //void operateCard(Card card);老师说不要删卡 听老师的
    //void findbook(char*bookid);        //为了在修改库存之前给类中的私有成员book赋值
    void newStorage(short storage);//新设库存
    int addadmin(char*aPassword, char*accountHolder, char*aID, char*aPhone);

    //11.9管理员所有查看行为函数
    void searchLog();//管理员查看大日志
    void searchLendBuffer();//管理员查看现在正借出的书
    void serchBookInformation();//管理员查看全部图书信息
    void searchCardInformation();//管理员查看全部用户信息
    void searchOrder();//管理员查看所有预约记录
    void searchCancleOrder();//管理员查看全部预约取消预约到期记录文件
    void searchReturn();//管理员查看所有还书信息


private:
    char account[5];        //记得修改上面对应得数值
    char aPassword[20];
    char accountHolder[10];
    char aID[19];
    char aPhone[12];
};

/*
class Library
{
public:
    Library();
    int signInUser(char*username_PutIn, char*password_PutIn);//用户登陆
    int signInAdmin(char*adminname_PutIn, char*password_PutIn);//管理员登陆
    void signUp(char*password, char*cardHolder, char*CID, char*CPhone);//用户注册
    void signOut();//用户注销
    void signOut_Admin();//管理员注销
    // void matchCid();//身份证ID匹配
    void ResetPassword(char*oldpassword, char*newpassword1, char*newpassword2);//输入新密码后重设密码写入原位置
    void update_Order();//函数用于用户进入系统时 对缓冲区进行更新
    void update_book();//函数用于在登陆后判断用户的已借书籍是否已经超期

    void charge(double money);//充值函数
    void Rcharge();//处理用户违约金
    // void resetCard();//更新修改卡信息 手机

    void Search(int select);//查询书本函数

    void deleteOrderFail();//删除orderbuffer中失效的预约记录
    void setbook(Book book1); //对需要操作的书进行赋值
    void bookLend();//直接进行的借书
    void bookLendOrder();//通过预约成功借书
    void bookReturn(Record record1);//还书
    void bookOrder();//预约
    void bookOrderCancel();//未到期的取消预约
    void bookRenew(Record record1);//续借

    Administrator getAdmin();

private:
    Book book;
    void on_userRegister_clicked();

Card card;
    Administrator admin;
};
*/

namespace Ui {
class LibrarySystem;
}

class LibrarySystem : public QWidget
{
    Q_OBJECT

public:
    explicit LibrarySystem(QWidget *parent = 0);
    ~LibrarySystem();

    int signInUser(char*username_PutIn, char*password_PutIn);//用户登陆
    int signInAdmin(char*adminname_PutIn, char*password_PutIn);//管理员登陆
    int signUp(char*password, char*cardHolder, char*CID, char*CPhone);//用户注册
    void signOut();//用户注销
    void signOut_Admin();//管理员注销
    // void matchCid();//身份证ID匹配
    void ResetPassword(char*oldpassword, char*newpassword1, char*newpassword2);//输入新密码后重设密码写入原位置
    void update_Order();//函数用于用户进入系统时 对缓冲区进行更新
    void update_book();//函数用于在登陆后判断用户的已借书籍是否已经超期

    void charge(double money);//充值函数
    void Rcharge();//处理用户违约金
    // void resetCard();//更新修改卡信息 手机

    void Search(int select);//查询书本函数

    void deleteOrderFail();//删除orderbuffer中失效的预约记录
    void setbook(Book book1); //对需要操作的书进行赋值
    void bookLend();//直接进行的借书
    void bookLendOrder();//通过预约成功借书
    void bookReturn(int recordyear,int recordmonth,int recordday,int recordorder);//还书
    void bookOrder();//预约
    void bookOrderCancel();//未到期的取消预约
    void bookRenew(Record record1);//续借

    Administrator getAdmin();

private slots:
    void on_searchokbutton_clicked();

    void on_userLogin_clicked();

    void on_registerAchieve_clicked();

    void on_userRegister_clicked();
    
    void on_chargeBtn_clicked();

    void on_chargeokBtn_clicked();

    void on_orderInfoBtn_clicked();

    void on_lendInfoBtn_clicked();

    void on_ordercancleBtn_clicked();

    void on_returnbookBtn_clicked();
    
    void on_booklendbutton_clicked();

    void on_searchBtn_clicked();

    void on_bookorderbutton_clicked();

    void on_userwindowinformation_clicked();

    void on_admininformationBtn_clicked();

    void on_registerExit_clicked();

    void on_lossPassword_clicked();

    void on_achievesetnewpassword_clicked();

    void on_submit_clicked();

    void on_setnewpasswordexit_clicked();

    void on_findbackpasswordexit_clicked();

    void on_userLogout_clicked();

    void on_adminLogout_clicked();

    void on_useraccount_editingFinished();

    void on_usernameget_editingFinished();

    void on_userpasswordget_editingFinished();

    void on_usersfznumbleget_editingFinished();

    void on_userphonenumbleget_editingFinished();

    void on_usernameget_textChanged(const QString &arg1);

    void on_usersfznumbleget_cursorPositionChanged(int arg1, int arg2);

    void on_userpasswordtwice_editingFinished();

    void on_setusernewpassword_editingFinished();

    void on_setusernewpasswordtwice_editingFinished();

    void on_addbookokBtn_clicked();

    void on_addbookBtn_clicked();

    void on_addadminBtn_clicked();

    void on_addadminokBtn_clicked();

    void on_looklogBtn_clicked();

    void setBtnQss(QPushButton *btn,
                   QString normalColor, QString normalTextColor,
                   QString hoverColor, QString hoverTextColor,
                   QString pressedColor, QString pressedTextColor);

    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);

    void UIDesign();

private:
    Ui::LibrarySystem *ui;
    Book book;
    Card card;
    Administrator admin;
};

#endif // LIBRARYSYSTEM_H
