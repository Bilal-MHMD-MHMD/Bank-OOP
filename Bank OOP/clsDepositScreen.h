#pragma once

#include <iostream>
#include "clsClientScreens.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsClientScreens
{

private:


public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadNewAccountNumber();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadNewAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadNumber<double>();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client1.Balance;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};
