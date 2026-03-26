#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurruncies.h"

using namespace std;

class clsCurrenciesScreen : protected clsScreen
{
protected:
    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.CountryName;
        cout << "\nCode       : " << Currency.CurrencyCode;
        cout << "\nName       : " << Currency.CurrencyName;
        cout << "\nRate(1$)   : " << Currency.CurrencyRateToUSD;
        cout << "\n_____________________________\n";
    }
};