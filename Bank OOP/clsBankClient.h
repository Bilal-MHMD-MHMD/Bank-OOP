#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
#include"Global.h"
// Forward declaration needed if you plan to use CurrentUser ptr
class clsUser;
extern clsUser CurrentUser;

using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    double _Balance;
    bool _markForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = " #//# ")
    {
        vector<string> vClientData = clsString::Split(Line, Seperator);
        return clsBankClient(clsBankClient::enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(EmptyMode, "", "", "", "", "", "", 0.0);
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = " #//# ")
    {
        string line = "";
        line += Client.GetAccountNumber() + Seperator;
        line += Client.GetPinCode() + Seperator;
        line += Client.GetFirstName() + Seperator;
        line += Client.GetLastName() + Seperator;
        line += Client.GetEmail() + Seperator;
        line += Client.GetPhone() + Seperator;
        line += to_string(Client.GetBalance());

        return line;
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    vClients.push_back(Client);
                }
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            for (clsBankClient& Client : vClients)
            {
                if (!Client._markForDelete)
                {
                    string Line = _ConverClientObjectToLine(Client);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& Client : vClients)
        {
            if (Client.AccountNumber == this->AccountNumber)
            {
                Client = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
    }

    void _AddDataLinetToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _AddNew()
    {
        _AddDataLinetToFile(_ConverClientObjectToLine(*this));
    }

public:


    clsBankClient(enMode Mode, string AccountNumber, string PinCode, string FirstName, string LastName, string Email, string Phone, double Balance)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        this->_Mode = Mode;
        this->_AccountNumber = AccountNumber;
        this->_PinCode = PinCode;
        this->_Balance = Balance;
    }

    bool IsEmpty()
    {
        return _Mode == EmptyMode;
    }

    string GetAccountNumber()
    {
        return _AccountNumber;
    }
    __declspec(property(get = GetAccountNumber)) string AccountNumber;

    string GetPinCode()
    {
        return _PinCode;
    }

    void SetPinCode(string PinCode)
    {
        this->_PinCode = PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    double GetBalance()
    {
        return _Balance;
    }

    void SetBalance(double Balance)
    {
        this->_Balance = Balance;
    }
    __declspec(property(get = GetBalance, put = SetBalance)) double Balance;

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        return !clsBankClient::Find(AccountNumber).IsEmpty();
    }

    enum enSaveResults { svFaileddEmptyObject = 0, svFailedExistingObject = 1, svSucceeded = 2 };

    enSaveResults Save()
    {
        switch (this->_Mode)
        {
        case EmptyMode:
            return svFaileddEmptyObject;

        case UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;

        case AddNewMode:
            _AddNew();
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSucceeded;
        }
        return svFaileddEmptyObject; // Fallback
    }

    static clsBankClient GetNewBankClientObject(string AccountNumber)
    {
        return clsBankClient(AddNewMode, AccountNumber, "", "", "", "", "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient>vClients = clsBankClient::_LoadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.AccountNumber == this->AccountNumber)
            {
                this->_markForDelete = true;
                break;
            }
        }

        clsBankClient::_SaveClientsDataToFile(vClients);
        *this = clsBankClient::_GetEmptyClientObject();

        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        double TotalBalance = 0;
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& Client : vClients)
        {
            TotalBalance += Client.Balance;
        }
        return TotalBalance;
    }

    bool Withdraw(double Amount)
    {
        if (Amount > Balance)
        {
            return false;
        }
        else
        {
            this->Balance -= Amount;
            this->Save();
            return true;
        }
    }

    bool Deposit(double Amount)
    {
        this->Balance += Amount;
        this->Save();
        return true;
    }

    bool Transfer(double Amount, clsBankClient& DestinationClient)
    {
        if (DestinationClient.IsEmpty())
        {
            return false;
        }
        else
        {
            if (this->Withdraw(Amount))
            {
                DestinationClient.Deposit(Amount);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    struct stTransferRecord
    {
        string DateTime;
        string FromAccountNumber;
        string ToAccountNumber;
        double Amount;
        double FromAccountBalanceAfterTransfer;
        double ToAccountBalanceAfterTransfer;
        string AdminUserName;
    };
    static void AddTransferRecordToFile(stTransferRecord& TransferRecord)
    {
        string seperator = "#//#";
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << _GetTransferLine(TransferRecord, seperator) << endl;
            MyFile.close();
        }
    }

    static string _GetTransferLine(stTransferRecord& TransferRecord, string Seperator = "#//#")
    {
        string TransferLine = "";
        TransferLine += TransferRecord.DateTime + Seperator;
        TransferLine += TransferRecord.FromAccountNumber + Seperator;
        TransferLine += TransferRecord.ToAccountNumber + Seperator;
        TransferLine += to_string(TransferRecord.Amount) + Seperator;  
		TransferLine += to_string(TransferRecord.FromAccountBalanceAfterTransfer) + Seperator;
		TransferLine += to_string(TransferRecord.ToAccountBalanceAfterTransfer) + Seperator;
		TransferLine += TransferRecord.AdminUserName ;

        return TransferLine;
    }

    static stTransferRecord _ConvertLineToTransferRecord(string Line, string Seperator = "#//#")
    {
        stTransferRecord TransferRecord;
        vector<string> vTransferData = clsString::Split(Line, Seperator);
        TransferRecord.DateTime = vTransferData[0];
        TransferRecord.FromAccountNumber = vTransferData[1];
        TransferRecord.ToAccountNumber = vTransferData[2];
        TransferRecord.Amount = stof(vTransferData[3]);
        // Avoid out of bound exceptions index errors.
        if (vTransferData.size() > 4) {
            TransferRecord.FromAccountBalanceAfterTransfer = stof(vTransferData[4]);
            TransferRecord.ToAccountBalanceAfterTransfer = stof(vTransferData[5]); 
            TransferRecord.AdminUserName = vTransferData[6];
        }

      
        return TransferRecord;
    }

    static vector <stTransferRecord> GetTransferLogList()
    {
        vector<stTransferRecord> vTransferRecords;
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    stTransferRecord TransferRecord = _ConvertLineToTransferRecord(Line);
                    vTransferRecords.push_back(TransferRecord);
                }
            }
            MyFile.close();
        }
        return vTransferRecords;
    }
};