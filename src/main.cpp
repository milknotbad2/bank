#define RUNNING true
// #define CLEAR_SCREEN() cout << "\x1b[2J\x1b[H"

#include "security.cpp"

using namespace std;

#include "databaseAPI.cpp"
#include "screen.cpp"
#include "login.cpp"
#include "tools.cpp"

void runMainDisplay();

int main()
{
	runMainDisplay();
	
	return 0;
}

void runMainDisplay()
{
	string response;
	
	while (RUNNING)
	{
		showMainScreen();

		sin >> response;
		
		switch (response)
		{
			case 1:
				runLoginDisplay();
				break;
				
			case 2:
				// RUN CREATE ACCOUNT
				break;
				
			case 3:
				return;
			
			default:
				// SHOW INVALID INPUT SCREEN
		}
	}
}
