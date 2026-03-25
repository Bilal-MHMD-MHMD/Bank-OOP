#pragma once
#include "clsClientScreens.h" 
#include "clsBankClient.h"
#include "clsUtility.h"
#include <iomanip>
class clsTotalBalancesScreen :
    protected clsClientScreens
{ 

public :
	static void ShowTotalBalancesScreen()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				cout << "| " << setw(15) << left << Client.AccountNumber;
				cout << "| " << setw(20) << left << Client.FullName();
				cout << "| " << setw(12) << left << Client.Balance;
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << clsUtil::Tabs(10) << "Total Balances is = " << clsBankClient::GetTotalBalances()
			<< "\n" << clsUtil::Tabs(10) << clsUtil::NumberToText(clsBankClient::GetTotalBalances()) << "Thank You :) \n";
	}

};

