#pragma once
#include "clsClientScreens.h" 
#include "clsBankClient.h"
#include "clsString.h"
#include "clsUser.h" 

class clsAddNewClientScreen :
    protected clsClientScreens
{

public:
	static void ShowAddNewClientScreen()
	{ 

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		string AccountNumber = clsString::ReadString("Enter New Account Number");

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with account number " << AccountNumber << " already exists, please try again\n";
			AccountNumber = clsString::ReadString("Enter New Account Number: ");
		}

		clsBankClient Client = clsBankClient::GetNewBankClientObject(AccountNumber);

		clsScreen::_DrawScreenHeader("Add New Client");
		clsClientScreens::_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svFailedExistingObject:
			cout << "Failed to update client info because this account number already exist \n";
			break;

		case clsBankClient::enSaveResults::svSucceeded:
			cout << "Client info updated successfully\n";
			
			break;
		default:
			break;
		}

	}
};

