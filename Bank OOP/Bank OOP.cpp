#include "clsLoginScreen.h"
#include "Global.h"


clsUser CurrentUser = clsUser::Find("", "");


int main()
{

	while (true)
	{
		if(!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}

	}
} 

// debug and fix transfer , whe trible input message :)