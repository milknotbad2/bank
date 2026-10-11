#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void showMainScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Welcome to CBank!           |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| [1] Login                   |\n";
	cout << "| [2] Create Account          |\n";
	cout << "| [3] Exit                    |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| SELECT CHOICE >             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}

void showAccountTypeSelectScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Select Account Type:        |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| [1] Savings                 |\n";
	cout << "| [2] Time Deposit            |\n";
	cout << "| [3] Cancel                  |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| SELECT CHOICE >             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}

void showDatabaseEmptyScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|      Database is Empty!     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(1s);
}

void showDatabaseOpenFailedScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|  Database Failed to Open... |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(1s);
}

void showAccountAddedScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Account Succesfully Created!|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(1s);
}

void showAccountNotAddedScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|     An Error Occured...     |\n";
	cout << "|  Failed to Create Account   |\n";
	cout << "|                             |\n";
	cout << "|      Please Try Again       |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(1s);
}

void showPasswordCreationScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Create your password:       |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Password:                   |\n";
	cout << "|                             |\n";
	cout << "| Confirm Password:           |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}

void showDepositScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Insert Initial Deposit:     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Deposit:                    |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Minimum of 100 pesos        |\n";
	cout << "| Maximum of 500,000 pesos    |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}

void showNoAccountFoundScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|    Account ID not found!    |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(1s);
}

void showInvalidInputScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|        Invalid Input!       |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(1s);
}

void showExitScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|  Thank you for using CBank! |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(1s);
}

void showIncorrectPasswordScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|     Incorrect Password!     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(1s);
}

void showLoginScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Enter Account Credentials:  |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| PIN:                        |\n";
	cout << "| Password:                   |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";	
	cout << "| [1] Exit                    |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
}

void showAccountMenuScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Select Transaction:         |\n";
	cout << "|                             |\n";
	cout << "| [1] Deposit                 |\n";
	cout << "| [2] Withdraw                |\n";
	cout << "| [3] Transfer                |\n";
	cout << "| [4] View Transaction History|\n";
	cout << "| [5] Delete Account          |\n";
	cout << "| [6] Exit                    |\n";
	cout << "|                             |\n";
	cout << "| SELECT CHOICE >             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}