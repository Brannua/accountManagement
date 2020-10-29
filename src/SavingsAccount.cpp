#include "stdafx.h"
using namespace std;

const double RATE = 0.015;

int main()
{
	Date date(2008, 11, 1);
	SavingsAccount accounts[] = {
		SavingsAccount("S3755217", 0.015, date),
		SavingsAccount("02342342", 0.015, date)
	};

	accounts[0].deposit(Date(2008, 11, 5), 5000, "salary");
	accounts[1].deposit(Date(2008, 11, 25), 10000, "sell stock 0323");
	accounts[0].deposit(Date(2008, 12, 5), 5500, "salary");
	accounts[1].withDraw(Date(2008, 12, 20), 4000, "buy a laptop");

	cout << endl;

	for (int i = 0, n = sizeof(accounts) / sizeof(SavingsAccount); i < n; i ++) {
		accounts[i].settle(Date(2009, 1, 1)); // 指定日期结算利息
		accounts[i].show();
		cout << endl;
	}

	cout << "Total: " << SavingsAccount::getTotal() << endl;

	return 0;
}
