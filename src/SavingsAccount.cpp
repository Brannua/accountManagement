#include <iostream>
#include <cmath>
using namespace std;

// const int DAYS_OF_YEAR = 360;   // 一年按照 360 天计算
// const double RATE = 0.0035;     // 活期存款利率
const int DAYS_OF_YEAR = 365;
const double RATE = 0.015;

class SavingsAccount
{
public:
    SavingsAccount(int id, double rate, int date); // 构造函数
    void show();                                   // 显示账户基本信息
    void deposit(int date, double amount);         // 存款
    void withDraw(int date, double amount);        // 取款
    void settle(int date);                         // 结算利息

private:
    int id;                               // 账户 id
    double balance;                       // 余额
    double rate;                          // 利率
    int lastDate;                         // 上一次修改余额的时间
    double accumulation;                  // 累积从上一次结算利息到最近一次余额变动时，中间 n 段 (存款金额 * 天数) 的加和
    double accumulate(int date);          // 修改 accumulation
    void record(int date, double amount); // 修改余额
};

SavingsAccount::SavingsAccount(int newId, double newRate, int newDate) : balance(0), accumulation(0)
{
    id = newId;
    rate = newRate;
    lastDate = newDate;
    cout << lastDate << "\t#" << id << " is created." << endl;
}

void SavingsAccount::show()
{
    cout << "#" << id << "\tBalance: " << balance << endl;
}

double SavingsAccount::accumulate(int date)
{
    return accumulation + balance * (date - lastDate);
}

void SavingsAccount::record(int date, double amount)
{
    accumulation = accumulate(date);
    lastDate = date;
    amount = floor(amount * 100 + 0.5) / 100; // 四舍五入保留小数点后两位 floor -- <cmath>
    balance += amount;
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance << endl;
}

void SavingsAccount::deposit(int date, double amount)
{
    record(date, amount);
}

void SavingsAccount::withDraw(int date, double amount)
{
    // 注意这里要进行判断余额是否充足的
    if (amount > balance)
    {
        cout << "Error: not enough money" << endl;
    }
    else
    {
        record(date, -amount);
    }
}

void SavingsAccount::settle(int date)
{
    double interest = accumulate(date) * rate / DAYS_OF_YEAR;
    if (interest != 0)
    {
        record(date, interest);
    }
    accumulation = 0;
}

int main()
{
    // 在日期 1 号，开俩账户
    SavingsAccount sa0(21325302, RATE, 1);
    SavingsAccount sa1(58320212, RATE, 1);

    // 对俩账户一顿操作
    sa0.deposit(5, 5000);
    sa1.deposit(25, 10000);
    sa0.deposit(45, 5500);
    sa1.withDraw(60, 4000);
    sa0.settle(90);
    sa1.settle(90);

    // 显示俩账户的基本信息
    sa0.show();
    sa1.show();
    return 0;
}
