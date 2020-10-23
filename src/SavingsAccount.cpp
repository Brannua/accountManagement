
#include "account.h"
#include <iostream>
using namespace std;

const double RATE = 0.015;

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

    // 显示户主总资产
    cout << "Total: " << SavingsAccount::getTotal() << endl;
    return 0;
}
