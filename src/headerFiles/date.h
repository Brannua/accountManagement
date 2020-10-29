#ifndef __DATE_H__
#define __DATE_H__

class Date
{
public:
    Date(int year, int month, int day);     // 构造函数
    bool isLeapYear() const {               // 判断日期对象所属年份是否为闰年
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    };
    int distance(const Date& d) const {     // 计算两日期对象之间相差的天数
        return totalDays - d.totalDays;
    };
    void show() const;                      // 格式化打印日期对象表示的日期
    int getYear() const { return year; };   // 获取日期对象 year 属性的接口
    int getMonth() const { return month; }; // 获取日期对象 month 属性的接口
    int getDay() const { return day; };     // 获取日期对象 day 属性的接口
    int getMaxDay() const;                  // 获取日期对象所属月份的天数
private:
    int year, month, day, totalDays;        // totalDays 表示从公元元年 1 月 1 日开始的第几天
};

#endif
