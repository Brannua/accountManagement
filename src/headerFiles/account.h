#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

using std::string;

class SavingsAccount
{
public:
    SavingsAccount(const string& id, double rate, const Date& date);    // 构造函数
    void show() const;                                                  // 显示账户基本信息
    void deposit(const Date& date, double amount, const string& desc);  // 存款
    void withDraw(const Date& date, double amount, const string& desc); // 取款
    void settle(const Date& date);                                      // 结算利息
    static double getTotal() { return total; };                         // 查询一个人名下所有账户总余额的接口

private:
    string id;                                                          // 账户 id
    double balance;                                                     // 余额
    double rate;                                                        // 利率
    Date lastDate;                                                      // 上一次修改余额的时间
    double accumulation;                                                // 累积从上一次结算利息到最近一次余额变动时，中间 n 段 (存款金额 * 天数) 的加和
    double accumulate(const Date& date) const;                          // 修改 accumulation
    void record(const Date& date, double amount, const string& desc);   // 修改余额
    static double total;                                                // 一个人名下所有账户的总余额
    void error(const string& msg) const;                                // 打印报错信息
};
#endif
