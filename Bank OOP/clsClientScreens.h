#pragma once
#include "clsScreen.h" 
#include "clsBankClient.h"
class clsClientScreens :
    protected clsScreen
{

protected :
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.Balance;
        cout << "\n___________________\n";

    }

    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.FirstName = clsString::ReadString("Please enter First Name: ");
        Client.LastName = clsString::ReadString("Please enter Last Name: ");
        Client.Email = clsString::ReadString("Please enter Email: ");
        Client.Phone = clsString::ReadString("Please enter Phone: ");
        Client.Balance = stod(clsString::ReadString("Please enter Balance: ")); // string to double
        Client.PinCode = clsString::ReadString("Please enter Pin Code: ");

    }  

    static string _ReadNewAccountNumber()
    {
        return clsString::ReadString("Please enter Account Number: ");
	} 

    static string _ReadExistingAccountNumber()
    {
        string AccountNumber = "";
        AccountNumber = clsString::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
           
            cout << "\nClient is not found, please enter another Account Number: ";
        
            AccountNumber = clsString::ReadString();
        }

        return AccountNumber;
    }
};

