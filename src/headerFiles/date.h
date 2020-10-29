#ifndef __DATE_H__
#define __DATE_H__

class Date
{
public:
    Date(int year, int month, int day);
    int distance(const Date& d) const;
    void show() const;
    int getYear() const { return year; };
    int getMonth() const { return month; };
    int getDay() const { return day; };
    int getMaxDay() const;
private:
    int year, month, day, totalDays;
    bool isLeapYear() const;
};

#endif
