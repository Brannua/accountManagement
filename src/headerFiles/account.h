
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
class SavingsAccount
{
public:
    SavingsAccount(int id, double rate, int date); // 构造函数
    void show() const;                             // 显示账户基本信息
    void deposit(int date, double amount);         // 存款
    void withDraw(int date, double amount);        // 取款
    void settle(int date);                         // 结算利息
    static double getTotal()
    { // 静态方法: 查询一个人名下所有账户总余额的接口
        return total;
    };

private:
    int id;                               // 账户 id
    double balance;                       // 余额
    double rate;                          // 利率
    int lastDate;                         // 上一次修改余额的时间
    double accumulation;                  // 累积从上一次结算利息到最近一次余额变动时，中间 n 段 (存款金额 * 天数) 的加和
    double accumulate(int date) const;    // 修改 accumulation
    void record(int date, double amount); // 修改余额
    static double total;                  // 静态属性: 一个人名下所有账户的总余额
};
#endif
