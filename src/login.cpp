#include <iostream>
#include <fstream>

void displayDatabaseIsEmpty()
{
	cout << "========================\n";
	cout << "=	                    =\n";
	cout << "=	                    =\n";
	cout << "=  Database is empty!  =\n";
	cout << "=	                    =\n";
	cout << "=	                    =\n";
	cout << "========================\n";
}

/*
NOT DONE YET
*/
void runLoginDisplay()
{
	ifstream database("database.txt");
	
	if (isDatabaseEmpty(database)) 
	{
		displayDatabaseIsEmpty();
		
		return;
	}
	
	string userID, password;
	
}
