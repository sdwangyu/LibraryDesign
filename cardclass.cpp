#include "cardclass.h"

    Card::Card(char CardID[10], char CPassword[20], char CardHolder[10], double Balance, char CID[19], char CPhone[12]) //构造函数
    {
        for (int i = 0; i<10; i++)
        {
            cardID[i] = CardID[i];
        }

        for (int i = 0; i<20; i++)
        {
            cPassword[i] = CPassword[i];
        }

        for (int i = 0; i<10; i++)
        {
            cardHolder[i] = CardHolder[i];
        }
        lendedCount = 0;//初始已借本数为0
        lendingCount = 10;//初始可借本数为10
        cardState = '1';//1表示未冻结
        balance = Balance;
        oweMoney = 0;
        bookedCount = 0;//初始预约本数为0
        for (int i = 0; i<19; i++)
        {
            cID[i] = CID[i];
        }
        for (int i = 0; i<12; i++)
        {
            cPhone[i] = CPhone[i];
        }
    }
    Card::Card(Card &card) //复制构造函数
    {
        for (int i = 0; i<10; i++)
        {
            cardID[i] = card.cardID[i];
        }
        for (int i = 0; i<20; i++)
        {
            cPassword[i] = card.cPassword[i];
        }
        lendedCount = card.lendedCount;
        lendingCount = card.lendingCount;
        for (int i = 0; i<10; i++)
        {
            cardHolder[i] = card.cardHolder[i];
        }
        cardState = card.cardState;
        balance = card.balance;
        oweMoney = card.oweMoney;
        bookedCount = card.bookedCount;
        for (int i = 0; i<19; i++)
        {
            cID[i] = card.cID[i];
        }
        for (int i = 0; i<12; i++)
        {
            cPhone[i] = card.cPhone[i];
        }
    }
    Card::Card()
    {
        int i = 0;
        for (i = 0; i<10; i++)
        {
            cardID[i] = ' ';
        }
        for (i = 0; i<20; i++)
        {
            cPassword[i] = ' ';
        }
        for (i = 0; i<10; i++)
        {
            cardHolder[i] = ' ';
        }
        balance = 0;
        for (i = 0; i<19; i++)
        {
            cID[i] = ' ';
        }
        for (i = 0; i<12; i++)
        {
            cPhone[i] = ' ';
        }
        lendedCount = 0;//初始已借本数为0
        lendingCount = 10;//初始可借本数为10
        cardState = '1';//1表示未冻结
        oweMoney = 0;
        bookedCount = 0;//初始预约本数为0
    }

    char* Card::getcardID()
    {
        return cardID;
    }
    void Card::setcardID(char newcardID[10])
    {
        for (int i = 0; i<10; i++)
        {
            cardID[i] = newcardID[i];
        }
    }
    char* Card::getcPassword()
    {
        return cPassword;
    }
    void Card::setcPassword(char newcPassword[20])
    {
        for (int i = 0; i<20; i++)
        {
            cPassword[i] = newcPassword[i];
        }
    }
    short Card::getlendedCount()
    {
        return lendedCount;
    }
    void Card::setlendedCount(short newlendedCount)
    {
        lendedCount = newlendedCount;
    }
    short Card::getlendingCount()
    {
        return lendingCount;
    }
    void Card::setlendingCount(short newlendingCount)
    {
        lendingCount = newlendingCount;
    }
    char* Card::getcardHolder()
    {
        return cardHolder;
    }
    void Card::setcardHolder(char newcardHolder[10])
    {
        for (int i = 0; i<10; i++)
        {
            cardHolder[i] = newcardHolder[i];
        }
    }
    char Card::getcardState()
    {
        return cardState;
    }
    void Card::setcardState(char newcardState)
    {
        cardState = newcardState;
    }
    double Card::getbalance()
    {
        return balance;
    }
    void Card::setbalance(double newbalance)
    {
        balance = newbalance;
    }
    double Card::getoweMoney()
    {
        return oweMoney;
    }
    void Card::setoweMoney(double newoweMoney)
    {
        oweMoney = newoweMoney;
    }
    short Card::getbookedCount()
    {
        return bookedCount;
    }
    void Card::setbookedCount(short newbookedCount)
    {
        bookedCount = newbookedCount;
    }
    char* Card::getcID()
    {
        return cID;
    }
    void Card::setcID(char newcID[19])
    {
        for (int i = 0; i<19; i++)
        {
            cID[i] = newcID[i];
        }
    }
    char* Card::getcPhone()
    {
        return cPhone;
    }
    void Card::setcPhone(char newcPhone[12])
    {
        for (int i = 0; i<12; i++)
        {
            cPhone[i] = newcPhone[i];
        }
    }
