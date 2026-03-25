#pragma once
#include <iostream>
#include "clsString.h"
#include"clsBankClient.h"
#include "global.h"
#include "clsDate.h" 
#include <string> 
using namespace std;

class clsScreen
{
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }

		cout << "\n\t\t\t\t\t  " << "Current User: " << CurrentUser.FullName();
		cout << "\n\t\t\t\t\t  " << "Current Date: " << clsDate::DateToString(clsDate::GetSystemDate());
        cout << "\n\t\t\t\t\t______________________________________\n\n"; 
    }


    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            _DrawScreenHeader("\tAccess denied Contact Your Admin");
            return false;
        }
        return true;
    }

   

};
