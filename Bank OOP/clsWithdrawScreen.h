#pragma once

#include <iostream>
#include "clsClientScreens.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsClientScreens
{
private:



public:

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = clsClientScreens::_ReadNewAccountNumber();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadNewAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client1);


        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadNumber<double>();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.Balance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client1.Balance;

            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};
