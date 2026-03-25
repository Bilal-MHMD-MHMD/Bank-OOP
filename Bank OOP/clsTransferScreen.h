#pragma once
#include "clsClientScreens.h"
#include "clsBankClient.h" 
#include "clsDate.h"
class clsTransferScreen : protected clsClientScreens
{


	static double _ReadAmount(clsBankClient SourceClient)
	{ 
		float amount = 0;
		
			cout << "\nEnter the Amount to Transfer";
			amount = clsInputValidate::ReadNumber<float>();

			while (SourceClient.Balance < amount)
		 {
			 cout << "\nAmount Exceeds the Balance, Enter another Amount";
			 amount = clsInputValidate::ReadNumber<float>();
		 }
		return amount;
	} 

	static void _FillTransferRecord(clsBankClient::stTransferRecord& Record, clsBankClient SourceClient, clsBankClient DestinationClient, float Amount)
	{
		Record.DateTime = clsDate::DateToString(clsDate::GetSystemDateTimeString());
		Record.FromAccountNumber = SourceClient.AccountNumber;
		Record.ToAccountNumber = DestinationClient.AccountNumber;
		Record.Amount = Amount;
		Record.FromAccountBalanceAfterTransfer = SourceClient.Balance;
		Record.ToAccountBalanceAfterTransfer = DestinationClient.Balance; 
		Record.AdminUserName = CurrentUser.UserName;
	}



public:
static	void ShowTransferScreen()
	{ 
	clsClientScreens::_DrawScreenHeader("Transfer Screen");
	cout << "\nEnter Account Number to Transfer From :";
	 
	

	clsBankClient SourceClient =
			clsBankClient::Find(clsClientScreens::_ReadExistingAccountNumber());  

	_PrintClientCard(SourceClient);

	float amount = _ReadAmount(SourceClient);
	

	cout << "\nEnter Account Number to Transfer to : \n";
string DestinationAccountNumber = clsClientScreens::_ReadExistingAccountNumber(); 
clsBankClient DestinationClient = clsBankClient::Find(DestinationAccountNumber);
_PrintClientCard(DestinationClient);

	char answer = clsInputValidate::ReadYesNoQuestionAnswer("\n Are you sure ,you want to transfer ?Y/N");

	if (answer == 'Y')
	{
		if( SourceClient.Transfer(amount , DestinationClient))
		{
			cout << "\nTransfer Succeeded";
			_PrintClientCard(SourceClient); 
			_PrintClientCard(DestinationClient); 

			clsBankClient::stTransferRecord Record;

			_FillTransferRecord(Record, SourceClient, DestinationClient, amount); 
			clsBankClient::AddTransferRecordToFile(Record);
		}
		else
		{
			cout << "\nTransfer Failed";
		}
	}
	else
	{
		cout << "\nTransfer Cancelled";
	}

	} 

 


};

