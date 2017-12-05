#include "recordclass.h"
#include<string.h>
#include<iostream>
#include<stdio.h>
#include "allx.h"
    Record::Record(char*bookid1, char*cardid1, int Year, int Month, int Day, char flag11, char flag22)
    {

        for (int i = 0; i < 10; i++)
        {
            bookid[i] = bookid1[i];
        }
        for (int i = 0; i < 10; i++)
        {
            cardid[i] = cardid1[i];
        }
        year = Year;
        month = Month;
        day = Day;
        flag1 = flag11;
        flag2 = flag22;
        //获取当前系统日期 自行查询方法 读入当前year month day
    }

    Record::Record(char*cardid1, int Year, int Month, int Day, int flag11)
    {
        for (int i = 0; i < 10; i++)
        {
            cardid[i] = cardid1[i];
        }
        year = Year;
        month = Month;
        day = Day;
        flag1 = flag11;
    }

    //刘峰同学需要的构造函数啦啦~~
    Record::Record(char*bookid1, char*cardid1, int Year, int Month, int Day, char flag11, char flag22, int Order)
    {
        for (int i = 0; i < 10; i++)
        {
            bookid[i] = bookid1[i];
        }
        for (int i = 0; i < 10; i++)
        {
            cardid[i] = cardid1[i];
        }
        year = Year;
        month = Month;
        day = Day;
        flag1 = flag11;
        flag2 = flag22;
        order = Order;
    }

    //默认构造函数
    Record::Record()
    {
        for (int i = 0; i < 10; i++)
        {
            bookid[i] = ' ';
        }
        for (int i = 0; i < 10; i++)
        {
            cardid[i] = ' ';
        }
        year = 0;
        month = 0;
        day = 0;
        flag2 = 1;//用于缓冲区   1对预约记录表示此预约失效并且已经写入记录文件 1对续借记录表示该书已续借
        order = 1;
        flag1 = '1';   //所有标记 0表示不存在 1表示存在//此处，1表示书可借
    }
    //复制构造函数
    Record::Record(Record &R)
    {
        for (int i = 0; i<10; i++)
        {
            bookid[i] = R.bookid[i];
        }
        for (int i = 0; i<10; i++)
        {
            cardid[i] = R.cardid[i];
        }
        year = R.year;
        month = R.month;
        day = R.day;
        flag2 = R.flag2;//用于缓冲区   1对预约记录表示此预约失效并且已经写入记录文件 1对续借记录表示该书已续借
        order = R.order;
        flag1 = R.flag1;
    }

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

    char Record::getflag1()
    {
        return flag1;
    }
    void Record::setflag1(char newflag1)
    {
        flag1 = newflag1;
    }
    int Record::getyear()
    {
        return year;
    }
    void Record::setyear(int newyear)
    {
        year = newyear;
    }
    int Record::getmonth()
    {
        return month;
    }
    void Record::setmonth(int newmonth)
    {
        month = newmonth;
    }
    int Record::getday()
    {
        return day;
    }
    void Record::setday(int newday)
    {
        day = newday;
    }
    char Record::getflag2()
    {
        return flag2;
    }
    void Record::setflag2(char newflag2)
    {
        flag2 = newflag2;
    }
    int Record::getorder()
    {
        return order;
    }
    void Record::setorder(int neworder)
    {
        order = neworder;
    }
    char* Record::getBookid()
    {
        return bookid;
    }
    char* Record::getCardid()
    {
        return cardid;
    }


    //Record类内部函数的实现

    //11.04增加一个日期变化的函数
    void Record::alter_Date(int addday)
    {
        int tempday = 0;
        int monthday[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//定义出每个月的天数以方便增加月
        if (isLeapYear(year))monthday[1] = 29;//闰年的2月
        else monthday[1] = 28;//非润年的2月
        tempday = day + addday;//通过减天数，加月数加年数的方法来获取新的日期
        while (tempday>monthday[month - 1])
        {
            tempday = tempday - monthday[month - 1];
            month++;
            if (month > 12)
            {
                month = month - 12;
                if (isLeapYear(++year))monthday[1] = 29;
                else monthday[1] = 28;
            }
        }
        day = tempday;
    }

    //11.7增加管理员改变书库存记录
    void Record::admininchangestorage()
    {
        FILE *fp_change_storage;
        FILE *fp_log;
        if (NULL == (fp_change_storage = fopen("ADMININ_CHANGE_STORAGE", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_change_storage, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_change_storage) != 1)	//这两处的this也是可以用的，指向的是一个Record对象
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_change_storage);
        fclose(fp_log);
    }

    //11.7增加管理员新增书目的记录
    void Record::admininaddbook()
    {
        FILE *fp_add_book;
        FILE *fp_log;
        if (NULL == (fp_add_book = fopen("ADMININ_ADD_BOOK", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_add_book, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_add_book) != 1)	//这两处也是可以用的，理由同上
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_add_book);
        fclose(fp_log);
    }

    //10.31借书记录

    void Record::bookLendRecord(int flag)        //借书记录
    {
        FILE *fp_book_lend;
        FILE *fp_log;
        FILE *fp_buffer;
        FILE *fp_order;
        FILE *fp_new_order;
        if (flag == 0)
        {
            if (NULL == (fp_book_lend = fopen("BOOK_LEND_RECORD", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (NULL == (fp_log = fopen("LOG", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            fseek(fp_book_lend, 0, SEEK_END);
            fseek(fp_log, 0, SEEK_END);
            fseek(fp_buffer, 0, SEEK_END);
            if (fwrite(this, sizeof(Record), 1, fp_book_lend) != 1)	//this可用
                printf("file write error\n");
            if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
                printf("file write error\n");
            if (fwrite(this, sizeof(Record), 1, fp_buffer) != 1)
                printf("file write error\n");
            fclose(fp_book_lend);
            fclose(fp_log);
            fclose(fp_buffer);
        }
        else if (flag == 1)
        {


            if (NULL == (fp_book_lend = fopen("BOOK_LEND_RECORD", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (NULL == (fp_log = fopen("LOG", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            fseek(fp_book_lend, 0, SEEK_END);
            fseek(fp_log, 0, SEEK_END);
            fseek(fp_buffer, 0, SEEK_END);
            if (fwrite(this, sizeof(Record), 1, fp_book_lend) != 1)
                printf("file write error\n");
            if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
                printf("file write error\n");
            if (fwrite(this, sizeof(Record), 1, fp_buffer) != 1)
                printf("file write error\n");
            fclose(fp_book_lend);
            fclose(fp_log);
            fclose(fp_buffer);

            if (NULL == (fp_order = fopen("BUFFERZONE_ORDER", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (NULL == (fp_new_order = fopen("bufferzone_ordernew", "wb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            Record record_temp;
            while (!feof(fp_order))
            {
                fread(&record_temp, sizeof(Record), 1, fp_order);
                if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid())continue;
                fwrite(&record_temp, sizeof(Record), 1, fp_new_order);
            }
            fclose(fp_order);
            fclose(fp_new_order);
            if (remove("BUFFERZONE_ORDER") != 0)exit(1);
            if (rename("bufferzone_ordernew", "BUFFERZONE_ORDER") != 0)exit(1);

        }

    }

    //11.1还书记录
    //向还书记录和大记录中写入一条还书记录，并在buffer文件中找出对应借书记录，将借书记录删除。
    void Record::bookReturnRecord()
    {
        FILE *fp_book_return;
        FILE *fp_log;
        FILE *fp_lend_buffer;
        FILE *fp_lend_buffernew;
        if (NULL == (fp_book_return = fopen("BOOK_RETURN_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_lend_buffer = fopen("BUFFERZONE_LEND", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_lend_buffernew = fopen("bufferzone_lendnew", "wb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        Record record_temp;
        while (!feof(fp_lend_buffer))
        {
            fread(&record_temp, sizeof(Record), 1, fp_lend_buffer);
            if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
            fwrite(&record_temp, sizeof(Record), 1, fp_lend_buffernew);
        }
        fclose(fp_lend_buffer);
        fclose(fp_lend_buffernew);
        if (remove("BUFFERZONE_LEND") != 0)exit(1);
        if (rename("bufferzone_lendnew", "BUFFERZONE_LEND") != 0)exit(1);
        fseek(fp_book_return, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_book_return) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_book_return);
        fclose(fp_log);

    }


    //11.1预约记录
    void Record::bookOrderRecord()
    {
        FILE *fp_book_order;
        FILE *fp_log;
        FILE *fp_buffer;
        if (NULL == (fp_book_order = fopen("BOOK_ORDER_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_buffer = fopen("BUFFERZONE_ORDER", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_book_order, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        fseek(fp_buffer, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_book_order) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_buffer) != 1)
            printf("file write error\n");
        fclose(fp_book_order);
        fclose(fp_log);
        fclose(fp_buffer);
    }

    //11.1取消预约记录
    void Record::bookOrderCancelRecord()
    {
        FILE *fp_book_order_cancel;
        FILE *fp_log;
        FILE *fp_order_buffer;
        FILE *fp_order_buffernew;
        if (NULL == (fp_book_order_cancel = fopen("BOOK_ORDER_CANCEL_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_order_buffer = fopen("BUFFERZONE_ORDER", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_order_buffernew = fopen("bufferzone_ordernew", "wb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        Record record_temp;
        while (!feof(fp_order_buffer))
        {
            fread(&record_temp, sizeof(Record), 1, fp_order_buffer);
            if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
            fwrite(&record_temp, sizeof(Record), 1, fp_order_buffernew);
        }
        fclose(fp_order_buffer);
        fclose(fp_order_buffernew);
        if (remove("BUFFERZONE_ORDER") != 0)exit(1);
        if (rename("bufferzone_ordernew", "BUFFERZONE_ORDER") != 0)exit(1);

        fseek(fp_book_order_cancel, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_book_order_cancel) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_book_order_cancel);
        fclose(fp_log);
    }

    //新增无记录删除功能的预约记录函数
    void Record::bookOrderNoRecord_new()
    {
        FILE *fp_book_order_no;
        FILE *fp_log;
        if (NULL == (fp_book_order_no = fopen("BOOK_ORDER_CANCEL_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_book_order_no, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_book_order_no) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_book_order_no);
        fclose(fp_log);
    }
    //11.1预约失效记录
    ///预约失效和取消预约的文件相同
    void Record::bookOrderNoRecord()
    {
        FILE *fp_book_order_cancel;
        FILE *fp_log;
        FILE *fp_noorder_buffer;
        FILE *fp_noorder_buffernew;
        if (NULL == (fp_book_order_cancel = fopen("BOOK_ORDER_CANCEL_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_noorder_buffer = fopen("BUFFERZONE_ORDER", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_noorder_buffernew = fopen("bufferzone_ordernew", "wb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        Record record_temp;
        while (!feof(fp_noorder_buffer))
        {
            fread(&record_temp, sizeof(Record), 1, fp_noorder_buffer);
            if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
            fwrite(&record_temp, sizeof(Record), 1, fp_noorder_buffernew);
        }
        fclose(fp_noorder_buffer);
        fclose(fp_noorder_buffernew);
        if (remove("BUFFERZONE_ORDER") != 0)exit(1);
        if (rename("bufferzone_lendnew", "BUFFERZONE_ORDER") != 0) exit(1);

        fseek(fp_book_order_cancel, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_book_order_cancel) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_book_order_cancel);
        fclose(fp_log);
    }


    //11.1续借记录
    //由于没有取消续借功能，所以续借只存放在续借文件和大日志文件中，并未存放在缓存文件中

    //续借也需要写到bufferlend缓冲文件里，因为还书的时候需要从bufferlend中检索出来
    //欧巴说的都对啦啦~~mua~~
    void Record::bookRenewRecord()
    {
        FILE *fp_book_renew;
        FILE *fp_log;
        FILE *fp_buffer;
        FILE *fp_new_buffer_lend;
        if (NULL == (fp_book_renew = fopen("BOOK_RENEW_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
        {
            fprintf(stderr, "Can not open file");
        }
        if (NULL == (fp_new_buffer_lend = fopen("bufferzone_lendnew", "wb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        Record record_temp;
        while (!feof(fp_buffer))
        {
            fread(&record_temp, sizeof(Record), 1, fp_buffer);
            if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
            fwrite(&record_temp, sizeof(Record), 1, fp_new_buffer_lend);
        }
        fclose(fp_buffer);
        fclose(fp_new_buffer_lend);
        if (remove("BUFFERZONE_LEND") != 0)exit(1);
        if (rename("bufferzone_lendnew", "BUFFERZONE_LEND") != 0)exit(1);
        if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
        {
            fprintf(stderr, "Can not open file");
        }
        fseek(fp_book_renew, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        fseek(fp_buffer, 0, SEEK_END);
        this->setflag1('d');
        if (fwrite(this, sizeof(Record), 1, fp_book_renew) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_buffer) != 1)
            printf("file write error\n");
        fclose(fp_book_renew);
        fclose(fp_log);
        fclose(fp_buffer);
    }

    //11.1登录记录
    //登录记录未存在缓存文件中
    void Record::signInRecord()
    {
        FILE *fp_sign_in;
        FILE *fp_log;
        if (NULL == (fp_sign_in = fopen("SIGN_IN_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_sign_in, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_sign_in) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_sign_in);
        fclose(fp_log);
    }

    //11.1注销记录
    //未记录在缓冲文件中
    void Record::signOutRecord()
    {
        FILE *fp_sign_out;
        FILE *fp_log;
        if (NULL == (fp_sign_out = fopen("SIGN_OUT_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_sign_out, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_sign_out) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_sign_out);
        fclose(fp_log);
    }

    //11.1注册记录
    //未放进缓冲文件中
    void Record::signUpRecord()
    {
        FILE *fp_sign_up;
        FILE *fp_log;
        if (NULL == (fp_sign_up = fopen("SIGN_UP_RECORD", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open file");
            exit(1);
        }
        fseek(fp_sign_up, 0, SEEK_END);
        fseek(fp_log, 0, SEEK_END);
        if (fwrite(this, sizeof(Record), 1, fp_sign_up) != 1)
            printf("file write error\n");
        if (fwrite(this, sizeof(Record), 1, fp_log) != 1)
            printf("file write error\n");
        fclose(fp_sign_up);
        fclose(fp_log);
    }

