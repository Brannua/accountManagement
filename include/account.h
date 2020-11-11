#pragma once
#include <string>
#include "date.h"
#include "accumulator.h"
using namespace std;

class Account
{
public:
    const string& getId() const { return id; };
    double getBalance() const { return balance; };
    static double getTotal() { return total; };
    void show() const; // 显示账户信息
protected:
    Account(const Date& date, const string& id);                      // 供派生类调用的构造函数
    void record(const Date& date, double amount, const string& desc); // 记录一笔账
    void error(const string& msg) const;                              // 报告错误信息
private:
    string id;           // 账号
    double balance;      // 余额
    static double total; // 所有账户的总金额
};

// 储蓄账户类
class SavingsAccount : public Account
{
public:
    SavingsAccount(const Date& date, const string& id, double rate);
    double getRate() const { return rate; };
    void deposit(const Date& date, double amount, const string& desc);    // 存入现金
    void withdraw(const Date& date, double amount, const string& desc);   // 取出现金
    void settle(const Date& date); // 结算利息，每年 1 月 1 日 调用一次该函数
private:
    double rate;        // 存款的年利率
    Accumulator acc;    // 辅助计算利息的累加器
};

// 信用账户类
class CreditAccount : public Account
{
public:
    CreditAccount(const Date& date, const string& id, double rate, double fee, double credit);
    double getRate() const { return rate; };
    double getFee() const { return fee; };
    double getCredit() const { return credit; };
    void deposit(const Date& date, double amount, const string& desc);    // 存入现金
    void withdraw(const Date& date, double amount, const string& desc);   // 取出现金
    void settle(const Date& date);      // 结算利息和年费，每月 1 日 调用一次该函数
    double getAvailableCredit() const;  // 获得可用信用额度
    void show() const;
private:
    double rate;            // 欠款的日利率
    double fee;             // 信用卡年费
    double credit;          // 信用额度
    Accumulator acc;        // 辅助计算利息的累加器
    double getDebt() const; // 获得欠款额
};
