#include "account.h"
#include "date.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

const int DAYS_OF_YEAR = 365; // 一年按照 365 天计算

double SavingsAccount::total = 0; // 初始化静态属性: 一个人名下所有账户的总余额

SavingsAccount::SavingsAccount(const string& newId, double newRate, const Date& newDate) : id(newId), balance(0), rate(newRate), lastDate(newDate), accumulation(0)
{
    newDate.show();
    cout << "\t#" << id << " is created." << endl;
}

void SavingsAccount::show() const
{
    cout << "#" << id << "\t账户余额: " << balance << endl;
}

double SavingsAccount::accumulate(const Date& date) const
{
    return accumulation + balance * date.distance(lastDate);
}

void SavingsAccount::record(const Date& date, double amount, const string& desc)
{
    accumulation = accumulate(date);
    lastDate = date;
    amount = floor(amount * 100 + 0.5) / 100; // 四舍五入保留小数点后两位 floor -- <cmath>
    balance += amount; // 更新当前账户的余额
    total += amount;   // 更新开户人名下所有账户的总余额
    date.show();
    cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void SavingsAccount::deposit(const Date& date, double amount, const string& desc)
{
    record(date, amount, desc);
}

void SavingsAccount::withDraw(const Date& date, double amount, const string& desc)
{
    // 注意这里要进行判断余额是否充足的
    if (amount > balance)
    {
        error("not enough money");
    }
    else
    {
        record(date, -amount, desc);
    }
}

void SavingsAccount::settle(const Date& date)
{
    double interest = accumulate(date) * rate / DAYS_OF_YEAR;
    if (interest != 0)
    {
        record(date, interest, "结算利息");
    }
    accumulation = 0;
}

void SavingsAccount::error(const string& msg) const
{
    cout << "Error: (#" << id << "): " << msg << endl;
}
