//ProgrammingAdivces.com
//Mohammed Abu-Hadhoud

#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <limits>	
class clsInputValidate
{

public:

	  template <typename T> static bool  IsNumberBetween(T Number, T From, T To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	} 


	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			)
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	template <typename T> static T  ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n") 
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //'(': illegal token on right side of '::'
			cout << ErrorMessage;
		}
		return Number;
	}

	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}
		return Number;
	}

	


	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	} 

	static char ReadChar(string message)
	{
		cout << message; 
		char c;

		cin >> c;
		return c;
	} 

	static char ReadYesNoQuestionAnswer(string message)
	{
		char answer = toupper(ReadChar(message));
		while ( ! (answer == 'Y' || answer == 'N'))
		{
			answer = toupper(ReadChar(message));

		} 

		return answer;

	}


	static string ReadString(string message = "")
	{
		if (message != "")
			cout << message;
		string sInput;
		cin >> sInput;
		return sInput;
	}


};
