#pragma once

#include "clsUserScreens.h"
#include "Global.h" 
#include "clsUser.h" 

#include "clsMainScreen.h" 

class clsLoginScreen : protected clsUserScreens
{
private:
	static bool  _Login()
	{ 
		bool LoginFailed = false;
		int Trials = 3;
		string username, password;

		do
		{

			if (LoginFailed)
			{
				cout << "Invalid Username/Password try Again";
				--Trials;
			} 
			if (Trials == 0)
			{
				return false;
			}
				
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;	
			CurrentUser = clsUser::Find(username, password);
			LoginFailed = CurrentUser.IsEmpty();
			
		} while (LoginFailed); 
		clsUser::AddCurrentUserRecordToResisterFile();
		clsMainScreen::ShowMainMenue();
		return true;
	}


public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");

		
			if( _Login()==true)
			{ 
				//LoginRegister();
				return true;
			}
			else
			{
				return false;
			}
	}
};