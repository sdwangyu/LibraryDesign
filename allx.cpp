#include "allx.h"

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
