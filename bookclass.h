#ifndef BOOKCLASS_H
#define BOOKCLASS_H


class Book//构造函数 复制构造函数
{
public:
    friend class Administrator;
    friend class Record;
    Book(char BookID[10], char BookName[100], char Author[50], char Publisher[50], short Storage);
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
    short storage; //库存
    short bookMan; //预约人数
    short tStorage;  //临时库存
    char flag;  //图书是否存在
    char books[21]; //数组中每一项用来表示具体某一本的状态，0：损坏 1：可借 2：借出 3.表示初始化值，这本书还不可以用
    //动态开辟存储空间?
    //书籍库存上限为20
};

#endif // BOOKCLASS_H
