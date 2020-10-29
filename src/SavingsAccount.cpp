#include "stdafx.h"
using namespace std;

const double RATE = 0.015;

int main()
{
	// 新建日期，开俩账户
	Date d1(2020, 10, 29), d2(2020, 10, 30), d3(2020, 11, 7), d4(2020, 11, 17), d5(2020, 11, 19);
	SavingsAccount accounts[] = {
		SavingsAccount("21325302", RATE, d1),
		SavingsAccount("58320212", RATE, d1)};

	// 对俩账户一顿操作
	accounts[0].deposit(d2, 5000, "存款");
	accounts[1].deposit(d3, 10000, "存款");
	accounts[1].withDraw(d4, 400, "取款");
	accounts[0].settle(d5);
	accounts[1].settle(d5);

	// 显示俩账户的基本信息
	for (int i = 0, len = sizeof(accounts) / sizeof(accounts[0]); i < len; i++)
	{
		accounts[i].show();
	}

	// 显示户主总资产
	cout << "所有账户总余额: " << SavingsAccount::getTotal() << endl;
	return 0;
}
