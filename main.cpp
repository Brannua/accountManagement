#include "date.h"
#include "accumulator.h"
#include "account.h"
#include "Array.h"
#include <iostream>
using namespace std;

int main()
{
	// 起始日期
	Date date(2008, 11, 1);

    // 创建账户数组，元素个数为 0
    Array<Account*> accounts(0); 

	// 一句友好的提示语
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change_day (n)next_month (e)exit" << endl;

	char cmd;
	do
	{
        char type;
		int index, day;
		double amount, credit, rate, fee;
		string id, desc;
        Account * account;

        // 显示日期和总金额
		date.show();
		cout << "\tTotal: " << Account::getTotal() << "\tcommand>";

        cin >> cmd;
		switch (cmd)
		{
        case 'a': // 增加账户
            cin>>type>>id;
            if (type == 's') {
                cin >> rate;
                account = new SavingsAccount(date, id, rate);
            } else {
                cin >> credit >> rate >> fee;
                account = new CreditAccount(date, id, credit, rate, fee);
            }
            accounts.resize(accounts.getSize() + 1);
            accounts[accounts.getSize() - 1] = account;
            break;
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
			for (int i = 0; i < accounts.getSize(); i++)
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
			for (int i = 0; i < accounts.getSize(); i++)
			{
                accounts[i] -> settle(date);
			}
			break;
		default:
			break;
		}

	} while (cmd != 'e');

    for (int i = 0; i < accounts.getSize(); i ++) {
        delete accounts[i];
    }

	return 0;
}
