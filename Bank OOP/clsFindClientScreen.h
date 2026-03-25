#pragma once
#include "clsClientScreens.h" 
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen :
    protected clsClientScreens
{ 

public:
    static void ShowFindClientScreen()
    { 
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

       clsClientScreens::_PrintClientCard(Client1);

    }
};

