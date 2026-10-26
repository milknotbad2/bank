#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <unordered_map>

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
	cout << "| [2] Time Deposit (3 years)  |\n";
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

void showAccountAddedScreen(const string &accountID)
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Account Succesfully Created!|\n";
	cout << "|                             |\n";
	cout << "|     Your Account PIN is:    |\n";
	cout << "|            " << accountID << "            |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(3s);
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

void showDepositScreen(bool isTimeDeposit)
{
	if (isTimeDeposit)
	{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|     Cannot Deposit in a     |\n";
		cout << "|    Time Deposit Account!    |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";
		
		this_thread::sleep_for(2s);
		return;
	}
	
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Insert Deposit:             |\n";
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

void showDepositTransactionScreen(const string &deposit, const string &newBalance, const string &accountID)
{
    stringstream sstream;
    string roundedBalance, roundedDeposit;
    const int maxSpaceBalance = 17;
    const int maxSpaceDeposit = 21;
    
    sstream << "P " << fixed << setprecision(2) << stod(newBalance) << " |\n";
    
	// Convert sstream to string object
    roundedBalance = sstream.str();

	// Handle big money
    if (roundedBalance.length() > maxSpaceBalance)
    {
        roundedBalance = ">P999999999.99 |\n";
    }
    
    sstream.clear();
    sstream.str("");
    
    sstream << "P " << fixed << setprecision(2) << stod(deposit) << " |\n";
    
    // Convert sstream to string object
    roundedDeposit = sstream.str();

	// Handle big money
    if (roundedDeposit.length() > maxSpaceDeposit)
    {
        roundedDeposit = ">P9999999999999.99 |\n";
    }
    
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|     Deposit Successful!     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Account PIN:          " << accountID << " |\n";
	cout << "| Deposit: " << string(maxSpaceDeposit - roundedDeposit.length(), ' ') << roundedDeposit;
	cout << "| New Balance: " << string(maxSpaceBalance - roundedBalance.length(), ' ') << roundedBalance;
	cout << "| Date (YY-MM-DD): " << getToday() << " |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(5s);
}

void showWithdrawScreen(const string maturityDate, const unordered_map<string, string> &accountDetails)
{
	if (accountDetails.at("Account Type") != "Time Deposit")
	{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "| Insert Withdrawal:          |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "| Withdraw:                   |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";
		cout << ">> ";
			
		return;
	}
	
	stringstream sstream;
	string roundedBalance;
	const int maxSpaceBalance = 20;
	
	if (getToday() != maturityDate)
	{
		double expectedBalance = stod(accountDetails.at("Balance"));
		double rate = stod(accountDetails.at("Interest Rate"));
		int timespan = dateDifference(maturityDate, accountDetails.at("Creation Date"));
		
		// Compute expected gains
		for (int i = 0; i <  timespan / FULL_MONTH; i++)
		{
			expectedBalance += expectedBalance * rate * (FULL_MONTH / (double)FULL_YEAR);
		}
		expectedBalance += expectedBalance * rate * ((timespan % FULL_MONTH) / (double)FULL_YEAR);
		
		sstream << "P " << fixed << setprecision(2) << expectedBalance << " |\n";
		
		roundedBalance = sstream.str();
		
		if (roundedBalance.length() > maxSpaceBalance)
		{
			roundedBalance = ">P99999999999.99 |\n";
		}
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|     Time Deposit has not    |\n";
		cout << "|         matured yet...      |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "| Date Today:      " << getToday() << " |\n";
		cout << "| Maturation Date: " << maturityDate << " |\n";
		cout << "| Expected: " << string(maxSpaceBalance - roundedBalance.length(), ' ') << roundedBalance;
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";

		this_thread::sleep_for(5s);
		
		return;
	}
	
	sstream << "P " << fixed << setprecision(2) << stod(accountDetails.at("Balance")) << " |\n";
		
	roundedBalance = sstream.str();
	
	if (roundedBalance.length() > maxSpaceBalance)
	{
		roundedBalance = ">P99999999999.99 |\n";
	}
	
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| 	Time Deposit has matured!  |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Date Today:      " << getToday() << " |\n";
	cout << "| Balance: " << string(maxSpaceBalance - roundedBalance.length(), ' ') << roundedBalance;
	cout << "|                             |\n";
	cout << "| Now withdrawing...          |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(5s);
}

void showWithdrawTransactionScreen(const string &withdraw, const string &newBalance, const string &accountID)
{
    stringstream sstream;
    string roundedBalance, roundedWithdraw;
    const int maxSpaceBalance = 17;
    const int maxSpaceWithdraw = 20;
    
    sstream << "P " << fixed << setprecision(2) << stod(newBalance) << " |\n";
    
	// Convert sstream to string object
    roundedBalance = sstream.str();

	// Handle big money
    if (roundedBalance.length() > maxSpaceBalance)
    {
        roundedBalance = ">P999999999.99 |\n";
    }
    
    sstream.clear();
    sstream.str("");
    
    sstream << "P " << fixed << setprecision(2) << stod(withdraw) << " |\n";
    
    // Convert sstream to string object
    roundedWithdraw = sstream.str();

	// Handle big money
    if (roundedWithdraw.length() > maxSpaceWithdraw)
    {
        roundedWithdraw = ">P999999999999.99 |\n";
    }
    
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|     Withdrawal Success!     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Account PIN:          " << accountID << " |\n";
	cout << "| Withdrew: " << string(maxSpaceWithdraw - roundedWithdraw.length(), ' ') << roundedWithdraw;
	cout << "| New Balance: " << string(maxSpaceBalance - roundedBalance.length(), ' ') << roundedBalance;
	cout << "| Date (YY-MM-DD): " << getToday() << " |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(5s);
}

void showAccountDetailsScreen(const unordered_map<string, string> &accountDetails)
{
	// Initialize
    stringstream sstream;
    string roundedBalance = accountDetails.at("Balance");
	const int maxSpaceBalance = 21;
    const int maxSpaceAccountType = 13;
	
	// Edit the formatting to two decimal places and add peso sign and border
    sstream << "P " << fixed << setprecision(2) << stod(accountDetails.at("Balance")) << " |\n";
    
	// Convert sstream to string object
    roundedBalance = sstream.str();

	// Handle big money
    if (roundedBalance.length() > maxSpaceBalance)
    {
        roundedBalance = ">P9999999999999.99 |\n";
    }

	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|            CBank            |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Account ID (PIN):     " << accountDetails.at("Account ID") << " |\n";
	cout << "| Account Type: " << string(maxSpaceAccountType - accountDetails.at("Account Type").length(), ' ') << accountDetails.at("Account Type") << " |\n";
	cout << "| Created on:      " << accountDetails.at("Creation Date") << " |\n";
	cout << "| Balance: " << string(maxSpaceBalance - roundedBalance.length(), ' ') << roundedBalance;
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(6s);
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
	cout << "| [4] Delete Account          |\n";
	cout << "| [5] View Account Details    |\n";
	cout << "| [6] Confirm and Exit        |\n";
	cout << "|                             |\n";
	cout << "| SELECT CHOICE >             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}

void showTransferScreen(bool isTimeDeposit)
{
	if (isTimeDeposit)
	{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|    Cannot Transfer in a     |\n";
		cout << "|    Time Deposit Account!    |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";
		
		this_thread::sleep_for(2s);
		return;
	}
	
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "| Transfer Transaction:       |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Recipient PIN:              |\n";
	cout << "| Amount:                     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
}

void showTransferTransactionScreen(const string &senderID, const string &targetID, const string &moneySent, const string &balance)
{
    stringstream sstream;
    string roundedMoney, roundedBalance;
	const int maxSpace = 17;
    
    sstream << "P " << fixed << setprecision(2) << stod(moneySent) << " |\n";
    
	// Convert sstream to string object
    roundedMoney = sstream.str();

	// Handle big money
    if (roundedMoney.length() > maxSpace)
    {
        roundedMoney = ">P999999999.99 |\n";
    }
    
    sstream.clear();
    sstream.str("");
    
    sstream << "P " << fixed << setprecision(2) << stod(balance) << " |\n";
    
    // Convert sstream to string object
    roundedBalance = sstream.str();

	// Handle big money
    if (roundedBalance.length() > maxSpace)
    {
        roundedBalance = ">P999999999.99 |\n";
    }
    
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|      Transfer Success!      |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "| Sender (You) PIN:     " << senderID << " |\n";
	cout << "| Receiver PIN:         " << targetID << " |\n";
	cout << "| Amount Sent: " << string(maxSpace - roundedMoney.length(), ' ') << roundedMoney;
	cout << "| New Balance: " << string(maxSpace - roundedBalance.length(), ' ') << roundedBalance;
	cout << "| Date (YY-MM-DD): " << getToday() << " |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	
	this_thread::sleep_for(10s);
}

void showConfirmDeleteScreen()
{
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|    Are you sure you want    |\n";
	cout << "|   to delete your account?   |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|    [1] Yes         [2] No   |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";
	cout << ">> ";
}


void showAccountDeleteScreen(string balance)
{
	if (stod(balance) > 0.0)
	{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|     Please withdraw your    |\n";
		cout << "|   remaining balance first.  |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";

		this_thread::sleep_for(2s);
		return;
	}
	
	if (stod(balance) < 0.0)
	{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|      An error occured...    |\n";
		cout << "|      Please try again.      |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";

		this_thread::sleep_for(2s);
		return;
	}
	
	cout << "_______________________________\n";
	cout << "|-----------------------------|\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|     Account Successfully    |\n";
	cout << "|           Deleted!          |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|-----------------------------|\n";
	cout << "|_____________________________|\n\n";

	this_thread::sleep_for(1s);
}

void showUpdateFailedScreen()
{
		cout << "_______________________________\n";
		cout << "|-----------------------------|\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|      An error occured...    |\n";
		cout << "|  Transactions not saved...  |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|                             |\n";
		cout << "|-----------------------------|\n";
		cout << "|_____________________________|\n\n";

		this_thread::sleep_for(2s);
}