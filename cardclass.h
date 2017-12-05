#ifndef CARDCLASS_H
#define CARDCLASS_H


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


#endif // CARDCLASS_H
