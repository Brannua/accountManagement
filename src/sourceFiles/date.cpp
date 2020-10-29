#include "stdafx.h"
using namespace std;

namespace
{
    // 存储平年中的每个月一号之前有多少天，为便于 getMaxDay 函数的实现，数组应有第 13 个元素
    const int DAYS_BEFORE_MONTH[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
}

Date::Date(int year, int month, int day) : year(year), month(month), day(day)
{
    if (day <= 0 || day > getMaxDay())
    {
        cout << "Invalid date: ";
        show();
        cout << endl;
        exit(1);
    }
    int gap = year - 1;
    // 4年一闰，100免闰，400再闰
    totalDays = 365 * gap + gap / 4 - gap / 100 + gap / 400;

    totalDays += DAYS_BEFORE_MONTH[month];
    if (isLeapYear())
    {
        totalDays += 1;
    }

    totalDays += day;
}

void Date::show() const
{
    cout << getYear() << "-" << getMonth() << "-" << getDay();
}

int Date::distance(const Date &d) const
{
    int destDays = d.totalDays;
    return destDays > totalDays ? destDays - totalDays : totalDays - destDays;
}

bool Date::isLeapYear() const
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int Date::getMaxDay() const
{
    if (isLeapYear() && month == 2) {
        return 29;
    }
    return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
}
