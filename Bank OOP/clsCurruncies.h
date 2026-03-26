#pragma once
#include <string>
#include <iostream> 
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;
class clsCurrency
{
private:
	enum enMode { emptymode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	double _CurrencyRateToUSD;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperatror = "#//#")
	{ 
		vector<string> vCurrencyData = clsString::Split(Line, Seperatror);
		if (vCurrencyData.size() != 4)
			return _GetEmptyCurrencyObject();
		else
			return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
 

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperatror = "#//#")
	{
		string Line = "";
		Line += Currency.CountryName + Seperatror;
		Line += Currency.CurrencyCode + Seperatror;
		Line += Currency.CurrencyName + Seperatror;
		Line += to_string(Currency.CurrencyRateToUSD);
		return Line;
	} 

	static vector<clsCurrency>_LoadCurrenciesFromFile()
	{
		vector<clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); 
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	static bool _SaveCurrunciesDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsCurrency Currency : vCurrencies)
			{
				MyFile << _ConvertCurrencyObjectToLine(Currency) << endl;
			}
			MyFile.close();
			return true;
		}
		return false;
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile();
		for (clsCurrency & Currency : vCurrencies)
		{
			if (Currency.CountryName == this->CountryName)
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrunciesDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::emptymode, "", "", "", 0);
	}



public:
	
	string GetCountryName() { return _CountryName; }
	string GetCurrencyCode() { return _CurrencyCode; }
	string GetCurrencyName() { return _CurrencyName; }
	bool IsEmpty() { return _Mode == enMode::emptymode; }// Get the mode 

	double GetCurrencyRateToUSD() { return _CurrencyRateToUSD; }
	double SetCurrencyRateToUSD(double CurrencyRateToUSD) { return _CurrencyRateToUSD = CurrencyRateToUSD; }

	__declspec(property(get = GetCurrencyName)) string CurrencyName;
	__declspec(property(get = GetCurrencyCode)) string CurrencyCode;
	__declspec(property(get = GetCountryName)) string CountryName;
	__declspec(property(get = GetCurrencyRateToUSD, put = SetCurrencyRateToUSD)) double CurrencyRateToUSD;

	clsCurrency (enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, double CurrencyRateToUSD)
	{
		this->_Mode = Mode;
		this->_CountryName = CountryName;
		this->_CurrencyCode = CurrencyCode;
		this->_CurrencyName = CurrencyName;
		this->_CurrencyRateToUSD = CurrencyRateToUSD;
	} 

	static clsCurrency FindByCountryName(string CountryName)
	{
		CountryName = clsString::UpperAllString(CountryName);

		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile(); 

		for(clsCurrency & Currency : vCurrencies)
		{
			if (clsString::UpperAllString( Currency.CountryName )== CountryName)
				return Currency;
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCurrencyCode(string CountryCode)
	{
		CountryCode = clsString::UpperAllString(CountryCode);
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (clsString::UpperAllString( Currency.CurrencyCode) == CountryCode)
				return Currency;
		}
		return _GetEmptyCurrencyObject();
	}
	

	static vector<clsCurrency>GetCurrenciesList()
	{
		return _LoadCurrenciesFromFile();
	} 


void UpdateCurrencyRate(double NewCurrencyRateToUSD)
	{
		this->CurrencyRateToUSD = NewCurrencyRateToUSD;
		this->_Update();
	}
	static bool IsCurrencyExist(string CurrencyCode)
	{
		return FindByCurrencyCode(CurrencyCode).IsEmpty() == false;
	}
	
}; 

