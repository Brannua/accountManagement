#include "date.h"
#include "accumulator.h"
#include "account.h"
#include <iostream>
using namespace std;

int main()
{
	// 起始日期
	Date date(2008, 11, 1);

	// 建立几个账户
	SavingsAccount sa1(date, "s3755217", 0.015);
	SavingsAccount sa2(date, "02342342", 0.015);
	CreditAccount ca(date, "c5392394", 0.0005, 50, 10000);

	// 将这几个账户组织起来并计算账户总数
	Account *accounts[] = {&sa1, &sa2, &ca};
	const int n = sizeof(accounts) / sizeof(Account *);

	// 一句友好的提示语
	cout << "(d)deposit (w)withdraw (s)show (c)change_day (n)next_month (e)exit" << endl;

	char cmd;
	do
	{
		int index, day;
		double amount;
		string desc;

		date.show();

		cout << "\tTotal: " << Account::getTotal() << "\tcommand>";
		cin >> cmd;

		switch (cmd)
		{
		case 'd': // 存入现金
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w': // 取出现金
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's': // 查询各账户信息
			for (int i = 0; i < n; i++)
			{
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c': // 改变日期
			cin >> day;
			if (day < date.getDay())
			{
				cout << "You can't specify a previous day.";
			}
			else if (day > date.getMaxDay())
			{
				cout << "Invalid day.";
			}
			else
			{
				date = Date(date.getYear(), date.getMonth(), day);
			}
			break;
		case 'n': // 进入下个月
			if (date.getMonth() == 12)
			{
				date = Date(date.getYear() + 1, 1, 1);
			}
			else
			{
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}
			for (int i = 0; i < n; i++)
			{
				accounts[i]->settle(date);
			}
			break;
		default:
			break;
		}

	} while (cmd != 'e');

	return 0;
}
