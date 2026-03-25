#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(23) << left << Record.DateTime;
        cout << "| " << setw(8) << left << Record.FromAccountNumber;
        cout << "| " << setw(8) << left << Record.ToAccountNumber;
        cout << "| " << setw(8) << left << Record.Amount;
        cout << "| " << setw(10) << left << Record.FromAccountBalanceAfterTransfer;
        cout << "| " << setw(10) << left << Record.ToAccountBalanceAfterTransfer;
        cout << "| " << setw(10) << left << Record.AdminUserName;

         
    }

public:

    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferRecord> vTransferRecord = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        
    
         cout << "| " << left << setw(10 ) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRecord.size() == 0)
        {
            cout << "\t\t\t\tNo Transfers Available In the System!";
        }
        else
        {
            for (clsBankClient::stTransferRecord Record : vTransferRecord)
            {
                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};