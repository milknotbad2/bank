#define RUNNING true
// #define CLEAR_SCREEN() cout << "\x1b[2J\x1b[H"

#include "security.cpp"

// INCLUDE "security.cpp" IS ABOVE BECAUSE IT INCLUDES osrandom AND DOES NOT MIX WELL WITH using namespace std;
using namespace std;

#include "screen.cpp"
#include "database_api.cpp"
#include "tools.cpp"
#include "create_account.cpp"
#include "login.cpp"

// DECLARE
void runMainDisplay();

// ENTRY POINT OF THE PROGRAM
int main()
{
	runMainDisplay();
	
	return 0;
}

// MAIN MENU THAT INCLUDES THE FRONTEND AND BACKEND
void runMainDisplay()
{
	string response;
	
	while (RUNNING)
	{
		showMainScreen();

		getline(cin, response);
		
		switch (stoi(response, 67))
		{
			case 1:
				runLoginDisplay();
				break;
				
			case 2:
				runCreateAccountDisplay();
				break;
				
			case 3:
				return;
			
			default:
				showInvalidInputScreen();
		}
	}
}
