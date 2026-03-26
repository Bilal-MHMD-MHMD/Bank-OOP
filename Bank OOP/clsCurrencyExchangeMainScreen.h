#pragma once
#include "clsScreen.h" 
#include <iostream>
#include <iomanip>
#include "clsUser.h" 
#include "clsInputValidate.h" 
#include "clsMainScreen.h" 
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;
class clsCurrencyExchangeMainScreen :
    protected clsScreen
{
private:
	enum enCurrencyExchangeMainOptions
    { enListCurrencies = 1, enFindCurrency = 2, enUpdateRate = 3, enCurrencyCalculator = 4, enExit = 5 };

    static int _ReadCurrencyExchangeMainMenuOption()
    {
        cout <<  "Choose what do you want to do? [1 to 5]: ";
        return clsInputValidate::ReadNumberBetween<int>(enCurrencyExchangeMainOptions::enListCurrencies, enCurrencyExchangeMainOptions::enExit, "Enter a valid option [1 to 5]: ");
    } 

 static void _ListCurrencies()
    {
	 clsListCurrenciesScreen::ShowCurrenciesListScreen();
     }
 static void _FindCurrencyScreen()
 {
	 clsFindCurrencyScreen::ShowFindCurrencyScreen();
 }
 static void _UpdateCurrencyRateScreen()
 {
	 clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();

 }
 static void _CurrencyCalculatorScreen()
 {
	 clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
 }
 static void _GoBackToCurrencyMenu()
 { 
     cout << "\n\nPress any key to go back to Currencies Menue...";
	 system("pause>0");
     ShowCurrencyExchangeMainScreen();
 }
   static void _PerformCurrencyExchangeMainMenuOption(enCurrencyExchangeMainOptions Option)
    {
        switch (Option)
        {
        case enCurrencyExchangeMainOptions::enListCurrencies:
            system("cls");
			_ListCurrencies();
            _GoBackToCurrencyMenu();
			break;
        case enCurrencyExchangeMainOptions::enFindCurrency:
            system("cls");
			_FindCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;
        case enCurrencyExchangeMainOptions::enUpdateRate:
            system("cls");
            _UpdateCurrencyRateScreen();
            _GoBackToCurrencyMenu();
            break;
        case enCurrencyExchangeMainOptions::enCurrencyCalculator:
            system("cls");
            _CurrencyCalculatorScreen();
            _GoBackToCurrencyMenu();
            break;
        case enCurrencyExchangeMainOptions::enExit:
            system("cls");
            break;
        }
   }

public:

 static   void ShowCurrencyExchangeMainScreen()
     {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
            return; 
        system("cls");
        _DrawScreenHeader("Currency Exchange Main Screen");
        cout << setw(37) << left << "" << " ============================================" << endl;
      cout << setw(37) << left << "" <<"[1] List Currencies." << endl;
      cout << setw(37) << left << "" << "[2] Find Currency." << endl;
      cout << setw(37) << left << "" << "[3] Update Rate." << endl;
      cout << setw(37) << left << "" << "[4] Currency Calculator." << endl;
      cout << setw(37) << left << "" << "[5] Go Back To Main Menue." << endl;
      cout << setw(37) << left << "" << " ============================================" << endl;

		 _PerformCurrencyExchangeMainMenuOption((enCurrencyExchangeMainOptions)_ReadCurrencyExchangeMainMenuOption());
	}
};

             