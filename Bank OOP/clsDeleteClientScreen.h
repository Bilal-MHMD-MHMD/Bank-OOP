#pragma once
#include "clsClientScreens.h" 
#include "clsBankClient.h" 
#include "clsUser.h"
#include"clsInputValidate.h"
class clsDeleteClientScreen :
    protected clsClientScreens
{

public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		// read account number , if it true uppload object print it thern read the new edition , then save it , the save ternally is calling update so every thing is great :) يلا روح صلي , نكمل غذا إن شاء الله
		string AccountNumber = clsString::ReadString("Please enter Account Number: ");


		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with account number " << AccountNumber << " is not found, please try again\n";
			AccountNumber = clsString::ReadString("Please enter Account Number: ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();


		char c = clsInputValidate::ReadYesNoQuestionAnswer("Do you want to Deletet this Client Y/N :");

		if (c == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nclient Deleted Successfully \n";
				clsClientScreens::_PrintClientCard(Client);
			}
			else
			{
				cout << "\n Error happens";
			}
		}





	}

};

