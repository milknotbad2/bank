#include <iostream>
#include <fstream>

/*
NOT DONE YET
*/
void runLoginDisplay()
{
	ifstream database("database.txt");
	
	if (!getAccountsCount()) 
	{
		showDatabaseEmptyScreen();
		return;
	}
	
	while (RUNNING)
	{
		showLoginScreen();
	}
	
}
