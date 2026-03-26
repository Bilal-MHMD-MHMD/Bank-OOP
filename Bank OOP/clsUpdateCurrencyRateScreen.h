#pragma once
#include <iostream>
#include "clsCurrenciesScreen.h"
#include "clsCurruncies.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsCurrenciesScreen
{
public:
    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\tUpdate Currency Rate Screen");

        string CurrencyCode;
        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        _PrintCurrencyCard(Currency);

        cout << "\nAre you sure you want to update the rate of this currency y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            cout << "\nEnter New Rate: ";
            double NewRate = clsInputValidate::ReadNumber<double>();

          
			Currency.UpdateCurrencyRate(NewRate);
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrencyCard(Currency);
        }
    }
};