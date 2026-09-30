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
	int response;
	
	while (RUNNING)
	{
		showMainScreen();
		
		if (!(cin >> response) || response < 1 || response > 3)
		{
			cin.clear();
			cin.ignore(200, '\n');
			continue;
		}
		
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
		}
	}
}