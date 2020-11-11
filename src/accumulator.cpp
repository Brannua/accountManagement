#include "accumulator.h"
#include <iostream>
using namespace std;

Accumulator::Accumulator(const Date &date, double value) : lastDate(date), value(value), sum(0) {}

double Accumulator::getSum(const Date &date) const
{
    return sum + date.distance(lastDate) * value;
}

void Accumulator::change(const Date &date, double value)
{
    sum = getSum(date);
    lastDate = date;
    this->value = value;
}

void Accumulator::reset(const Date &date, double value)
{
    sum = 0;
    lastDate = date;
    this->value = value;
}
