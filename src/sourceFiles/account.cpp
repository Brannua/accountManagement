#include "stdafx.h"
using namespace std;

const int DAYS_OF_YEAR = 365; // 一年按照 360 天计算

double SavingsAccount::total = 0; // 初始化静态属性: 一个人名下所有账户的总余额

SavingsAccount::SavingsAccount(const string& newId, double newRate, int newDate) : balance(0), accumulation(0)
{
    id = newId;
    rate = newRate;
    lastDate = newDate;
    cout << lastDate << "\t#" << id << " is created." << endl;
}

void SavingsAccount::show() const
{
    cout << "#" << id << "\tBalance: " << balance << endl;
}

double SavingsAccount::accumulate(int date) const
{
    return accumulation + balance * (date - lastDate);
}

void SavingsAccount::record(int date, double amount, const string& desc)
{
    accumulation = accumulate(date);
    lastDate = date;
    amount = floor(amount * 100 + 0.5) / 100; // 四舍五入保留小数点后两位 floor -- <cmath>
    balance += amount; // 更新当前账户的余额
    total += amount;   // 更新开户人名下所有账户的总余额
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void SavingsAccount::deposit(int date, double amount, const string& desc)
{
    record(date, amount, desc);
}

void SavingsAccount::withDraw(int date, double amount, const string& desc)
{
    // 注意这里要进行判断余额是否充足的
    if (amount > balance)
    {
        cout << "Error: not enough money" << endl;
    }
    else
    {
        record(date, -amount, desc);
    }
}

void SavingsAccount::settle(int date)
{
    double interest = accumulate(date) * rate / DAYS_OF_YEAR;
    if (interest != 0)
    {
        record(date, interest, "interest");
    }
    accumulation = 0;
}
