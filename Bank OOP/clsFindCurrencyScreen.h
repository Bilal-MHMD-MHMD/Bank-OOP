#pragma once
#include <iostream>
#include "clsCurrenciesScreen.h"
#include "clsCurruncies.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsCurrenciesScreen
{
private:
    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrencyCard(Currency);
        }
        else
        {
            cout << "\nCurrency Not Found :-(\n";
        }
    }

public:
    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = clsInputValidate::ReadNumberBetween<short>(1, 2, "Invalid, Enter [1] or [2]: ");

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            string CountryName;
            cout << "\nPlease Enter Country Name: ";
            CountryName = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountryName(CountryName);
            _ShowResults(Currency);
        }
    }
};