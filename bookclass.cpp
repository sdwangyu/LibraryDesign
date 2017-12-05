#include "bookclass.h"
#include<string.h>

Book::Book(char BookID[10], char BookName[100], char Author[50], char Publisher[50], short Storage)//构造函数
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
