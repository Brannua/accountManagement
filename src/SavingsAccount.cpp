#include "stdafx.h"
using namespace std;

const double RATE = 0.015;

int main()
{
	// 新建日期，开俩账户
	Date d1(2020, 10, 29), d2(2020, 10, 30), d3(2020, 11, 7), d4(2020, 11, 17), d5(2020, 11, 19);
	SavingsAccount sa0("21325302", RATE, d1);
	SavingsAccount sa1("58320212", RATE, d1);

	// 对俩账户一顿操作
	sa0.deposit(d2, 5000, "存款");
	sa1.deposit(d3, 10000, "存款");
	sa1.withDraw(d4, 400, "取款");
	sa0.settle(d5);
	sa1.settle(d5);

	// 显示俩账户的基本信息
	sa0.show();
	sa1.show();

	// 显示户主总资产
	cout << "所有账户总余额: " << SavingsAccount::getTotal() << endl;
	return 0;
}
