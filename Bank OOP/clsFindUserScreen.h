#pragma once
#include <iostream>
#include "clsUserScreens.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsUserScreens
{


public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};
