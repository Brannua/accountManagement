#pragma once
#include "date.h"

class Accumulator
{
public:
    Accumulator(const Date& date, double value);
    double getSum(const Date& date) const;
    void change(const Date& date, double value);
    void reset(const Date& date, double value);
private:
    double sum;     // 数值按日累加之和
    Date lastDate;  // 上次变更数值的日期
    double value;   // 数值的当前值
};
