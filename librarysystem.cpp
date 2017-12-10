#include "librarysystem.h"
#include "ui_librarysystem.h"
#include<QMessageBox>
#include <QTextStream>
#include <QTableWidgetItem>
#include <sstream>

using namespace std;

int allbook;
int allcard;
int alladmin;

int dmend;

int tcflag=1; //用于表示找回密码的时候是用户还是管理员
QRegExp hanzi("[\u4e00-\u9fa5]{1,3}");
QRegExp passwordstype("[A-Za-z0-9]{6,16}");
QRegExp sfztype("[0-9]{18}");
QRegExp phonetype("[0-9]{11}");
QRegExp shuming("[A-Za-z0-9\u4e00-\u9fa5]{1,30}");
QRegExp zuozhe("[A-Za-z0-9\u4e00-\u9fa5]{1,15}");
QRegExp isbntype("[A-Za-z0-9]{1,16}");

LibrarySystem::LibrarySystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibrarySystem)
{
    dmend=0;
    FILE *fp1;
    if ((fp1 = fopen("ALLNUM", "rb")) == NULL)
    {
        fprintf(stderr, "Can not open file allnum");
        exit(1);
    }
        fread(&allcard, sizeof(int), 1, fp1);
        fread(&allbook, sizeof(int), 1, fp1);
        fread(&alladmin, sizeof(int), 1, fp1);

        fclose(fp1);
    ui->setupUi(this);
    //ui->mainwidget->setCurrentIndex(0);

    this->UIDesign();

    //对于预约信息表只能选中一行的限定
    ui->orderInfotable->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->orderInfotable->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->orderInfotable->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置每行不可编辑

    //对于借阅信息表只能选中一行的限定
    ui->lendInfotable->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->lendInfotable->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->lendInfotable->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置每行不可编辑

		//对于查询结果表只能选中一行的限定
    ui->searchresult->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->searchresult->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->searchresult->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置每行不可编辑
    //ui->searchresult->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    //ui->searchresult->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->mainwidget->setCurrentIndex(0);
    ui->userpassword->setEchoMode(QLineEdit::Password);
    //QRegExp regExp("0|[1-9]\\d{0,4}");
    //ui->useraccount->setValidator(new QRegExpValidator(regExp, this));
    //QRegExp hanzi("[\u4e00-\u9fa5]{1,3}");
    //ui->usernameget->setValidator(new QRegExpValidator(hanzi, this));


}

LibrarySystem::~LibrarySystem()
{
    delete ui;
}


bool comp_1(const so_1 &x, const so_1 &y)
{
    return x.a < y.a;
}
bool comp_2(const so_2 &x, const so_2 &y)
{
    return x.a > y.a;
}

int isLeapYear(int year) //判断是否是闰年,返回1为闰年，返回0不是闰年
{
  if (year % 4 == 0 && year % 100 != 0)return 1;
  if (year % 400 == 0)return 1;
  return 0;
}

int getDayInYear(int year, int month, int day) //得到该日期是一年的第几天
{
    int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year))months[1] = 29;
    for (int i = 0; i<month - 1; i++)
    {
        day = day + months[i];
    }
    return day;
}

int compareDate(int year1, int month1, int day1, int year2, int month2, int day2) //日期比较,日期1year1month1day1-日期2year2month2day2,
{
    int days = 0;
    //不需要判断日期数字是否合理，系统日期不会出现32天的情况
    if (year1 == year2) //年份相等
    {
        if (month1 == month2)days = day1 - day2;//月份相等
        else days = getDayInYear(year1, month1, day1) - getDayInYear(year2, month2, day2);//月份不等
    }
    else  //年份不同，则日期差值为日期1的在year1的第几天+日期2在year2还剩下的天数+year1和year2两年之间的天数差值
    {
        //确保year1年份比year2晚
        if (year1 > year2)
        {
            if (isLeapYear(year2))
                days = 366 - getDayInYear(year2, month2, day2); //取得日期2在该年还剩下多少天
            else
                days = 365 - getDayInYear(year2, month2, day2);
            days += getDayInYear(year1, month1, day1); //取得日期1在当年中的第几天
            for (int year = year2 + 1; year < year1; year++)//取得year1和year2之间的天数差值
            {
                if (isLeapYear(year))
                    days += 366;
                else
                    days += 365;
            }
        }
        else days = -compareDate(year2, month2, day2, year1, month1, day1);    //date1小于date2的情况
    }
    // if(days<0)exit(0);//出错则退出程序
    return days;
}


Book::Book(char BookID[10], char BookName[100], char Author[50], char Publisher[50],char BOOKISBN[20], short Storage)//构造函数
    {

        for (int i = 0; i<10; i++)
        {
            bookID[i] = BookID[i];
        }
        for (int i = 0; i<100; i++)
        {
            bookName[i] = BookName[i];
        }
        for (int i = 0; i<50; i++)
        {
            author[i] = Author[i];
        }
        for (int i = 0; i<50; i++)
        {
            publisher[i] = Publisher[i];
        }
        for (int i = 0; i < 20 ; i++ )
        {
            bookisbn[i] = BOOKISBN[i];
        }
        memset(books, '3', sizeof(books));//把books全部初始化为3
        books[20] = '\0';
        if(Storage < 21)
        {
            storage = Storage;//初始库存为10本
            for(int i = 0; i < Storage; i++)
            {
                books[i] = '1';  //把前storage本书置为1 表示可借
            }
        }
        bookMan = 0;//初始预约人数为0
        tStorage = 0;//初始预约该书的人数为0
        flag = '1';   //所有标记 0表示不存在 1表示存在//此处，1表示书可借
        //books[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        //books = (int*)malloc(storage*sizeof(int));        //分配给该类书对应库存量的空间大小    在管理员修改库存的时候应该重新分配内存
    }
Book::Book()
    {
        for (int i = 0; i<10; i++)
        {
            bookID[i] = ' ';
        }
        for (int i = 0; i<100; i++)
        {
            bookName[i] = ' ';
        }
        for (int i = 0; i<50; i++)
        {
            author[i] = ' ';
        }
        for (int i = 0; i<50; i++)
        {
            publisher[i] = ' ';
        }
        for (int i = 0; i < 20 ; i++ )
        {
            bookisbn[i] = ' ';
        }
        memset(books, '3', sizeof(books));//把books全部初始化为3
        books[20] = '\0';
        storage = 0;//初始库存为10本
        bookMan = 0;//初始预约人数为0
        tStorage = 0;//初始预约该书的人数为0
        flag = '1';   //所有标记 0表示不存在 1表示存在//此处，1表示书可借
    }

Book::Book(Book &book) //复制构造函数
    {
        for (int i = 0; i<10; i++)
        {
            bookID[i] = book.bookID[i];
        }
        for (int i = 0; i<100; i++)
        {
            bookName[i] = book.bookName[i];
        }
        for (int i = 0; i<50; i++)
        {
            author[i] = book.author[i];
        }
        for (int i = 0; i<50; i++)
        {
            publisher[i] = book.publisher[i];
        }
        for (int i = 0; i < 20 ; i++ )
        {
            bookisbn[i] = book.bookisbn[i];
        }
        storage = book.storage;
        bookMan = book.bookMan;
        tStorage = book.tStorage;
        flag = book.flag;
        for (int i = 0; i < 21; i++)
        {
            books[i] = book.books[i];
        }
    }
char* Book::getbookID()
    {
        return bookID;
    }
void Book::setbookID(char newbookID[10])
    {
        for (int i = 0; i<10; i++)
        {
            bookID[i] = newbookID[i];
        }
    }
char* Book::getbookName()
    {
        return bookName;
    }
void Book::setbookName(char newbookName[100])
    {
        for (int i = 0; i<50; i++)
        {
            bookName[i] = newbookName[i];
        }
    }
char* Book::getauthor()
    {
        return author;
    }
void Book::setauthor(char newauthor[50])
    {
        for (int i = 0; i<50; i++)
        {
            author[i] = newauthor[i];
        }
    }
char* Book::getpublisher()
    {
        return publisher;
    }
void Book::setpublisher(char newpublisher[50])
    {
        for (int i = 0; i<50; i++)
        {
            publisher[i] = newpublisher[i];
        }
    }
char* Book::getbookisbn()
{
    return bookisbn;
}
void Book::setbookisbn(char BOOKISBN[20])
{
    for(int i=0;i < 20; i++)
    {
        bookisbn[i]=BOOKISBN[i];
    }
}
short Book::getstorage()
    {
        return storage;
    }
void Book::setstorage(short newstorage)
    {
        storage = newstorage;
    }
void Book::addstorage(short newstorage)
    {
        int i=0;
        while(books[i] != '3') i++; //i为目前的库存
        if(i + newstorage < 20) //如果增加库存后超过20 提示越界 拒绝修改
        {
            storage += newstorage; //新库存
            while(newstorage != 0)
            {
                books[i + newstorage - 1] = '1';
                newstorage--;
            }
        }
    }
short Book::getbookMan()
    {
        return bookMan;
    }
void Book::setbookMan(short newbookMan)
    {
        bookMan = newbookMan;
    }
short Book::gettStorage()
    {
        return tStorage;
    }
void Book::settStorage(short newStorage)
    {
        tStorage = newStorage;
    }
char Book::getflag()
    {
        return flag;
    }
void Book::setflag(char newflag)
    {
        flag = newflag;
    }
char* Book::getBooks()
    {
        return books;
    }
    //11.10 新增修改Books[i]的函数
void Book::setBooksI(int i, char newbooksi) //i表示第i本书，newbooksi表示新的Books[i]的值
    {
        books[i] = newbooksi;
    }


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

Administrator::Administrator(char Account[5], char APassword[20], char AccountHolder[10], char AID[19], char APhone[12])//构造函数
{

    for (int i = 0; i<5; i++)
    {
        account[i] = Account[i];
    }
    for (int i = 0; i<20; i++)
    {
        aPassword[i] = APassword[i];
    }
    for (int i = 0; i<10; i++)
    {
        accountHolder[i] = AccountHolder[i];
    }
    for (int i = 0; i<19; i++)
    {
        aID[i] = AID[i];
    }
    for (int i = 0; i < 12; i++)
    {
        aPhone[i] = APhone[i];
    }
    aID[18]='\0';
    aPhone[11]='\0';
}
Administrator::Administrator()
{
    for (int i = 0; i<5; i++)
    {
        account[i] = ' ';
    }
    for (int i = 0; i<20; i++)
    {
        aPassword[i] = ' ';
    }
    for (int i = 0; i<10; i++)
    {
        accountHolder[i] = ' ';
    }
    for (int i = 0; i<19; i++)
    {
        aID[i] = ' ';
    }
    for (int i = 0; i<12; i++)
    {
        aPhone[i] = ' ';
    }
    aID[18]='\0';
    aPhone[11]='\0';
}

//复制构造函数
Administrator::Administrator(Administrator &administrator)
{
    for (int i = 0; i<5; i++)
    {
        account[i] = administrator.account[i];
    }
    for (int i = 0; i<20; i++)
    {
        aPassword[i] = administrator.aPassword[i];
    }
    for (int i = 0; i<10; i++)
    {
        accountHolder[i] = administrator.accountHolder[i];
    }
    for (int i = 0; i<19; i++)
    {
        aID[i] = administrator.aID[i];
    }
    for (int i = 0; i<12; i++)
    {
        aPhone[i] = administrator.aPhone[i];
    }
}

void Administrator::setaccount(char newaccount[5])
{
    for (int i = 0; i<5; i++)
    {
        account[i] = newaccount[i];
    }
}

void Administrator::setaPassword(char newaPassword[20])
{
    for (int i = 0; i<20; i++)
    {
        aPassword[i] = newaPassword[i];
    }
}

void Administrator::setaccountHolder(char newaccountHolder[10])
{
    for (int i = 0; i<10; i++)
    {
        accountHolder[i] = newaccountHolder[i];
    }
}

void Administrator::setaID(char newaID[19])
{
    for (int i = 0; i<19; i++)
    {
        aID[i] = newaID[i];
    }
}
void Administrator::setaPhone(char newaaPhone[12])
{
    for (int i = 0; i<12; i++)
    {
        aPhone[i] = newaaPhone[i];
    }
}
char* Administrator::getaccount()
{
    return account;
}
char* Administrator::getaPassword()
{
    return aPassword;

}
char* Administrator::getaccountHolder()
{
    return accountHolder;
}
char* Administrator::getaID()
{
    return aID;
}
char* Administrator::getaPhone()
{
    return aPhone;
}


int Administrator::addadmin(char*aPassword, char*accountHolder, char*aID, char*aPhone)
{
    std::string account_str = std::to_string(2000 + alladmin + 1);
    char account[5];
    strcpy(account,account_str.c_str());
    int i = 0;
    Administrator newadministrator(account, aPassword, accountHolder, aID, aPhone);
    Administrator temp;
    FILE*fp_admin;
    if (NULL == (fp_admin = fopen("ADMININFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    while(i < alladmin)
    {
        fseek(fp_admin, i*sizeof(Administrator), SEEK_SET);
        fread(&temp, sizeof(Administrator), 1, fp_admin);
        if(newadministrator.getaID() == temp.getaID())return 0;
        i++;
    }
    fseek(fp_admin, 0, SEEK_END);
    if (fwrite(&newadministrator, sizeof(Administrator), 1, fp_admin) != 1)
        printf("file write error\n");
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(newadministrator.getaccount(), year, month, day, 'l');
    record.signUpRecord();
    fclose(fp_admin);
    alladmin++;
    FILE *fp_num;
    if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
        printf("file write error\n");
    if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    fclose(fp_num);
    return 1;
}


//管理员查看大日志
void Administrator::searchLog()
{
    FILE *fp_log;
    if (NULL == (fp_log = fopen("LOG", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }

}


//11.2管理员新加书函数
int Administrator::addBook(Book book)
{
    FILE *fp_add_book;
    FILE *fp_book;
    Book temp;
    int i = 0;
    if (NULL == (fp_add_book = fopen("ADMININ_ADD_BOOK", "rb+")))
    {
        fprintf(stderr, "Can not open admin_add_book");
        exit(1);
    }
    if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open bookinformation");
        exit(1);
    }
    while(i < allbook)
    {
        fseek(fp_book, i*sizeof(Book), SEEK_SET);
        fread(&temp, sizeof(Book), 1, fp_book);
        if(strcmp(temp.getbookisbn(), book.getbookisbn()) == 0)return 0;
        i++;
    }
    fseek(fp_add_book, 0, SEEK_END);
    fseek(fp_book, 0, SEEK_END);
    fwrite(&book, sizeof(Book), 1, fp_book);
    allbook++;
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(book.getbookID(), this->getaccount(), year, month, day, 'j', '0');		//这个this是可以用的，因为调用的时候指向的也是一个具体的Administrator对象
    record.admininaddbook();
    fclose(fp_add_book);
    fclose(fp_book);
    FILE *fp_num;
    if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
        printf("file write error\n");
    if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    fclose(fp_num);
    return 1;
}


void Administrator::newStorage(short addstor) //addstor是要增加的库存数目
{
    //修改库存时输入的值应该改成增加的量或者减少的量，不能直接输入最终的库存量
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month  = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Book book;
    char bookid[10];  //qt中向此处传入bookid表示要修改哪本书的库存
    //****cout << "请输入要修改书籍的id（9位）：" ;
    //****cin >> bookid;
    FILE *fp_book;
    if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(bookid) - 100000000 - 1;//书籍位置
    fseek(fp_book, position * sizeof(Book), SEEK_SET);//定位到这本书
    fread(&book, sizeof(Book), 1, fp_book);///取出这本书
    book.addstorage(addstor);//增加这本书的库存 addstor是要增加的数目
    Record record(book.getbookID(), this->getaccount(), year, month, day, 'k', '0');//写入记录	//这个this也是可以用的，理由同上
    record.admininchangestorage();
    fseek(fp_book, position * sizeof(Book), SEEK_SET);//重新定位
    if (fwrite(&book, sizeof(Book), 1, fp_book) != 1)//把修改完的book写回文件
        printf("file write error\n");
}


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
            fprintf(stderr, "Can not open booklendrecord");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "rb+")))
        {
            fprintf(stderr, "Can not open log");
            exit(1);
        }
        if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
        {
            fprintf(stderr, "Can not open bufferzonelend");
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
            fprintf(stderr, "Can not open booklendrecord");
            exit(1);
        }
        if (NULL == (fp_log = fopen("LOG", "wb+")))
        {
            fprintf(stderr, "Can not open log");
            exit(1);
        }
        if (NULL == (fp_buffer = fopen("BUFFERZONE_LEND", "rb+")))
        {
            fprintf(stderr, "Can not open bufferzonelend");
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
            fprintf(stderr, "Can not open BUFFERZONE_ORDER");
            exit(1);
        }
        if (NULL == (fp_new_order = fopen("BUFFERZONE_ORDERNEW", "rb+")))
        {
            fprintf(stderr, "Can not open BUFFERZONE_ORDERNEW");
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
        if(fread(&record_temp, sizeof(Record), 1, fp_lend_buffer)){
        if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
        fwrite(&record_temp, sizeof(Record), 1, fp_lend_buffernew);
        }
        else break;
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
        fprintf(stderr, "Can not open book_order_record");
        exit(1);
    }
    if (NULL == (fp_log = fopen("LOG", "rb+")))
    {
        fprintf(stderr, "Can not open log");
        exit(1);
    }
    if (NULL == (fp_buffer = fopen("BUFFERZONE_ORDER", "rb+")))
    {
        fprintf(stderr, "Can not open bufferzone_order");
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
        if(fread(&record_temp, sizeof(Record), 1, fp_order_buffer)){
        if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid())continue;
           fwrite(&record_temp, sizeof(Record), 1, fp_order_buffernew);
        }
        else
            break;

    }
    fclose(fp_order_buffer);
    fclose(fp_order_buffernew);
    //if (remove("BUFFERZONE_ORDER") != 0)exit(1);
    if (rename("BUFFERZONE_ORDER", "BUFFERZONE_ORDER_TEMP") != 0)exit(1);
    if (rename("bufferzone_ordernew", "BUFFERZONE_ORDER") != 0)exit(1);
    if (rename("BUFFERZONE_ORDER_TEMP", "bufferzone_ordernew") != 0)exit(1);

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
        if(fread(&record_temp, sizeof(Record), 1, fp_noorder_buffer)){
        if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
        fwrite(&record_temp, sizeof(Record), 1, fp_noorder_buffernew);
        }
        else break;
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
        if(fread(&record_temp, sizeof(Record), 1, fp_buffer)){
        if ((std::string)record_temp.getBookid() == (std::string)this->getBookid() && (std::string)record_temp.getCardid() == (std::string)this->getCardid() && record_temp.getorder() == this->getorder())continue;
        fwrite(&record_temp, sizeof(Record), 1, fp_new_buffer_lend);
        }
        else break;
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

void LibrarySystem::Search(int select) //select 1表示前方一致（书名） 2表示模糊查询（书名）3表示作者 4表示出版社
{
    FILE *fp1;
    FILE *fp2;
    Book tc;
    QString temp;
    temp = ui->searchtext->text();
    std::string str = temp.toStdString();
    const char* source = str.c_str();
    unsigned int i;
    int n = 0;
    unsigned int num = 0;
    if (NULL == (fp1 = fopen("BOOKINFORMATION", "rb")))
    {
        fprintf(stderr, "Can not open file bookInformation");
    }
    if (NULL == (fp2 = fopen("searchResult", "wb+")))
    {
        fprintf(stderr, "Can not open file searchResult");
    }
    if (select == 1)
    {
        std::vector<so_1> sou_1;
        sou_1.reserve(10000);
        while (n != allbook)
        {
            fread(&tc, sizeof(Book), 1, fp1);
            size_t position;
            std::string target = tc.getbookName();
            position = target.find(source);
            if (position == 0)
            {
                if (fwrite(&tc, sizeof(Book), 1, fp2) != 1)
                    printf("file write error\n");
                so_1 temp;
                temp.b = num;
                temp.a = strlen(tc.getbookName());
                sou_1.push_back(temp);
                num++;
            }
            n++;
        }
        //num 为查找出来的书籍总数量
        std::sort(sou_1.begin(), sou_1.end(), comp_1);
        Book abc;   //打印书的信息，测试的时候只打印前十本，方便测试
        for (i = 0; i < num; i++)
        {
            fseek(fp2, sou_1[i].b*sizeof(Book), 0);
            fread(&abc, sizeof(Book), 1, fp2);
            int row = ui->searchresult->rowCount();//增加一行操作
            ui->searchresult->insertRow(row);
            int nn = abc.getstorage();
            QString s = QString::number(nn, 10);
            ui->searchresult->setItem(row,0,new QTableWidgetItem(abc.getbookID()));
            ui->searchresult->setItem(row,1,new QTableWidgetItem(abc.getbookName()));
            ui->searchresult->setItem(row,2,new QTableWidgetItem(abc.getauthor()));
            ui->searchresult->setItem(row,3,new QTableWidgetItem(abc.getpublisher()));
            ui->searchresult->setItem(row,4,new QTableWidgetItem(abc.getbookisbn()));
            ui->searchresult->setItem(row,5,new QTableWidgetItem(s));
        }
        fclose(fp1);
        fclose(fp2);

    }
    else if (select == 2)
    {
        std::vector<so_2> sou_2;
        sou_2.reserve(10000);
        unsigned int j;
        while (n!= allbook)
        {
            char target[100];
            double same=0;
            double Jaccardindex=0;
            fread(&tc,sizeof(Book),1,fp1);
            strcpy(target,tc.getbookName());
            int d[100][100];
            memset(d,0,sizeof(d));
            int arraytarget[50];
            unsigned int arraytargetlength=0;//target数组长度
            for(i = 0; i < strlen(target); ++i)
            {
                int ch = target[i];
                if(ch < 0)
                {
                    //  使用unsigned char 读取可以获取128 - 255 之间的数值
                    unsigned char c = target[i];
                    int itemp = c;
                    // 范围选择170 - 254是为了去掉中文标点及其他字符，范围请参考汉字ASCII对照表
                    if(itemp >= 170 && itemp <= 254)
                    {
                        arraytarget[arraytargetlength]=target[i]*256+target[i+1];
                    }
                    // 此时（ch < 0）两个char表示一个汉字，所以跳过第二个char
                    ++i;
                    ++arraytargetlength;
                }
                else if( (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57))
                {
                    arraytarget[arraytargetlength]=ch;
                    arraytargetlength++;
                }
            }
            //source数组转换
            int arraysource[50];
            unsigned int arraysourcelength=0;//source数组长度
            for(i = 0; i < strlen(source); ++i)
            {
                int ch = source[i];
                if(ch < 0)
                {
                    //  使用unsigned char 读取可以获取128 - 255 之间的数值
                    unsigned char c = source[i];
                    int itemp = c;
                    // 范围选择170 - 254是为了去掉中文标点及其他字符，范围请参考汉字ASCII对照表
                    if(itemp >= 170 && itemp <= 254)
                    {
                        arraysource[arraysourcelength]=source[i]*256+source[i+1];
                    }
                    // 此时（ch < 0）两个char表示一个汉字，所以跳过第二个char
                    ++i;
                    ++arraysourcelength;
                }
                else if( (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57))
                {
                    arraysource[arraysourcelength]=ch;
                    arraysourcelength++;
                }
            }
            //计算相似度
            for(i = 0; i <= arraysourcelength; i++)
                d[i][0] = i;
            for(j = 0; j <= arraytargetlength; j++)
                d[0][j] = j;

            for(i = 1; i <= arraysourcelength; i++)
            {
                for(j = 1; j <= arraytargetlength; j++)
                {
                    if(arraysource[i - 1] == arraytarget[j - 1])
                    {
                        d[i][j] = d[i - 1][j - 1]; //不需要编辑操作
                        same=same+1;
                    }
                    else
                    {
                        int edIns = d[i][j - 1] + 1; //source 插入字符
                        int edDel = d[i - 1][j] + 1; //source 删除字符
                        int edRep = d[i - 1][j - 1] + 1; //source 替换字符
                        d[i][j] = std::min(std::min(edIns, edDel), edRep);
                    }
                }
            }
            Jaccardindex=same/(d[arraysourcelength][arraytargetlength]+same);
            if(Jaccardindex>0)
            {
                if(fwrite(&tc,sizeof(Book),1,fp2)!=1)
                    printf("file write error\n");
                so_2 temp;
                temp.b=num;
                temp.a=Jaccardindex;
                sou_2.push_back(temp);
                num++;
            }
            memset(target,0,100);
            n++;
        }
        std::sort(sou_2.begin(),sou_2.end(),comp_2);
        Book abc;
        for(i=0; i < num; i++)
        {
            fseek(fp2,sou_2[i].b*sizeof(Book),0);
            fread(&abc,sizeof(Book),1,fp2);
            int row = ui->searchresult->rowCount();//增加一行操作
            ui->searchresult->insertRow(row);
            int nn = abc.getstorage();
            QString s = QString::number(nn, 10);
            ui->searchresult->setItem(row,0,new QTableWidgetItem(abc.getbookID()));
            ui->searchresult->setItem(row,1,new QTableWidgetItem(abc.getbookName()));
            ui->searchresult->setItem(row,2,new QTableWidgetItem(abc.getauthor()));
            ui->searchresult->setItem(row,3,new QTableWidgetItem(abc.getpublisher()));
            ui->searchresult->setItem(row,4,new QTableWidgetItem(abc.getbookisbn()));
            ui->searchresult->setItem(row,5,new QTableWidgetItem(s));
        }
        fclose(fp1);
        fclose(fp2);
    }
    else
    {
        if (select == 3) //与作者进行匹配
        {
            while (n != allbook)
            {
                fread(&tc, sizeof(Book), 1, fp1);
                if (strcmp(source, tc.getauthor()) == 0)
                {
                    if (fwrite(&tc, sizeof(Book), 1, fp2) != 1)
                        printf("file write error\n");
                    int row = ui->searchresult->rowCount();//增加一行操作
                    ui->searchresult->insertRow(row);
                    int nn = tc.getstorage();
                    QString s = QString::number(nn, 10);
                    ui->searchresult->setItem(row,0,new QTableWidgetItem(tc.getbookID()));
                    ui->searchresult->setItem(row,1,new QTableWidgetItem(tc.getbookName()));
                    ui->searchresult->setItem(row,2,new QTableWidgetItem(tc.getauthor()));
                    ui->searchresult->setItem(row,3,new QTableWidgetItem(tc.getpublisher()));
                    ui->searchresult->setItem(row,4,new QTableWidgetItem(tc.getbookisbn()));
                    ui->searchresult->setItem(row,5,new QTableWidgetItem(s));
                    num++;
                }
                n++;
            }
        }
        if (select == 4) //与出版社进行匹配
        {
            while (n != allbook)
            {
                fread(&tc, sizeof(Book), 1, fp1);
                if (strcmp(source, tc.getpublisher()) == 0)
                {
                    if (fwrite(&tc, sizeof(Book), 1, fp2) != 1)
                        printf("file write error\n");
                    int row = ui->searchresult->rowCount();//增加一行操作
                    ui->searchresult->insertRow(row);
                    int nn = tc.getstorage();
                    QString s = QString::number(nn, 10);
                    ui->searchresult->setItem(row,0,new QTableWidgetItem(tc.getbookID()));
                    ui->searchresult->setItem(row,1,new QTableWidgetItem(tc.getbookName()));
                    ui->searchresult->setItem(row,2,new QTableWidgetItem(tc.getauthor()));
                    ui->searchresult->setItem(row,3,new QTableWidgetItem(tc.getpublisher()));
                    ui->searchresult->setItem(row,4,new QTableWidgetItem(tc.getbookisbn()));
                    ui->searchresult->setItem(row,5,new QTableWidgetItem(s));
                    num++;
                }
                n++;
            }
        }
        if (select == 5) //与出版社进行匹配
        {
            while (n != allbook)
            {
                fread(&tc, sizeof(Book), 1, fp1);
                if (strcmp(source, tc.getbookisbn()) == 0)
                {
                    if (fwrite(&tc, sizeof(Book), 1, fp2) != 1)
                        printf("file write error\n");
                    int row = ui->searchresult->rowCount();//增加一行操作
                    ui->searchresult->insertRow(row);
                    int nn = tc.getstorage();
                    QString s = QString::number(nn, 10);
                    ui->searchresult->setItem(row,0,new QTableWidgetItem(tc.getbookID()));
                    ui->searchresult->setItem(row,1,new QTableWidgetItem(tc.getbookName()));
                    ui->searchresult->setItem(row,2,new QTableWidgetItem(tc.getauthor()));
                    ui->searchresult->setItem(row,3,new QTableWidgetItem(tc.getpublisher()));
                    ui->searchresult->setItem(row,4,new QTableWidgetItem(tc.getbookisbn()));
                    ui->searchresult->setItem(row,5,new QTableWidgetItem(s));
                    num++;
                }
                n++;
            }
        }
        fclose(fp1);
        fclose(fp2);
    }
}
void LibrarySystem::bookLend() { //借书 1.直接借书
    if (card.getlendedCount() == 10) {//已借本数超过上限
        //cout << "可借本书已达到上限，无法再进行借阅！" << endl;
        QMessageBox::information(this, "Warning", "可借本书已达到上限，无法再进行借阅！");
    }
    else{//可借本数没有超过上限
        if (book.getstorage() > 1) { //库存允许
            //cout << "借阅成功" << endl;
            QMessageBox::information(this, "Success", "借阅成功");
            int order = 1;//标识第几本书
            char *q = book.getBooks();
            while (!(*(q + order) == '1')) {//从第一本书开始检索而不是第0本
                order++;
            }
            book.setBooksI(order, '2');//将这本书改为已借出
            book.setstorage(book.getstorage() - 1);//库存-1
            card.setlendedCount(card.getlendedCount() + 1);//已借本数+1
            card.setlendingCount(card.getlendingCount() - 1);//可借本数-1
            //生成一条借书的记录
            time_t timer;
            time(&timer);
            tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
            int year = t_tm->tm_year + 1900;
            int month = t_tm->tm_mon + 1;
            int day = t_tm->tm_mday;
            Record record(book.getbookID(), card.getcardID(), year, month, day, 'a', '0', order);//生成一条借书的记录
            record.alter_Date(30);    //加上30天，把应还日期写进记录
            record.bookLendRecord(0);
            //写回book文件
            FILE *fp_book;
            if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
            {
                fprintf(stderr, "Can not open bookinformation");
                exit(1);
            }
            int position = atoi(book.getbookID()) - 100000000 - 1;
            fseek(fp_book, position*sizeof(book), 0);
            if (fwrite(&book, sizeof(Book), 1, fp_book) != 1) {
                printf("file write error\n");
            }
            fclose(fp_book);
        }
        else { //库存不够
            //cout << "库存不够，借阅失败！" << endl;//借阅失败
            QMessageBox::information(this, "Warning", "库存不够，借阅失败");
            //cout << "是否进行预约？" << endl;
            //cout << "1.是   2.否" << endl;//提示框①
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Notice", "是否进行预约", QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes)bookOrder();
        }
    }
}

void LibrarySystem::bookLendOrder() {//2.通过预约成功借书
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    card.setlendedCount(card.getlendedCount() + 1);//已借本数+1
    card.setlendingCount(card.getlendingCount() - 1);//可借本数-1
    card.setbookedCount(card.getbookedCount() - 1);//人的预约本数-1

    book.setbookMan(book.getbookMan() - 1);//书的预约人数-1
    book.settStorage(book.gettStorage() - 1);//书的临时库存-1
    int order = 1;//标识第几本书
    char *q = book.getBooks();
    while (!(*(q + order) == '1')) {//从第一本书开始检索
        order++;
    }
    book.setBooksI(order, '2');//将这本书改为已借出
    //生成一条借书的记录
    Record record(book.getbookID(), card.getcardID(), year, month, day, 'a', '0', order);
    record.alter_Date(30);
    record.bookLendRecord(1);
    //写回book文件
    FILE *fp_book;
    if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(book.getbookID()) - 100000000 - 1;
    fseek(fp_book, position*sizeof(book), 0);
    if (fwrite(&book, sizeof(Book), 1, fp_book) != 1) {
        printf("file write error\n");
    }
    fclose(fp_book);
}

void LibrarySystem::bookReturn(int recordyear,int recordmonth,int recordday,int recordorder){ //还书（需要用到qt）
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    card.setlendedCount(card.getlendedCount() - 1);//已借本数-1
    card.setlendingCount(card.getlendingCount() + 1);//可借本数+1
    //1.检测这本书是否有人预约
    if (book.getbookMan()>0) {
        //1.1若有人预约
        if (book.gettStorage() == book.getbookMan()) {//检测临时库存是否等于预约人数，若等于则库存+1
            book.setstorage(book.getstorage() + 1);
        }
        else {//若不等于，临时库存+1
            book.settStorage(book.gettStorage() + 1);
        }
    }
    else {
        //1.2若无人预约，库存+1
        book.setstorage(book.getstorage() + 1);
    }
    //将order改为1可借
    book.setBooksI(recordorder,'1');
    //写回book文件
    FILE *fp_book;
    if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(book.getbookID()) - 100000000 - 1;
    fseek(fp_book, position*sizeof(book), 0);
    if (fwrite(&book, sizeof(Book), 1, fp_book) != 1) {
        printf("file write error\n");
    }
    fclose(fp_book);
    //生成一条还书记录
    Record record(book.getbookID(), card.getcardID(), year, month, day, 'b', '0',recordorder);
    record.bookReturnRecord();
    //用户超期处理
    if (!(compareDate(recordyear, recordmonth, recordday, year, month, day) > 0) )
    {
          double money = 0.5*compareDate(year, month, day, recordyear, recordmonth, recordday);
          card.setbalance(card.getbalance()-money);
          card.setoweMoney(card.getoweMoney()-money);
          QMessageBox::information(this, tr("提示"),tr("还书超期，扣除违约金%1元").arg(money));
    }
    QMessageBox::information(this, "提示", "还书成功");
}

void LibrarySystem::bookOrder(){//预约
    //预约记录就记录预约时间即可，因为为了方便在update_order里使用
    if(book.getstorage() > 2)QMessageBox::information(this, "Fail", "该书可以直接借阅！");
    else if (card.getbookedCount() == 5) {//预约本数已达上限
        //cout << "您的预约本数已达上限，无法进行预约！" << endl;
        QMessageBox::information(this, "Warning", "您的预约本数已达上限，无法进行预约！");
    }
    else{
        //cout << "预约成功！" << endl;//提示预约成功
        QMessageBox::information(this, "Success", "预约成功！");
        book.setbookMan(book.getbookMan() + 1);//书的预约人数+1
        card.setbookedCount(card.getbookedCount() + 1);//人的预约本数+1
        //写回book文件
        FILE *fp_book;
        if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
        {
            fprintf(stderr, "Can not open bookinformation");
            exit(1);
        }
        int position = atoi(book.getbookID()) - 100000000 - 1;
        fseek(fp_book, position*sizeof(book), 0);
        if (fwrite(&book, sizeof(Book), 1, fp_book) != 1) {
            printf("file write error\n");
        }
        fclose(fp_book);
        //生成一条预约记录
        time_t timer;
        time(&timer);
        tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
        int year = t_tm->tm_year + 1900;
        int month = t_tm->tm_mon + 1;
        int day = t_tm->tm_mday;
        Record record(book.getbookID(), card.getcardID(), year, month, day, 'c', '0');
        record.bookOrderRecord();
    }
}

void LibrarySystem::bookOrderCancel(){//取消预约 1.未到期取消预约
    if (book.getbookMan() == book.gettStorage()) { //若取消预约时临时库存等于预约人数
        book.settStorage(book.gettStorage() - 1);//临时库存-1
        book.setstorage(book.getstorage() + 1);//库存+1
    }
    book.setbookMan(book.getbookMan() - 1);//此书的预约人数-1
    card.setbookedCount(card.getbookedCount() - 1);//此人的预约数量-1
    //生成一条取消预约的记录
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(book.getbookID(), card.getcardID(), year, month, day, 'e', '0');
    record.bookOrderCancelRecord();
    //写回book文件
    FILE *fp_book;
    if (NULL == (fp_book = fopen("BOOKINFORMATION", "rb+")))
    {
        fprintf(stderr,"test cancleorder function!");
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(book.getbookID()) - 100000000 - 1;
    fseek(fp_book, position*sizeof(book), 0);
    if (fwrite(&book, sizeof(Book), 1, fp_book) != 1) {
        printf("file write error\n");
    }
    fclose(fp_book);
    QMessageBox::information(this, "提示", "取消预约成功");
}

void LibrarySystem::bookRenew(Record record1){//图书续借（需要用到qt）
   //获取借书的应还书时间
    int year = record1.getyear();
    int month = record1.getmonth();
    int day = record1.getday();
    Record record(book.getbookID(), card.getcardID(), year, month, day, 'd', '1',record1.getorder());
    //cout << "续借成功" << endl;
    QMessageBox::information(this, "Success", "续借成功！");
    record.alter_Date(30);        //加上30天，将应还日期写进记录
    record.bookRenewRecord();//生成一条续借记录
}

void LibrarySystem::deleteOrderFail() {//将预约缓冲区里已标记为1的记录删除
    FILE *fp_buffer;
    FILE *fp_new_buffer_order;
    if (NULL == (fp_buffer = fopen("BUFFERZONE_ORDER", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (NULL == (fp_new_buffer_order = fopen("bufferzone_ordernew", "wb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    Record record_temp;
    while (!feof(fp_buffer))
    {
        if(fread(&record_temp, sizeof(Record), 1, fp_buffer)){
        if (record_temp.getflag2()=='1' && (std::string)record_temp.getCardid() == (std::string)card.getcardID()) {        //只能删除当前用户失效的预约记录，所以应该判断这条记录的cardID和当前用户的cardID是否一致
            continue;
        }
        fwrite(&record_temp, sizeof(Record), 1, fp_new_buffer_order);
        }
        else break;
    }
    fclose(fp_buffer);
    fclose(fp_new_buffer_order);
    if (remove("BUFFERZONE_ORDER") != 0)exit(1);
    if (rename("bufferzone_ordernew", "BUFFERZONE_ORDER") != 0)exit(1);
}

int LibrarySystem::signInUser(char*username_PutIn, char*password_PutIn)         //用户登录
{
    //将用户输入的id和密码传到形参以便进行账号和密码的匹配
    //FILE*fpEnd = fopen("BOOKINFORMATION", "rb+");    //用于标志文件的末尾，以控制查找时的循环变量的控制。
    FILE *fpEnd = fopen("BOOKINFORMATION", "rb+");
     if (fpEnd == NULL) {
     printf("file error bookinformation\n");
     exit(1);
     }
     fseek(fpEnd, 0, SEEK_END);        //把fpEnd指针移到文件末尾
    //FILE *fp = fopen("CARDINFORMATION", "rb+");        //在循环时每一次往后移动的指针
    FILE *fp = fopen("CARDINFORMATION", "rb+");
    if (fp == NULL)
    {
        printf("file error cardinformation\n");
        exit(1);
    }
    Card card_find;
    Card card_temp;
    int i = 0;    //循环变量，用于将fp向后移动
    while (i<allcard)
    {
        fseek(fp, i * sizeof(Card), SEEK_SET);
        fread(&card_temp, sizeof(Card), 1, fp);
        if (strcmp(card_temp.getcardID(), username_PutIn) == 0)     //如果找到对应的card就用复制构造函数把找到的值赋值给一个暂时的变量card_find，以便于后面的密码匹配
        {
            card_find = card_temp;
            break;
        }
        i++;
    }
    if (strcmp(card_find.getcardID(), username_PutIn) == 0 && strcmp(card_find.getcPassword(), password_PutIn) == 0)
    {
        //账号和密码匹配成功后就可以登录成功了，然后就直接把查找到的card_find赋值给私有成员card
        card = card_find;
        time_t timer;
        time(&timer);
        tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
        int year = t_tm->tm_year + 1900;
        int month = t_tm->tm_mon + 1;
        int day = t_tm->tm_mday;
        Record record(card.getcardID(), year, month, day, 'i');
        record.signInRecord();
        fclose(fp);
        return 1;
    }
    else
    {
        fclose(fp);
        return 0;
    }

}

int LibrarySystem::signInAdmin(char*adminname_PutIn, char*password_PutIn)     //管理员登录
{
    //将管理员输入的id和密码传到形参以便进行账号和密码的匹配
     FILE*fpEnd = fopen("ADMININFORMATION", "rb+");    //用于标志文件的末尾，以控制查找时的循环变量的控制。
     if (fpEnd == NULL) {
     printf("file error\n");
     exit(1);
     }
     fseek(fpEnd, 0, SEEK_END);        //把fpEnd指针移到文件末尾
    FILE*fp = fopen("ADMININFORMATION", "rb+");        //在循环时每一次往后移动的指针
    if (fp == NULL)
    {
        printf("file error\n");
        exit(1);
    }
    Administrator admin_find;
    Administrator admin_temp;
    int i = 0;    //循环变量，用于将fp向后移动
    while (i<alladmin)
    {
        fseek(fp, i * sizeof(Administrator), SEEK_SET);
        fread(&admin_temp, sizeof(Administrator), 1, fp);
        if (strcmp(admin_temp.getaccount(), adminname_PutIn) == 0)     //如果找到对应的admin就用复制构造函数把找到的值赋值给一个暂时的变量admin_find，以便于后面的密码匹配
        {
            admin_find = admin_temp;
            break;
        }
        i++;
    }
    if (strcmp(admin_find.getaccount(), adminname_PutIn) == 0 && strcmp(admin_find.getaPassword(), password_PutIn) == 0)
    {
        //账号和密码匹配成功后就可以登录成功了，然后就直接把查找到的admin_find赋值给私有成员admin
        admin = admin_find;
        time_t timer;
        time(&timer);
        tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
        int year = t_tm->tm_year + 1900;
        int month = t_tm->tm_mon + 1;
        int day = t_tm->tm_mday;
        Record record(admin.getaccount(), year, month, day, 'i');
        record.signInRecord();
        fclose(fp);
        return 1;
    }
    else
    {
        fclose(fp);
        return 0;
    }
}

int LibrarySystem::signUp(char*password, char*cardHolder, char*CID, char*CPhone)     //用户注册
{
    std::string account_str = std::to_string(10000 + allcard + 1);
    char account[10];
    strcpy(account,account_str.c_str());
    Card newcard(account, password, cardHolder, 0, CID, CPhone);
    Card temp;
    int i = 0;
    FILE*fp_card;
    if (NULL == (fp_card = fopen("CARDINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open cardinformation");
        exit(1);
    }
    while(i < allcard)
    {
        fseek(fp_card, i*sizeof(Card), SEEK_SET);
        fread(&temp, sizeof(Card), 1, fp_card);
        if(strcmp(newcard.getcID(),temp.getcID()) == 0){
            return 0;
        }
        i++;
    }
    fseek(fp_card, 0, SEEK_END);
    if (fwrite(&newcard, sizeof(Card), 1, fp_card) != 1)
        printf("file write error\n");
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(newcard.getcardID(), year, month, day, 'g');
    record.signUpRecord();
    fclose(fp_card);
    allcard++;
    FILE *fp_num;
    if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
        printf("file write error\n");
    if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    fclose(fp_num);
    return 1;
}

void LibrarySystem::signOut()         //用户注销
{
    //把刚刚登录时获取的card写回文件原来的位置
    FILE*fp_card;
    if (NULL == (fp_card = fopen("CARDINFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(card.getcardID()) - 10000 - 1;
    fseek(fp_card, position*sizeof(Card), 0);
    if (fwrite(&card, sizeof(Card), 1, fp_card) != 1)
        printf("file write error\n");
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(card.getcardID(), year, month, day, 'h');
    record.signOutRecord();
    fclose(fp_card);
    //把card变量重新用无参的构造函数赋值，是否能用？
    Card card_blank;
    card = card_blank;
    //是否将allcard，allbook，alladmin写回文件？
    FILE *fp_num;
    if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
        printf("file write error\n");
    if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    fclose(fp_num);
    dmend=0;
    update_Order();
}

void LibrarySystem::signOut_Admin()         //管理员注销
{
    //把刚刚登录时获取的admin写回文件原来的位置
    FILE*fp_admin;
    if (NULL == (fp_admin = fopen("ADMININFORMATION", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    int position = atoi(card.getcardID()) - 2000 - 1;    //管理员账户格式2001
    fseek(fp_admin, position*sizeof(Administrator), 0);
    if (fwrite(&admin, sizeof(Administrator), 1, fp_admin) != 1)
        printf("file write error\n");
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    Record record(admin.getaccount(), year, month, day, 'h');
    record.signOutRecord();
    fclose(fp_admin);
    //同用户注销函数
    Administrator admin_blank;
    admin = admin_blank;
    //是否将allcard，allbook，alladmin写回文件？
    FILE *fp_num;
    if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
        printf("file write error\n");
    if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
        printf("file write error\n");
    fclose(fp_num);
    dmend=0;
    update_Order();
}


void LibrarySystem::ResetPassword(char*oldpassword, char*newpassword1, char*newpassword2)     //输入新密码后重设密码写入原位置
{
    if ((std::string)oldpassword == (std::string)card.getcPassword())
    {
        if ((std::string)newpassword1 == (std::string)newpassword2)
            card.setcPassword(newpassword1);
    }
    return;
}

void LibrarySystem::update_Order()             //函数用于用户进入系统时 对缓冲区进行更新
{

    FILE *fp_buffer_order;
    FILE *fp_bookInfo;
    FILE *fp_cardInfo;
    if ((fp_buffer_order = fopen("BUFFERZONE_ORDER", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if ((fp_bookInfo = fopen("BOOKINFORMATION", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    if ((fp_cardInfo = fopen("CARDINFORMATION", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    Record record_temp;
    Card card_temp;
    Book book_temp;
    time_t timer;
    time(&timer);
    tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
    int year = t_tm->tm_year + 1900;
    int month = t_tm->tm_mon + 1;
    int day = t_tm->tm_mday;
    int i = 0;
    while (!feof(fp_buffer_order)) //feof()函数可以用来判断文件是否到达文件尾，若到达文件尾，函数返回值为1
    {
        //cout << "------------------------" << endl;
        fseek(fp_buffer_order, i*sizeof(Record), SEEK_SET);
        if (fread(&record_temp, sizeof(Record), 1, fp_buffer_order)){
            //cout <<"***"<< record_temp.getCardid() << " " << record_temp.getBookid() << endl;
            if (compareDate(year, month, day, record_temp.getyear(), record_temp.getmonth(), record_temp.getday()) > 10)
            {
                //修改各个需要修改的变量,书的预约人数-1，比较书的临时库存和预约人数的大小，再对库存和临时库存做相应操作。用户的预约本数-1
                int position = atoi(record_temp.getBookid()) - 100000000 - 1;
                fseek(fp_bookInfo, position*sizeof(Book), SEEK_SET);
                fread(&book_temp, sizeof(Book), 1, fp_bookInfo);
                book_temp.setbookMan(book_temp.getbookMan() - 1);
                if (book_temp.getbookMan() < book_temp.gettStorage()) //预约人数小于临时库存
                {
                    //cout << "___" << book_temp.gettStorage() << " " << book_temp.getstorage();
                    book_temp.settStorage(book_temp.gettStorage() - 1);//临时库存-1
                    book_temp.setstorage(book_temp.getstorage() + 1);//库存+1
                }
                int size1 = sizeof(Book);
                fseek(fp_bookInfo, -size1, SEEK_CUR);
                if (fwrite(&book_temp, sizeof(Book), 1, fp_bookInfo) != 1)printf("file write error1\n");//修改文件中的内容

                position = atoi(record_temp.getCardid()) - 10000 - 1;
                fseek(fp_cardInfo, position*sizeof(Card), SEEK_SET);
                fread(&card_temp, sizeof(Card), 1, fp_cardInfo);
                card_temp.setbookedCount(card_temp.getbookedCount() - 1);//用户的预约本数减一
                int size2 = sizeof(Card);
                fseek(fp_cardInfo, -size2, SEEK_CUR);
                if (fwrite(&card_temp, sizeof(Card), 1, fp_cardInfo) != 1)printf("file write error2\n");//修改文件中的内容

                record_temp.setflag2('1');//1对预约记录表示此预约失效
                int size = sizeof(Record);
                fseek(fp_buffer_order, -size, SEEK_CUR);//由于fread函数使用后会使指针后移，所以在重写当前位置时要将指针向前移动一个单位，SEEK_CUR表示从当前位置
                if (fwrite(&record_temp, sizeof(Record), 1, fp_buffer_order) != 1)printf("file write error3\n");//更新预约缓冲文件
                //cout << "++++" << record_temp.getBookid() << " " << record_temp.getCardid() << endl;
                record_temp.setflag1('f');
                //record_temp.setyear(year);
                //record_temp.setmonth(month);
                //record_temp.setday(day);//将record_temp修改成一条预约失效记录
                record_temp.alter_Date(10);
                record_temp.bookOrderNoRecord_new();//调用函数写入失效记录文件
            }
        }
        i++;

    }
    fclose(fp_bookInfo);
    fclose(fp_cardInfo);
    fclose(fp_buffer_order);
    //cout << "更新成功！" << endl;
}

void LibrarySystem::update_book()         //函数用于在登录后判断用户的已借书籍是否已经超期
{
    FILE*fp_lendbuffer;
    if ((fp_lendbuffer = fopen("BUFFERZONE_LEND", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
        exit(1);
    }
    Record record_temp;        //用于读取借书buffer中的每一条记录
    int i = 0;
    fseek(fp_lendbuffer, i * sizeof(Record), SEEK_SET);
    card.setoweMoney(0);	//每次登陆时重新计算超期违约金
    while (!feof(fp_lendbuffer))
    {
        if (fread(&record_temp, sizeof(Record), 1, fp_lendbuffer)){
            if ((std::string)record_temp.getCardid() == (std::string)card.getcardID())
            {
                //确实是当前用户借阅并且未还的书籍
                //cout << record_temp.getBookid() << " " << record_temp.getCardid() << " " << record_temp.getyear() << " " << record_temp.getmonth() << " " << record_temp.getday() << " " << record_temp.getflag1() << " " << record_temp.getorder() << endl;
                time_t timer;
                time(&timer);
                tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
                int year = t_tm->tm_year + 1900;
                int month = t_tm->tm_mon + 1;
                int day = t_tm->tm_mday;
                //判断当前时间与应还日期
                if (!(compareDate(record_temp.getyear(), record_temp.getmonth(), record_temp.getday(), year, month, day) > 0))
                {
                    //如果当前日期超过还书日期，那么就进行违约金处理；

                    card.setoweMoney(card.getoweMoney() + 0.5*compareDate(year, month, day, record_temp.getyear(), record_temp.getmonth(), record_temp.getday()));//按超期一天0.5元计算
                    if (card.getbalance() < card.getoweMoney())card.setcardState('0');        //余额不足冻结账号
                    //cout << "违约金为：" << card.getoweMoney() << endl;
                }
            }
            //i++;
            //fseek(fp_lendbuffer, i * sizeof(Record), SEEK_SET);
            //cout << endl;
        }
    }
    fclose(fp_lendbuffer);
    //fclose(fp_End);
    //cout << "更新结束" << endl;
}

void LibrarySystem::charge(double money)             //充值函数
{
    card.setbalance(card.getbalance() + money);
    if (card.getbalance() > card.getoweMoney() && card.getcardState() == '0'){
        card.setcardState('1');
    }
}

void LibrarySystem::Rcharge()         //处理用户违约金
{
    double owemoney = card.getoweMoney();
    card.setbalance(card.getbalance() - owemoney);
}

void LibrarySystem::setbook(Book book1)
{//对需要操作的书进行赋值
    book = book1;
}


void LibrarySystem::on_userLogin_clicked()
{

    if(ui->useraccount->text().isEmpty()||ui->userpassword->text().isEmpty()){
        QMessageBox::information(this,"登录","用户名和密码不能为空.");
        ui->useraccount->clear();
        ui->useraccount->setFocus();
        ui->userpassword->clear();
        return;
    }
    //QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码."),QMessageBox::Ok);
    //对用户账号和密码的检查，*/
    /*FILE *fp1; //= fopen("ALLNUM", "rb");
    //if ((fp1 = fopen("ALLNUM", "rb")) == NULL)
    if ((fp1 = fopen("ALLNUM", "rb")) == NULL)
    {
        fprintf(stderr, "Can not open file allnum");
        exit(1);
    }
        fread(&allcard, sizeof(int), 1, fp1);
        fread(&allbook, sizeof(int), 1, fp1);
        fread(&alladmin, sizeof(int), 1, fp1);

        fclose(fp1);*/
        //QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码."),QMessageBox::Ok);
        //Library library1;
        //cout << "请输入账号：";
        //char username[10];
        //cin >> username;
        //cout << "请输入密码：";
        //char password[20];
        //cin >> password;
        //QString q_str("abc");
        //string = q_str.toStdString();
        //string std_str("abc");
        //char *str = std_str.c_str(std_str);
        /*QString usernamegets1=ui->usernameget->text();
        string usernamegets2;
        usernamegets2=usernamegets1.toStdString();
        char usernamegets[10];
        strcpy(usernamegets, usernamegets2.c_str());*/
        QString username1=ui->useraccount->text();
        string ba=username1.toStdString();
        char username[10];
        strcpy(username, ba.c_str());
        QString password1=ui->userpassword->text();
        string be=password1.toStdString();
        char password[20];
        strcpy(password, be.c_str());
        if(ui->loginforuser->isChecked()){
            if(signInUser(username, password)==1){
                ui->useraccount->clear();
                ui->useraccount->setFocus();
                ui->userpassword->clear();
                //隐藏登录对话框
                on_userwindowinformation_clicked();
                ui->mainwidget->setCurrentIndex(4);;//显示用户主窗口
            }
            else {
                QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码."),QMessageBox::Ok);
                //ui->useraccount->clear();
                ui->userpassword->clear();
                ui->userpassword->setFocus();
            }
            dmend=1;
            //对用户账号和密码的检查，
        }
        else if(ui->loginforadmin->isChecked()){
            if(signInAdmin(username, password)==1){
                ui->useraccount->clear();
                ui->useraccount->setFocus();
                ui->userpassword->clear();
                //隐藏登录对话框
                ui->mainwidget->setCurrentIndex(5);;//显示管理员主窗口
            }
            else {
                QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码."),QMessageBox::Ok);
                //ui->useraccount->clear();
                ui->userpassword->clear();
                ui->userpassword->setFocus();

            }
            //对用户账号和密码的检查，
            dmend=2;
        }
        ui->inputbookname1warning->setText(tr("1到30个字符，汉字、字母、数字"));
        ui->inputauthor1warning->setText(tr("1到15个字符，汉字、字母、数字"));
        ui->inputpublisher1warning->setText(tr("1到15个字符，汉字、字母、数字"));
        ui->inputisbn1warning->setText(tr("1到16位数字或字母，区分大小写"));
        ui->inputstorage1warning->setText(tr("库位1到20"));
        ui->inputadminname1warning->setText(tr("1到3位汉字"));
        ui->inputadminpass1warning->setText(tr("6到16位数字或字母，区分大小写"));
        ui->inputadminpasstwice1warning->setText(tr("请再次填写密码"));
        ui->inputadmincid1warning->setText(tr("忘记密码时，可以通过该身份证号码快速找回密码"));
        ui->inputadminphone1warning->setText(tr("方便我们联系您"));
        ui->inputadminpass1->setEchoMode(QLineEdit::Password);
        ui->inputadminpasstwice1->setEchoMode(QLineEdit::Password);
        update_book();
        update_Order();

}

//用户注册
void LibrarySystem::on_registerAchieve_clicked()
{


    /*QString usernamegets1=ui->usernameget->text();
    string usernamegets2;
    usernamegets2=usernamegets1.toStdString();
    char usernamegets[10];
    strcpy(usernamegets, usernamegets2.c_str());*/
    ui->useraccount->setFocus();
    if(ui->usernameget->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入用户名.");
        return;
    }
    else if(ui->userpasswordget->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入密码.");
        ui->userpasswordget->setFocus();
        return;
    }
    else if(ui->userpasswordtwice->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请确认密码.");
        ui->userpasswordtwice->setFocus();
        return;
    }
    else if(ui->usersfznumbleget->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入身份证号.");
        ui->usersfznumbleget->setFocus();
        return;
    }
    else if(ui->userphonenumbleget->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入手机号.");
        ui->userphonenumbleget->setFocus();
        return;
    }

    QRegExpValidator validator(hanzi,0);
    int pos = 0;
    QString dongman=ui->usernameget->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        QMessageBox::information(this,"用户名输入错误","请输入1~3个汉字.");
        return;
     }
    QRegExpValidator validator1(passwordstype,0);
    pos = 0;
    QString userpasswordgetstype=ui->userpasswordget->text();
    if(QValidator::Acceptable!=validator1.validate(userpasswordgetstype,pos)){
        QMessageBox::information(this,"密码输入错误","请输入6到16位数字或字母，区分大小写.");
        return;
     }

    QString userpasswordgets1=ui->userpasswordget->text();
    string ba1=userpasswordgets1.toStdString();
    char userpasswordgets[20];
    strcpy(userpasswordgets, ba1.c_str());
    QString userpasswordtwice1=ui->userpasswordtwice->text();
    string ba4=userpasswordtwice1.toStdString();
    char userpasswordtwice[20];
    strcpy(userpasswordtwice, ba4.c_str());
    if (strcmp(userpasswordgets,userpasswordtwice) == 0){
        QRegExpValidator validator2(sfztype,0);
        pos = 0;
        QString usersfznumblegetstype=ui->usersfznumbleget->text();
        if(QValidator::Acceptable!=validator2.validate(usersfznumblegetstype,pos)){
            QMessageBox::information(this,"身份证号输入错误","请输入正确的身份证号.");
            return;
         }
        QRegExpValidator validator3(phonetype,0);
        pos = 0;
        QString userphonenumblegetstype=ui->userphonenumbleget->text();
        if(QValidator::Acceptable!=validator3.validate(userphonenumblegetstype,pos)){
            QMessageBox::information(this,"手机号输入错误","请输入正确的手机号.");
            return;
         }

        QString usernamegets1=ui->usernameget->text();
        string ba=usernamegets1.toStdString();
        char usernamegets[10];
        strcpy(usernamegets, ba.c_str());

        QString usersfznumblegets1=ui->usersfznumbleget->text();
        string ba2=usersfznumblegets1.toStdString();
        char usersfznumblegets[19];
        strcpy(usersfznumblegets, ba2.c_str());


        QString userphonenumblegets1=ui->userphonenumbleget->text();
        string ba3=userphonenumblegets1.toStdString();
        char userphonenumblegets[12];
        strcpy(userphonenumblegets, ba3.c_str());

        if(signUp(userpasswordgets,usernamegets,usersfznumblegets,userphonenumblegets)==0){
            QMessageBox::information(this,"注册失败","该身份证号已被注册.");
            return;
        }
        QMessageBox::information(this,"注册","注册成功.");
        //隐藏注册窗口
        ui->usernameget->clear();
        ui->userpasswordget->clear();
        ui->userpasswordtwice->clear();
        ui->usersfznumbleget->clear();
        ui->userphonenumbleget->clear();
        ui->mainwidget->setCurrentIndex(0);//显示用户主窗口//发射显示登录对话框信号
        //注意判断是否为空,存储数据，转至登录界面
        QString newuseraccount;
        newuseraccount=QString::number(10000+allcard);
        ui->useraccount->setText(newuseraccount);
        ui->userpassword->setFocus();
    }
    else {
        ui->userpasswordget->clear();
        ui->userpasswordget->setFocus();
        ui->userpasswordtwice->clear();
        QMessageBox::information(this,"确认密码错误","请再次输入密码并确认.");
    }

}

//充值界面
void LibrarySystem::on_chargeBtn_clicked()
{
    ui->userwidget->setCurrentIndex(5);
    //以下内容用于限定充值时输入金额的大小
    QRegExp rx("^[1-9][0-9]?[0-9]?[0-9]?$");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(rx, this);
    ui->chargetext->setValidator(pRevalidotor);//限定输入内容为正则表达式^[1-9][0-9][0-9][0-9][0-9]$的形式
}

void LibrarySystem::on_chargeokBtn_clicked()
{


    if(ui->chargetext->text().isEmpty()){//判断充值金额是否为空
        QMessageBox::warning(this,tr("充值"),tr("充值金额不能为空."));
        ui->chargetext->clear();
        return;
    }
    else {
        QString chargemoney=ui->chargetext->text();
        int chargeintmoney=0;
        chargeintmoney=chargemoney.toInt();
        charge(chargeintmoney);
        QMessageBox::information(this,tr("充值"),tr("充值成功."));
        ui->chargetext->clear();
        return;
    }
    this->hide();
}


void LibrarySystem::on_orderInfoBtn_clicked()
{
    ui->userwidget->setCurrentIndex(3);
    ui->orderInfotable->setRowCount(0);
    ui->orderInfotable->clearContents();
    FILE*fp_orderbuffer=NULL,*fp_book=NULL;
    Book book_temp;//用于读取每条借书记录对应的书的信息
    Record record_temp;        //用于读取借书buffer中的每一条记录
    if ((fp_book = fopen("BOOKINFORMATION", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
         exit(1);
    }
    if ((fp_orderbuffer = fopen("BUFFERZONE_ORDER", "rb+")) == NULL)
    {
       fprintf(stderr, "Can not open file");
       exit(1);
    }
    //向预约表格中写入数据
    int orderInforow=0;//对应写入某一行
    QString year,month,day,date,interval;//用于将int型的日期转换为QString类型
    char charinterval='-';
    interval=QString(charinterval);//将日期间隔-转换为QString类型
    while (!feof(fp_orderbuffer))
    {
        if (fread(&record_temp, sizeof(Record), 1, fp_orderbuffer))
        {
            if ((std::string)record_temp.getCardid() == (std::string)card.getcardID())
            {
                orderInforow=ui->orderInfotable->rowCount();//获取当前即将要操作的行的编号
                ui->orderInfotable->insertRow(orderInforow);//向表格中添加一行
                int position = atoi(record_temp.getBookid()) - 100000000 - 1;//用于定位到书籍的位置
                fseek(fp_book, position*sizeof(Book), SEEK_SET);//定位到某一本书
                fread(&book_temp, sizeof(Book), 1, fp_book);//读取这本书
                //日期格式转换
                year=QString::number(record_temp.getyear());
                month=QString::number(record_temp.getmonth());
                day=QString::number(record_temp.getday());
                date=year+interval+month+interval+day;
                //写入表格
                ui->orderInfotable->setItem(orderInforow,0,new QTableWidgetItem(record_temp.getBookid()));
                ui->orderInfotable->setItem(orderInforow,1,new QTableWidgetItem(book_temp.getbookName()));
                ui->orderInfotable->setItem(orderInforow,2,new QTableWidgetItem(date));
            }
        }
    }
    fclose(fp_book);
    fclose(fp_orderbuffer);
}

void LibrarySystem::on_searchokbutton_clicked()
{
    ui->searchresult->setRowCount(0);
    ui->searchresult->clearContents();
    if(ui->searchtext->text().isEmpty())
            QMessageBox::warning(this, "Warning", "请输入查询内容！");
    else if(ui->bookname1->isChecked())Search(1);
    else if(ui->bookname2->isChecked())Search(2);
    else if(ui->author->isChecked())Search(3);
    else if(ui->publisher->isChecked())Search(4);
    else if(ui->ISBN->isChecked())Search(5);
}

//用户点击注册
void LibrarySystem::on_userRegister_clicked()
{
    ui->useraccount->clear();
    ui->usernameget->setFocus();
    ui->userpassword->clear();
    ui->mainwidget->setCurrentIndex(1);
    ui->usernamewarning->setText(tr("1到3位汉字"));
    ui->userpasswordwarning->setText(tr("6到16位数字或字母，区分大小写"));
    ui->userpasswordtwicewaring->setText(tr("请再次填写密码"));
    ui->usersfzhwarning->setText(tr("忘记密码时，可以通过该身份证号码快速找回密码"));
    ui->userphonenumblewarning->setText(tr("方便我们联系您"));
    ui->userpasswordget->setEchoMode(QLineEdit::Password);
    ui->userpasswordtwice->setEchoMode(QLineEdit::Password);
}

void LibrarySystem::on_lendInfoBtn_clicked()
{
    ui->userwidget->setCurrentIndex(4);
    ui->lendInfotable->setRowCount(0);
    ui->lendInfotable->clearContents();
    FILE*fp_lendbuffer=NULL,*fp_book=NULL;
    Book book_temp;//用于读取每条借书记录对应的书的信息
    Record record_temp;        //用于读取借书buffer中的每一条记录
    if ((fp_book = fopen("BOOKINFORMATION", "rb+")) == NULL)
    {
        fprintf(stderr, "Can not open file");
         exit(1);
    }
    if ((fp_lendbuffer = fopen("BUFFERZONE_LEND", "rb+")) == NULL)
    {
       fprintf(stderr, "Can not open file");
       exit(1);
    }
    //向预约表格中写入数据
    int lendInforow=0;//对应写入某一行
    QString year,month,day,bookorder;//用于将int型的日期转换为QString类型.以及10本书中第几本书的序号转换为QString类型
    while (!feof(fp_lendbuffer))
    {
        if (fread(&record_temp, sizeof(Record), 1, fp_lendbuffer))
        {
            if ((std::string)record_temp.getCardid() == (std::string)card.getcardID())
            {
                lendInforow=ui->lendInfotable->rowCount();//获取当前即将要操作的行的编号
                ui->lendInfotable->insertRow(lendInforow);//向表格中添加一行
                int position = atoi(record_temp.getBookid()) - 100000000 - 1;//用于定位到书籍的位置
                fseek(fp_book, position*sizeof(Book), SEEK_SET);//定位到某一本书
                fread(&book_temp, sizeof(Book), 1, fp_book);//读取这本书
                //日期格式转换
                year=QString::number(record_temp.getyear());
                month=QString::number(record_temp.getmonth());
                day=QString::number(record_temp.getday());
               // date=year+interval+month+interval+day;
                bookorder=QString::number(record_temp.getorder());
                //写入表格,将日期分开写方便还书时使用日期
                ui->lendInfotable->setItem(lendInforow,0,new QTableWidgetItem(record_temp.getBookid()));
                ui->lendInfotable->setItem(lendInforow,1,new QTableWidgetItem(book_temp.getbookName()));
                ui->lendInfotable->setItem(lendInforow,2,new QTableWidgetItem(year));
                ui->lendInfotable->setItem(lendInforow,3,new QTableWidgetItem(month));
                ui->lendInfotable->setItem(lendInforow,4,new QTableWidgetItem(day));
                ui->lendInfotable->setItem(lendInforow,5,new QTableWidgetItem(bookorder));
            }
        }
    }
    fclose(fp_book);
    fclose(fp_lendbuffer);
}

void LibrarySystem::on_ordercancleBtn_clicked()
{
    bool focus = ui->orderInfotable->isItemSelected(ui->orderInfotable->currentItem());//用于判断当前是否有行被选中
    if(focus==true)
    {
        QMessageBox mess(QMessageBox::Information,tr("取消预约"),tr("确定要取消本条预约吗？"));
        QPushButton *okbutton = (mess.addButton(tr("确定"),QMessageBox::AcceptRole));
        QPushButton *canclebutton=(mess.addButton(tr("取消"),QMessageBox::RejectRole));
        mess.exec();
        if(mess.clickedButton()==okbutton)//确认取消预约
        {
            int selectrow = ui->orderInfotable->currentRow();//获取当前选中的行号
            QString str = ui->orderInfotable->item(selectrow,0)->text();//获取某行某列单元格的文本内容
            int position = str.toInt() - 100000001;//QString转int
            FILE *fp_book=NULL;
            if ((fp_book = fopen("BOOKINFORMATION", "rb+")) == NULL)
            {
                fprintf(stderr, "Can not open file");
                 exit(1);
            }
            fseek(fp_book, position*sizeof(Book), SEEK_SET);//定位到某一本书
            fread(&book, sizeof(Book), 1, fp_book);//读取这本书到公用的book
            //调用取消预约的函数
            bookOrderCancel();
            fclose(fp_book);
        }
        if(mess.clickedButton()==canclebutton)return;//取消取消预约则返回
    }
    else
    {
        QMessageBox::warning(this,tr("提示"),tr("请先选中对应预约信息."));
    }
}

void LibrarySystem::on_returnbookBtn_clicked()
{
  bool focus = ui->lendInfotable->isItemSelected(ui->lendInfotable->currentItem());//用于判断当前是否有行被选中
    if(focus==true)
    {
        QMessageBox mess(QMessageBox::Information,tr("还书"),tr("确定要还书吗？"));
        QPushButton *okbutton = (mess.addButton(tr("确定"),QMessageBox::AcceptRole));
        QPushButton *canclebutton=(mess.addButton(tr("取消"),QMessageBox::RejectRole));
        mess.exec();
        if(mess.clickedButton()==okbutton)//确认还书
        {
            int selectrow = ui->lendInfotable->currentRow();//获取当前选中的行号
            QString strid = ui->lendInfotable->item(selectrow,0)->text();//获取某行某列单元格的文本内容,
            int position = strid.toInt() - 100000001;//QString转int
            FILE *fp_book=NULL;
            if ((fp_book = fopen("BOOKINFORMATION", "rb+")) == NULL)
            {
                fprintf(stderr, "Can not open file");
                 exit(1);
            }
            fseek(fp_book, position*sizeof(Book), SEEK_SET);//定位到某一本书
            fread(&book, sizeof(Book), 1, fp_book);//读取这本书到公用的book
            //调用还书的函数
            QString stryear = ui->lendInfotable->item(selectrow,2)->text();//获取某行某列单元格的文本内容,
            int recordy = stryear.toInt();//记录中的日期的年
            QString strmonth = ui->lendInfotable->item(selectrow,3)->text();//获取某行某列单元格的文本内容,
            int recordm = strmonth.toInt();//记录中日期的月
            QString strday = ui->lendInfotable->item(selectrow,4)->text();//获取某行某列单元格的文本内容,
            int recordd = strday.toInt();//记录中日期的日
            QString strorder = ui->lendInfotable->item(selectrow,5)->text();//获取某行某列单元格的文本内容,
            int recordo = strorder.toInt();//记录中书的序号
            bookReturn(recordy,recordm,recordd,recordo);
        }
        if(mess.clickedButton()==canclebutton)return;//取消还书则返回
    }
    else
    {
        QMessageBox::warning(this,tr("提示"),tr("请先选中对应借书信息."));
    }
}

void LibrarySystem::on_booklendbutton_clicked()
{
    bool focus = ui->searchresult->isItemSelected(ui->searchresult->currentItem());
    if(focus == true)
    {
    int row = ui->searchresult->currentRow();//获取当前选中的行号
    QString str = ui->searchresult->item(row,0)->text();//获取某行某列单元格的文本内容
    int bookid = str.toInt() - 100000001;//QString转int
    FILE *fp;
    if (NULL == (fp = fopen("BOOKINFORMATION", "rb")))
    {
        fprintf(stderr, "Can not open file bookInformation");
    }
    fseek(fp, bookid*sizeof(Book), SEEK_SET);
    if (fread(&book, sizeof(Book), 1, fp) != 1)
        printf("file write error\n");
    fclose(fp);
    bookLend();
    ui->searchresult->setRowCount(0);
    ui->searchresult->clearContents();
    if(ui->bookname1->isChecked())Search(1);
    else if(ui->bookname2->isChecked())Search(2);
    else if(ui->author->isChecked())Search(3);
    else if(ui->publisher->isChecked())Search(4);
    //ui->searchtext->clear();
    }
    else QMessageBox::warning(this,tr("提示"),tr("请先选中要借阅的书籍."));
}

void LibrarySystem::on_searchBtn_clicked()
{
    ui->searchtext->clear();
    ui->searchtext->setFocus();
    ui->searchresult->setRowCount(0);
    ui->searchresult->clearContents();
    ui->userwidget->setCurrentIndex(2);
}

void LibrarySystem::on_bookorderbutton_clicked()
{
    bool focus = ui->searchresult->isItemSelected(ui->searchresult->currentItem());
    if(focus == true)
    {
    int row = ui->searchresult->currentRow();//获取当前选中的行号
    QString str = ui->searchresult->item(row,0)->text();//获取某行某列单元格的文本内容
    int bookid = str.toInt() - 100000001;//QString转int
    FILE *fp;
    if (NULL == (fp = fopen("BOOKINFORMATION", "rb")))
    {
        fprintf(stderr, "Can not open file bookInformation");
    }
    fseek(fp, bookid*sizeof(Book), SEEK_SET);
    if (fread(&book, sizeof(Book), 1, fp) != 1)
        printf("file write error\n");
    fclose(fp);
    bookOrder();
    //ui->searchtext->clear();
    }
    else QMessageBox::warning(this,tr("提示"),tr("请先选中要预约的书籍."));
}

void LibrarySystem::on_userwindowinformation_clicked()
{
    ui->userwidget->setCurrentIndex(0);
    ui->username1->setText(card.getcardHolder());
    ui->userid1->setText(card.getcardID());
    ui->usercid1->setText(card.getcID());
    QString temp = QString::number(card.getlendedCount(),10);
    ui->lendednum1->setText(temp);
    temp.setNum(card.getlendingCount());
    ui->lendingnum1->setText(temp);
    temp.setNum(card.getbookedCount());
    ui->ordernum1->setText(temp);
    temp.setNum(card.getbalance());
    ui->usermoney1->setText(temp);
    temp.setNum(card.getoweMoney());
    ui->userowemoney1->setText(temp);
    if(card.getcardState() == '1')     ui->userstate1->setText("可用");
        else ui->userstate1->setText("冻结");
}


void LibrarySystem::on_admininformationBtn_clicked()
{
    ui->adminwidget->setCurrentIndex(1);
    ui->adminname1->setText(admin.getaccountHolder());
    ui->adminid1->setText(admin.getaccount());
    ui->admincid1->setText(admin.getaID());
    ui->adminphone1->setText(admin.getaPhone());
}
//用户退出注册
void LibrarySystem::on_registerExit_clicked()
{
    ui->usernameget->clear();
    ui->useraccount->setFocus();
    ui->userpasswordget->clear();
    ui->userpasswordtwice->clear();
    ui->usersfznumbleget->clear();
    ui->userphonenumbleget->clear();
    ui->mainwidget->setCurrentIndex(0);//清空内容并返回登录界面
}

//忘记密码
void LibrarySystem::on_lossPassword_clicked()
{
    ui->useraccount->clear();
    ui->findbackuseraccount->setFocus();
    ui->userpassword->clear();
    ui->mainwidget->setCurrentIndex(2);
}

//用户找回密码
void LibrarySystem::on_submit_clicked()
{
    /*FILE *fp1;
    if ((fp1 = fopen("ALLNUM", "rb")) == NULL)
    {
        fprintf(stderr, "Can not open file allnum");
        exit(1);
    }
        fread(&allcard, sizeof(int), 1, fp1);
        fread(&allbook, sizeof(int), 1, fp1);
        fread(&alladmin, sizeof(int), 1, fp1);

        fclose(fp1);*/
    if(ui->findbackuseraccount->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入用户名.");
        ui->findbackuseraccount->setFocus();
        return;
    }
    else if(ui->findbackusersfznumble->text().isEmpty()){
        QMessageBox::information(this,"输入错误","请输入身份证号码.");
        ui->findbackusersfznumble->setFocus();
        return;
    }
    QString findbackuseraccount1=ui->findbackuseraccount->text();
    string ba1=findbackuseraccount1.toStdString();
    char findbackuseraccount2[10];
    strcpy(findbackuseraccount2, ba1.c_str());
    QString findbackusersfznumble1=ui->findbackusersfznumble->text();
    string ba2=findbackusersfznumble1.toStdString();
    char findbackusersfznumble2[19];
    strcpy(findbackusersfznumble2, ba2.c_str());

    //将用户输入的id和身份证号进行匹配
    //FILE*fpEnd = fopen("BOOKINFORMATION", "rb+");    //用于标志文件的末尾，以控制查找时的循环变量的控制。
    /*FILE *fpEnd = fopen("BOOKINFORMATION", "rb+");
     if (fpEnd == NULL) {
     printf("file error bookinformation\n");
     exit(1);
     }
     fseek(fpEnd, 0, SEEK_END);        //把fpEnd指针移到文件末尾*/
    //我注释掉了，感觉没啥用
    //FILE *fp = fopen("CARDINFORMATION", "rb+");        //在循环时每一次往后移动的指针
    FILE *fp = fopen("CARDINFORMATION", "rb+");
    if (fp == NULL)
    {
        printf("file error cardinformation\n");
        exit(1);
    }

    FILE *fp2 = fopen("ADMININFORMATION", "rb+");
    if (fp2 == NULL)
    {
        printf("file error admininformation\n");
        exit(1);
    }
    Card card_find;
    Card card_temp;
    Administrator administrator_find;
    Administrator administrator_temp;
    int i = 0;    //循环变量，用于将fp向后移动
    int j =0;
    while (i<allcard)
    {
        fseek(fp, i * sizeof(Card), SEEK_SET);
        fread(&card_temp, sizeof(Card), 1, fp);
        if (strcmp(card_temp.getcardID(), findbackuseraccount2) == 0)     //如果找到对应的card就用复制构造函数把找到的值赋值给一个暂时的变量card_find，以便于后面的身份证号匹配
        {
            tcflag=1;
            card_find = card_temp;
            break;
        }
        i++;
    }
    while (j<alladmin)
    {
        fseek(fp2, j * sizeof(Administrator), SEEK_SET);
        fread(&administrator_temp, sizeof(Administrator), 1, fp2);
        if (strcmp(administrator_temp.getaccount(), findbackuseraccount2) == 0)     //如果找到对应的card就用复制构造函数把找到的值赋值给一个暂时的变量card_find，以便于后面的身份证号匹配
        {
            tcflag=2;
            administrator_find = administrator_temp;
            break;
        }
        j++;
    }
    if(tcflag==1){
        if (strcmp(card_find.getcardID(), findbackuseraccount2) == 0 && strcmp(card_find.getcID(), findbackusersfznumble2) == 0)
        {
            //账号和身份证号匹配成功后就可以设置密码了，然后就直接把查找到的card_find赋值给私有成员card
            card = card_find;
            fclose(fp);
            ui->findbackuseraccount->clear();
            ui->findbackuseraccount->setFocus();
            ui->findbackusersfznumble->clear();
            ui->mainwidget->setCurrentIndex(3);//转到设置新密码界面
        }
        else
        {
            fclose(fp);
            //ui->findbackuseraccount->clear();
            ui->findbackusersfznumble->clear();
            ui->findbackusersfznumble->setFocus();

            QMessageBox::information(this,"输入错误","请输入正确的身份证号.");
        }
    }
    else if(tcflag==2){
        if (strcmp(administrator_find.getaccount(), findbackuseraccount2) == 0 && strcmp(administrator_find.getaID(), findbackusersfznumble2) == 0)
        {
            //账号和身份证号匹配成功后就可以设置密码了，然后就直接把查找到的card_find赋值给私有成员card
            admin = administrator_find;
            fclose(fp2);
            ui->findbackuseraccount->clear();
            ui->findbackuseraccount->setFocus();
            ui->findbackusersfznumble->clear();
            ui->mainwidget->setCurrentIndex(3);//转到设置新密码界面
        }
        else
        {
            fclose(fp2);
            //ui->findbackuseraccount->clear();
            ui->findbackusersfznumble->clear();
            ui->findbackusersfznumble->setFocus();
            QMessageBox::information(this,"输入错误","请输入正确的身份证号.");
        }
    }
    ui->setnewpasswordwarning->setText(tr("6到16位数字或字母，区分大小写"));
    ui->setnewpasswordtwicewarning->setText(tr("请再次填写密码"));
    ui->setusernewpassword->setEchoMode(QLineEdit::Password);
    ui->setusernewpasswordtwice->setEchoMode(QLineEdit::Password);
}

//重新设置密码
void LibrarySystem::on_achievesetnewpassword_clicked()
{
    QString setusernewpassword1=ui->setusernewpassword->text();
    string ba1=setusernewpassword1.toStdString();
    char setusernewpassword2[20];
    strcpy(setusernewpassword2, ba1.c_str());

    QString setusernewpasswordtwice1=ui->setusernewpasswordtwice->text();
    string ba2=setusernewpasswordtwice1.toStdString();
    char setusernewpasswordtwice2[20];
    strcpy(setusernewpasswordtwice2, ba2.c_str());
    QRegExpValidator validator(passwordstype,0);
    int pos = 0;
    QString setusernewpasswordstype=ui->setusernewpassword->text();
    if(QValidator::Acceptable!=validator.validate(setusernewpasswordstype,pos)){
        QMessageBox::information(this,"密码输入错误","请输入6到16位数字或字母，区分大小写.");
        return;
     }
    if (strcmp(setusernewpassword2,setusernewpasswordtwice2) == 0)
    {
        if(tcflag==1){
            card.setcPassword(setusernewpassword2);
            //把刚刚时获设置密码获取的card写回文件原来的位置
            FILE*fp_card;
            if (NULL == (fp_card = fopen("CARDINFORMATION", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            int position = atoi(card.getcardID()) - 10000 - 1;
            fseek(fp_card, position*sizeof(Card), 0);
            if (fwrite(&card, sizeof(Card), 1, fp_card) != 1)
                printf("file write error\n");
            /*time_t timer;
            time(&timer);
            tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
            int year = t_tm->tm_year + 1900;
            int month = month = t_tm->tm_mon + 1;
            int day = t_tm->tm_mday;
            Record record(card.getcardID(), year, month, day, 'h');
            record.signOutRecord();*/
            fclose(fp_card);
            //把card变量重新用无参的构造函数赋值，是否能用？
            Card card_blank;
            card = card_blank;
            /*//是否将allcard，allbook，alladmin写回文件？
            FILE *fp_num;
            if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
                printf("file write error\n");
            if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
                printf("file write error\n");
            if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
                printf("file write error\n");
            fclose(fp_num);*/

        }
        else if(tcflag==2){
            admin.setaPassword(setusernewpassword2);
            //把刚刚时获设置密码获取的admin写回文件原来的位置
            FILE*fp_admin;
            if (NULL == (fp_admin = fopen("ADMININFORMATION", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            int position = atoi(admin.getaccount()) - 10000 - 1;
            fseek(fp_admin, position*sizeof(Administrator), 0);
            if (fwrite(&admin, sizeof(Administrator), 1, fp_admin) != 1)
                printf("file write error\n");
            /*time_t timer;
            time(&timer);
            tm* t_tm = localtime(&timer);    //获取了当前时间，并且转换为int类型的year，month，day
            int year = t_tm->tm_year + 1900;
            int month = month = t_tm->tm_mon + 1;
            int day = t_tm->tm_mday;
            Record record(card.getcardID(), year, month, day, 'h');
            record.signOutRecord();*/
            fclose(fp_admin);
            //把card变量重新用无参的构造函数赋值，是否能用？
            Administrator administrator_blank;
            admin = administrator_blank;
            /*//是否将allcard，allbook，alladmin写回文件？
            FILE *fp_num;
            if (NULL == (fp_num = fopen("ALLNUM", "rb+")))
            {
                fprintf(stderr, "Can not open file");
                exit(1);
            }
            if (fwrite(&allcard, sizeof(int), 1, fp_num) != 1)            //覆盖写入?
                printf("file write error\n");
            if (fwrite(&allbook, sizeof(int), 1, fp_num) != 1)
                printf("file write error\n");
            if (fwrite(&alladmin, sizeof(int), 1, fp_num) != 1)
                printf("file write error\n");
            fclose(fp_num);*/

        }
         ui->setusernewpassword->clear();
         ui->useraccount->setFocus();
         ui->setusernewpasswordtwice->clear();
         ui->mainwidget->setCurrentIndex(0);//转到设置登录界面
    }
    else {
         QMessageBox::information(this,"输入错误","请确认密码.");
         ui->setusernewpassword->clear();
         ui->setusernewpassword->setFocus();
         ui->setusernewpasswordtwice->clear();
    }

}

void LibrarySystem::on_setnewpasswordexit_clicked()
{
    //把card变量重新用无参的构造函数赋值，是否能用？
    Card card_blank;
    card = card_blank;
    ui->setusernewpassword->clear();
    ui->useraccount->setFocus();
    ui->setusernewpasswordtwice->clear();
    ui->mainwidget->setCurrentIndex(0);//转到设置登录界面
}

void LibrarySystem::on_findbackpasswordexit_clicked()
{
    //把card变量重新用无参的构造函数赋值，是否能用？
    Card card_blank;
    card = card_blank;
    ui->findbackuseraccount->clear();
    ui->useraccount->setFocus();
    ui->findbackusersfznumble->clear();
    ui->mainwidget->setCurrentIndex(0);//转到设置登录界面
}

//用户注销
void LibrarySystem::on_userLogout_clicked()
{
    signOut();
    ui->mainwidget->setCurrentIndex(0);//转到设置登录界面
}

void LibrarySystem::on_adminLogout_clicked()
{
    signOut_Admin();
    ui->mainwidget->setCurrentIndex(0);//转到设置登录界面
}

void LibrarySystem::on_useraccount_editingFinished()
{
    /*QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(reg,0);
    int pos = 0;
    QString dongman=ui->useraccount->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        QMessageBox::information(this,"输入错误","请输入数字.");
     }*/
}

void LibrarySystem::on_usernameget_editingFinished()
{
    if(ui->usernameget->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(hanzi,0);
    int pos = 0;
    QString dongman=ui->usernameget->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->usernamewarning->setText(tr("输入错误,请输入1到3位汉字"));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->usernamewarning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_userpasswordget_editingFinished()
{
    if(ui->userpasswordget->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(passwordstype,0);
    int pos = 0;
    QString userpasswordgetstype=ui->userpasswordget->text();
    if(QValidator::Acceptable!=validator.validate(userpasswordgetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->userpasswordwarning->setText(tr("输入错误,请输入6到16位数字或字母，区分大小写"));
     }
    else if(QValidator::Acceptable==validator.validate(userpasswordgetstype,pos)){
        ui->userpasswordwarning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_usersfznumbleget_editingFinished()
{
    if(ui->usersfznumbleget->text().isEmpty()){
        return;
    }
    QRegExpValidator validator(sfztype,0);
    int pos = 0;
    QString usersfznumblegetstype=ui->usersfznumbleget->text();
    if(QValidator::Acceptable!=validator.validate(usersfznumblegetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->usersfzhwarning->setText(tr("输入错误,请输入正确18位身份证号"));
     }
    else if(QValidator::Acceptable==validator.validate(usersfznumblegetstype,pos)){
        ui->usersfzhwarning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_userphonenumbleget_editingFinished()
{
    if(ui->userphonenumbleget->text().isEmpty()){
        return;
    }
    QRegExpValidator validator(phonetype,0);
    int pos = 0;
    QString userphonenumblegetstype=ui->userphonenumbleget->text();
    if(QValidator::Acceptable!=validator.validate(userphonenumblegetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->userphonenumblewarning->setText(tr("输入错误,请输入正确11位手机号"));
     }
    else if(QValidator::Acceptable==validator.validate(userphonenumblegetstype,pos)){
        ui->userphonenumblewarning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_userpasswordtwice_editingFinished()
{
    if(ui->userpasswordtwice->text().isEmpty()){
        return;
    }
    QString userpasswordgets1=ui->userpasswordget->text();
    string ba1=userpasswordgets1.toStdString();
    char userpasswordgets[20];
    strcpy(userpasswordgets, ba1.c_str());
    QString userpasswordtwice1=ui->userpasswordtwice->text();
    string ba4=userpasswordtwice1.toStdString();
    char userpasswordtwice[20];
    strcpy(userpasswordtwice, ba4.c_str());
    if (strcmp(userpasswordgets,userpasswordtwice) == 0){
        ui->userpasswordtwicewaring->setText(tr("输入成功"));
    }
    else {
        ui->userpasswordtwicewaring->setText(tr("两次密码不相同"));
    }
}

void LibrarySystem::on_setusernewpassword_editingFinished()
{
    if(ui->setusernewpassword->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(passwordstype,0);
    int pos = 0;
    QString setusernewpasswordstype=ui->setusernewpassword->text();
    if(QValidator::Acceptable!=validator.validate(setusernewpasswordstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->setnewpasswordwarning->setText(tr("输入错误,请输入6到16位数字或字母，区分大小写"));
     }
    else if(QValidator::Acceptable==validator.validate(setusernewpasswordstype,pos)){
        ui->setnewpasswordwarning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_setusernewpasswordtwice_editingFinished()
{
    if(ui->setusernewpasswordtwice->text().isEmpty()){
        return;
    }
    QString userpasswordgets1=ui->setusernewpassword->text();
    string ba1=userpasswordgets1.toStdString();
    char userpasswordgets[20];
    strcpy(userpasswordgets, ba1.c_str());
    QString userpasswordtwice1=ui->setusernewpasswordtwice->text();
    string ba4=userpasswordtwice1.toStdString();
    char userpasswordtwice[20];
    strcpy(userpasswordtwice, ba4.c_str());
    if (strcmp(userpasswordgets,userpasswordtwice) == 0){
        ui->setnewpasswordtwicewarning->setText(tr("输入成功"));
    }
    else {
        ui->setnewpasswordtwicewarning->setText(tr("两次密码不相同"));
    }
}
void LibrarySystem::on_addbookokBtn_clicked()
{
    if(ui->inputbookname1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入书名");
    else if(ui->inputauthor1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入作者");
    else if(ui->inputpublisher1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入出版社");
    else if(ui->inputisbn1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入ISBN");
    else if(ui->inputstorage1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入数量");
    else
    {
        QRegExpValidator validator(shuming,0);
        int pos = 0;
        QString dongman=ui->inputbookname1->text();
        if(QValidator::Acceptable!=validator.validate(dongman,pos)){
            QMessageBox::information(this,"书名输入格式错误","请输入1~3个汉字.");
            return;
         }
        QRegExpValidator validator2(zuozhe,0);
        pos = 0;
        dongman=ui->inputauthor1->text();
        if(QValidator::Acceptable!=validator2.validate(dongman,pos)){
            QMessageBox::information(this,"作者输入格式错误","请输入1到15个字符，汉字、字母、数字.");
            return;
         }
        QRegExpValidator validator3(zuozhe,0);
        pos = 0;
        dongman=ui->inputpublisher1->text();
        if(QValidator::Acceptable!=validator3.validate(dongman,pos)){
            QMessageBox::information(this,"出版社输入格式错误","请输入1到15个字符，汉字、字母、数字.");
            return;
         }
        QRegExpValidator validator4(isbntype,0);
        pos = 0;
        dongman=ui->inputisbn1->text();
        if(QValidator::Acceptable!=validator4.validate(dongman,pos)){
            QMessageBox::information(this,"ISBN输入格式错误","请输入1到16位数字或字母，区分大小写.");
            return;
         }

        dongman=ui->inputstorage1->text();
        int numble;
        numble=dongman.toInt();
        if(numble > 20||numble<=0){
            QMessageBox::information(this,"库存输入错误","数量应为1~20.");
            return;
         }

    QString bookname = ui->inputbookname1->text();
    QString author = ui->inputauthor1->text();
    QString publisher = ui->inputpublisher1->text();
    QString isbn = ui->inputisbn1->text();
    QString storage = ui->inputstorage1->text();
    //std::string str = filename.toStdString();
    //const char* ch = str.c_str();
    std::string bookname_1 = bookname.toStdString();
    std::string author_1 = author.toStdString();
    std::string publisher_1 = publisher.toStdString();
    std::string isbn_1 = isbn.toStdString();
    char* bookname_2 = const_cast<char*>(bookname_1.c_str());
    char* author_2 = const_cast<char*>(author_1.c_str());
    char* publisher_2 = const_cast<char*>(publisher_1.c_str());
    char* isbn_2 = const_cast<char*>(isbn_1.c_str());
    short storage_2 = storage.toShort();
    int bookid = allbook + 100000001;
    QString s = QString::number(bookid, 10);
    char* bookid_2 = const_cast<char*>(s.toStdString().data());//int转char*
    QMessageBox::information(this, "Warning", "3");
    Book temp(bookid_2,bookname_2,author_2,publisher_2,isbn_2,storage_2);

    QMessageBox::information(this, "Warning", "6");
    if(admin.addBook(temp) == 1)QMessageBox::information(this, "Warning", "添加成功");
    else QMessageBox::warning(this, "ERROR", "该书已存在，添加失败");
    ui->inputbookname1->clear();
    ui->inputauthor1->clear();
    ui->inputpublisher1->clear();
    ui->inputisbn1->clear();
    ui->inputstorage1->clear();
    }
}

void LibrarySystem::on_addbookBtn_clicked()
{
    ui->inputbookname1->clear();
    ui->inputbookname1->setFocus();
    ui->inputauthor1->clear();
    ui->inputpublisher1->clear();
    ui->inputisbn1->clear();
    ui->inputstorage1->clear();
    ui->adminwidget->setCurrentIndex(3);
    //ui->inputbookname1warning->setText(tr("1到30个字符，汉字、字母、数字"));
    //ui->inputauthor1warning->setText(tr("1到15个字符，汉字、字母、数字"));
    //ui->inputpublisher1warning->setText(tr("1到15个字符，汉字、字母、数字"));
    //ui->inputisbn1warning->setText(tr("1到16位数字或字母，区分大小写"));
    //ui->inputstorage1warning->setText(tr("库位1到20"));
}

void LibrarySystem::on_addadminBtn_clicked()
{
    ui->inputadminname1->clear();
    ui->inputadminpass1->clear();
    ui->inputadminpasstwice1->clear();
    ui->inputadmincid1->clear();
    ui->inputadminphone1->clear();
    ui->adminwidget->setCurrentIndex(2);
    ui->inputadminname1warning->setText(tr("1到3位汉字"));
    ui->inputadminpass1warning->setText(tr("6到16位数字或字母，区分大小写"));
    ui->inputadminpasstwice1warning->setText(tr("请再次填写密码"));
    ui->inputadmincid1warning->setText(tr("忘记密码时，可以通过该身份证号码快速找回密码"));
    ui->inputadminphone1warning->setText(tr("方便我们联系您"));
    ui->inputadminpass1->setEchoMode(QLineEdit::Password);
    ui->inputadminpasstwice1->setEchoMode(QLineEdit::Password);
}


void LibrarySystem::on_addadminokBtn_clicked()
{
    if(ui->inputadminname1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入姓名");
    else if(ui->inputadminpass1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入密码");
    else if(ui->inputadminpasstwice1->text().isEmpty())QMessageBox::warning(this, "Warning", "请确认密码");
    else if(ui->inputadmincid1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入身份证");
    else if(ui->inputadminphone1->text().isEmpty())QMessageBox::warning(this, "Warning", "请输入手机号");
    else if(ui->inputadminpasstwice1->text() != ui->inputadminpass1->text())QMessageBox::warning(this, "Warning", "两次输入密码不一致");
    else{
        QRegExpValidator validator(hanzi,0);
        int pos = 0;
        QString dongman=ui->inputadminname1->text();
        if(QValidator::Acceptable!=validator.validate(dongman,pos)){
            QMessageBox::information(this,"姓名输入格式错误","请输入1~3个汉字.");
            return;
         }
        QRegExpValidator validator2(passwordstype,0);
        pos = 0;
        QString userpasswordgetstype=ui->inputadminpass1->text();
        if(QValidator::Acceptable!=validator2.validate(userpasswordgetstype,pos)){
            QMessageBox::information(this,"密码输入格式错误","请输入6到16位数字或字母，区分大小写.");
            return;
         }
        QRegExpValidator validator3(sfztype,0);
        pos = 0;
        userpasswordgetstype=ui->inputadmincid1->text();
        if(QValidator::Acceptable!=validator3.validate(userpasswordgetstype,pos)){
            QMessageBox::information(this,"身份证号输入格式错误","请输入正确的身份证号.");
            return;
         }
        QRegExpValidator validator4(phonetype,0);
        pos = 0;
        userpasswordgetstype=ui->inputadminphone1->text();
        if(QValidator::Acceptable!=validator4.validate(userpasswordgetstype,pos)){
            QMessageBox::information(this,"手机号输入格式错误","请输入正确的手机号.");
            return;
         }
        QString adminname = ui->inputadminname1->text();
        QString adminpass = ui->inputadminpass1->text();
        QString admincid = ui->inputadmincid1->text();
        QString adminphone = ui->inputadminphone1->text();
        std::string adminname_1 = adminname.toStdString();
        std::string adminpass_1 = adminpass.toStdString();
        std::string admincid_1 = admincid.toStdString();
        std::string adminphone_1 = adminphone.toStdString();
        //char* bookname_2 = const_cast<char*>(bookname_1.c_str());
        char* adminname_2 =  const_cast<char*>(adminname_1.c_str());
        char* adminpass_2 = const_cast<char*>(adminpass_1.c_str());
        char* admincid_2 = const_cast<char*>(admincid_1.c_str());
        char* adminphone_2 = const_cast<char*>(adminphone_1.c_str());
        //int Administrator::addadmin(char*aPassword, char*accountHolder, char*aID, char*aPhone)
        if(admin.addadmin(adminpass_2,adminname_2,admincid_2,adminphone_2) == 1)QMessageBox::information(this, "Warning", "添加成功");
        else QMessageBox::warning(this, "ERROR", "管理员已存在，添加失败");
        ui->inputadminname1->clear();
        ui->inputadminpass1->clear();
        ui->inputadminpasstwice1->clear();
        ui->inputadmincid1->clear();
        ui->inputadminphone1->clear();
    }
}

void LibrarySystem::on_looklogBtn_clicked()
{
    ui->adminwidget->setCurrentIndex(0);
}


void LibrarySystem::setBtnQss(QPushButton *btn,
                        QString normalColor, QString normalTextColor,
                        QString hoverColor, QString hoverTextColor,
                        QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

void LibrarySystem::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}

void LibrarySystem::UIDesign()
{
        setBtnQss(ui->userLogin, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");//绿色
        setBtnQss(ui->userRegister, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->lossPassword, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->registerAchieve, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->registerExit, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->submit, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->findbackpasswordexit, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->achievesetnewpassword, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        setBtnQss(ui->setnewpasswordexit, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");


        setBtnQss(ui->userwindowinformation, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");//用户蓝色
        setBtnQss(ui->lendInfoBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->searchBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->changeinforBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->userLogout, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->orderInfoBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->chargeBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");

        setBtnQss(ui->addadminBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");//管理员 蓝色
        setBtnQss(ui->addbookBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->adminLogout, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->admininformationBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->adminaddstoBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
        setBtnQss(ui->looklogBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");

        setBtnQss(ui->searchokbutton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");//暗蓝色
        setBtnQss(ui->bookorderbutton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
        setBtnQss(ui->booklendbutton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
        setBtnQss(ui->addadminokBtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
        setBtnQss(ui->addbookokBtn, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");

        setTxtQss(ui->useraccount, "#DCE4EC", "#34495E");
        setTxtQss(ui->userpassword, "#DCE4EC", "#34495E");
        setTxtQss(ui->searchtext,"#DCE4EC", "#1ABC9C");
}


void LibrarySystem::on_inputbookname1_editingFinished()
{
    if(ui->inputbookname1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(shuming,0);
    int pos = 0;
    QString dongman=ui->inputbookname1->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputbookname1warning->setText(tr("输入错误,请输入1到30位字符，汉字、字母、数字"));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->inputbookname1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputauthor1_editingFinished()
{
    if(ui->inputauthor1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(zuozhe,0);
    int pos = 0;
    QString dongman=ui->inputauthor1->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputauthor1warning->setText(tr("输入错误,请输入1到15个字符，汉字、字母、数字"));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->inputauthor1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputpublisher1_editingFinished()
{
    if(ui->inputpublisher1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(zuozhe,0);
    int pos = 0;
    QString dongman=ui->inputpublisher1->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputpublisher1warning->setText(tr("输入错误,请输入1到15个字符，汉字、字母、数字"));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->inputpublisher1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputisbn1_editingFinished()
{
    if(ui->inputisbn1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(isbntype,0);
    int pos = 0;
    QString dongman=ui->inputisbn1->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputisbn1warning->setText(tr("输入错误,请输入1到16位数字或字母，区分大小写"));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->inputisbn1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputstorage1_editingFinished()
{
    if(ui->inputstorage1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QString dongman=ui->inputstorage1->text();
    int numble;
    numble=dongman.toInt();
    if(numble > 20){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputstorage1warning->setText(tr("书库存上限为20"));
     }
    else if(numble<=0){
        ui->inputstorage1warning->setText(tr("库存应为正数"));
    }
    else {
        ui->inputstorage1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputadminname1_editingFinished()
{
    if(ui->inputadminname1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(hanzi,0);
    int pos = 0;
    QString dongman=ui->inputadminname1->text();
    if(QValidator::Acceptable!=validator.validate(dongman,pos)){
        //QMessageBox::information(this,"输入错误","请输入1~3个汉字.");
        ui->inputadminname1warning->setText(tr("输入错误,请输入1~3个汉字."));
     }
    else if(QValidator::Acceptable==validator.validate(dongman,pos)){
        ui->inputadminname1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputadminpass1_editingFinished()
{
    if(ui->inputadminpass1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(passwordstype,0);
    int pos = 0;
    QString userpasswordgetstype=ui->inputadminpass1->text();
    if(QValidator::Acceptable!=validator.validate(userpasswordgetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->inputadminpass1warning->setText(tr("输入错误,请输入6到16位数字或字母，区分大小写"));
     }
    else if(QValidator::Acceptable==validator.validate(userpasswordgetstype,pos)){
        ui->inputadminpass1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputadminpasstwice1_editingFinished()
{
    if(ui->inputadminpasstwice1->text().isEmpty()){
        return;
    }
    QString userpasswordgets1=ui->inputadminpass1->text();
    string ba1=userpasswordgets1.toStdString();
    char userpasswordgets[20];
    strcpy(userpasswordgets, ba1.c_str());
    QString userpasswordtwice1=ui->inputadminpasstwice1->text();
    string ba4=userpasswordtwice1.toStdString();
    char userpasswordtwice[20];
    strcpy(userpasswordtwice, ba4.c_str());
    if (strcmp(userpasswordgets,userpasswordtwice) == 0){
        ui->inputadminpasstwice1warning->setText(tr("输入成功"));
    }
    else {
        ui->inputadminpasstwice1warning->setText(tr("两次密码不相同"));
    }
}

void LibrarySystem::on_inputadmincid1_editingFinished()
{
    if(ui->inputadmincid1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(sfztype,0);
    int pos = 0;
    QString userpasswordgetstype=ui->inputadmincid1->text();
    if(QValidator::Acceptable!=validator.validate(userpasswordgetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->inputadmincid1warning->setText(tr("输入错误,请输入正确的身份证号"));
     }
    else if(QValidator::Acceptable==validator.validate(userpasswordgetstype,pos)){
        ui->inputadmincid1warning->setText(tr("输入成功"));
    }
}

void LibrarySystem::on_inputadminphone1_editingFinished()
{
    if(ui->inputadminphone1->text().isEmpty()){
        return;
    }
    //QRegExp reg("[1-9]\\d{0,8}");
    QRegExpValidator validator(phonetype,0);
    int pos = 0;
    QString userpasswordgetstype=ui->inputadminphone1->text();
    if(QValidator::Acceptable!=validator.validate(userpasswordgetstype,pos)){
        //QMessageBox::information(this,"输入错误","请输入6到16位数字或字母，区分大小写.");
        ui->inputadminphone1warning->setText(tr("输入错误,请输入正确的手机号"));
     }
    else if(QValidator::Acceptable==validator.validate(userpasswordgetstype,pos)){
        ui->inputadminphone1warning->setText(tr("输入成功"));
    }
}


void LibrarySystem::on_usernameget_textChanged(const QString &arg1)
{
    return;
}

void LibrarySystem::on_usersfznumbleget_cursorPositionChanged(int arg1, int arg2)
{
    return;
}

void LibrarySystem::closeEvent(QCloseEvent *event)
{
    /*QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        char accountdm[10]="0";
        char accountdmuser[10]="1";
        char accountdmadminr[10]="2";
        if(strcmp(carddm.getcardID(), accountdm) == 0){
            //QMessageBox::information(this,"输入错误","啥都没有.");
        }
        else if(strcmp(carddm.getcardID(), accountdmuser) == 0){
            //QMessageBox::information(this,"输入错误","用户登录过了");
            signOut();
        }
        else if(strcmp(carddm.getcardID(), accountdmadminr) == 0){
            //QMessageBox::information(this,"输入错误","管理员登录过了");
            signOut_Admin();
        }
        event->accept();  //接受退出信号，程序退出
    }*/
    if(dmend== 0){
        QMessageBox::information(this,"输入错误","啥都没有.");
    }
    else if(dmend == 1){
        QMessageBox::information(this,"输入错误","用户登录过了");
        signOut();
    }
    else if(dmend == 2){
        QMessageBox::information(this,"输入错误","管理员登录过了");
        signOut_Admin();
    }
    event->accept();  //接受退出信号，程序退出

}

void LibrarySystem::on_changeinforBtn_clicked()
{
    ui->userwidget->setCurrentIndex(1);
}
