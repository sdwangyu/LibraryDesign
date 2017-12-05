#ifndef ALLX_H
#define ALLX_H

extern int allbook;
extern int allcard;
extern int alladmin;

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

#endif // ALLX_H
