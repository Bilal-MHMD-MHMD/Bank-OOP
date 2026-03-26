#pragma once
#include <iostream>
#include "clsCurrenciesScreen.h"
#include "clsCurruncies.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsCurrenciesScreen
{
private:
    static double _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        return clsInputValidate::ReadNumber<double>();
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;
        cout << Message;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCurrencyCode(CurrencyCode);
    }


    static void _PrintCalculationsResults(double Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrintCurrencyCard(CurrencyFrom);

        double AmountInUSD = Amount / CurrencyFrom.CurrencyRateToUSD;

        if (CurrencyTo.CurrencyCode == "USD")
        {
            cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << AmountInUSD << " USD\n";
            return;
        }

        cout << "\nConverting from USD to:\n";
        _PrintCurrencyCard(CurrencyTo);

        double AmountInCurrencyTo = AmountInUSD * CurrencyTo.CurrencyRateToUSD;
        cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << AmountInCurrencyTo << " " << CurrencyTo.CurrencyCode << "\n";
    }


public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (tolower(Continue) == 'y')
        {
            system("cls");
            _DrawScreenHeader("\tUpdate Currency Rate Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            double Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }
    }
};