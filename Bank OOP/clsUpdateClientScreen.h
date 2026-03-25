#pragma once
#include "clsClientScreens.h"
#include "clsClientScreens.h"
#include "clsUser.h"
class clsUpdateClientScreen :
	protected clsClientScreens
{

public :
	static void ShowUpdateClientScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		// read account number , if it true uppload object print it thern read the new edition , then save it , the save ternally is calling update so every thing is great :) ??? ??? ??? , ???? ??? ?? ??? ????
		string AccountNumber = clsString::ReadString("Please enter Account Number: ");


		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with account number " << AccountNumber << " is not found, please try again\n";
			AccountNumber = clsString::ReadString("Please enter Account Number: ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();

		cout << "___ Update Client Info ___\n";

		clsClientScreens::_ReadClientInfo(Client);

		clsBankClient::enSaveResults  SaveResults = Client.Save();
		switch (SaveResults)
		{
		case clsBankClient::enSaveResults::svFaileddEmptyObject:
			cout << "Failed to update client info because client object is empty\n";
			break;

		case clsBankClient::enSaveResults::svSucceeded:
			cout << "Client info updated successfully\n";
			break;
		default:
			break;
		}

	}

};