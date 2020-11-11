#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;

double Account::total = 0;

Account::Account(const Date &date, const string &id) : id(id), balance(0)
{
    date.show();
    cout << "\t#" << id << " created" << endl;
}

void Account::show() const
{
    cout << id << "\tBalance " << balance;
}

void Account::record(const Date &date, double amount, const string &desc)
{
    amount = floor(amount * 100 + 0.5) / 100; // 四舍五入, 保留小数点后两位
    balance += amount;
    total += amount;
    date.show();
    cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void Account::error(const string &msg) const
{
    cout << "Error(#" << id << "): " << msg << endl;
}

SavingsAccount::SavingsAccount(const Date &date, const string &id, double rate) : Account(date, id), rate(rate), acc(date, 0) {}

void SavingsAccount::deposit(const Date &date, double amount, const string &desc)
{
    record(date, amount, desc);
    acc.change(date, getBalance());
}

void SavingsAccount::withdraw(const Date &date, double amount, const string &desc)
{
    if (amount > getBalance())
    {
        error("Not enough money.");
        return;
    }
    record(date, -amount, desc);
    acc.change(date, getBalance());
}

void SavingsAccount::settle(const Date &date)
{
    // 计算年息
    double interest = acc.getSum(date) / date.distance(Date(date.getYear() - 1, 1, 1)) * rate;
    if (interest != 0)
    {
        record(date, interest, "interest");
    }
    // 新的计息周期开始, 重置累加器
    acc.reset(date, getBalance());
}

CreditAccount::CreditAccount(const Date &date, const string &id, double rate, double fee, double credit) : Account(date, id), rate(rate), fee(fee), credit(credit), acc(date, 0) {}

double CreditAccount::getDebt() const
{
    double balance = getBalance();
    return balance < 0 ? balance : 0;
}

double CreditAccount::getAvailableCredit() const
{
    double balance = getBalance();
    return balance < 0 ? credit + balance : credit;
}

void CreditAccount::deposit(const Date &date, double amount, const string &desc)
{
    record(date, amount, desc);
    acc.change(date, getDebt());
}

void CreditAccount::withdraw(const Date &date, double amount, const string &desc)
{
    if (amount > getBalance() + credit) {
        error("Not enough credit.");
        return;
    }
    record(date, -amount, desc);
    acc.change(date, getDebt());
}

void CreditAccount::settle(const Date &date)
{
    double interest = acc.getSum(date) * rate;
    if (interest != 0) {
        record(date, interest, "interest");
    }
    if (date.getMonth() == 1) {
        record(date, -fee, "annual fee");
    }
    acc.reset(date, getDebt());
}

void CreditAccount::show() const
{
    Account::show();
    cout << "\tAvailable credit: " << getAvailableCredit();
}
