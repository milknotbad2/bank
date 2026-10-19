#include <iostream>
#include <string>

string generateAccountID(int accountNumber)
{
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    
    /* 
	Calculate the unique ID components based on how many is already in the database. 
	ID format:
	
	[a-Z][a-Z][0-9][0-9][a-Z]
	
	Can support 14,060,800 accounts
	*/
	char symbol5 = letters[accountNumber % 52];
	char symbol4 = digits[(accountNumber / 52) % 10];
	char symbol3 = digits[(accountNumber / (52 * 10)) % 10];
	char symbol2 = letters[(accountNumber / (52 * 10 * 10)) % 52];
	char symbol1 = letters[(accountNumber / (52 * 10 * 10 * 52)) % 52];

    string accountID;
    
    accountID += symbol1;
    accountID += symbol2;
    accountID += symbol3;
    accountID += symbol4;
    accountID += symbol5;

    return accountID;
}

void runCreateAccountDisplay()
{
	// Initialize account attributes
	string response;
	string accountID, accountType, initialDeposit, interestRate, hashedPassword, salt, lastAccrualDate, lastCompoundingDate, accruedInterest;
	accruedInterest = "0";
	
	// Default interest rate and deposit min max
	string savingsRate = "0.001";
	string timeDepositRate = "0.035";
	double minimumDeposit = 100;
	double maximumDeposit = 500000;
	int lastAccountValue;
	
	// Account type selection
	while (RUNNING)
	{
		// Print screen and get user input
		showAccountTypeSelectScreen(); getline(cin, response);
		
		switch (stoi(response, 67))
		{
			case 1:
				accountType = "Savings";
				interestRate = savingsRate;
				break;
			
			case 2:
				accountType = "Time Deposit";
				interestRate = timeDepositRate;
				break;
			
			case 3:
				return;
				
			default:
				showInvalidInputScreen();
				continue;
		}
		break;
	}
		
	// Automatically generate account credentials
	salt = generateSalt();
	lastAccountValue = getLastAccountValue();
	
	// Database check
	if (lastAccountValue == -1) 
	{
		showDatabaseOpenFailedScreen();
		return;
	}
	
	accountID = generateAccountID(lastAccountValue);
	
	// Create password 
	while (RUNNING)
	{
		// Print screen and get user input
		showPasswordCreationScreen(); getline(cin, response);
		
		hashedPassword = createPassword(salt, response);
		
		// Confirm password
		cout << ">> "; getline(cin, response);
		
		if (isPasswordCorrect(response, salt, hashedPassword))
		{
			// Break out of password creation loop
			break;
		}
		showIncorrectPasswordScreen();
	}
	
	// Initial deposit
	while (RUNNING)
	{
		// Print screen and get user input
		showDepositScreen(); getline(cin, initialDeposit);
		
		if (stoi(initialDeposit, 67) >= minimumDeposit && stoi(initialDeposit, 67) <= maximumDeposit)
		{
			// Break out of deposit loop
			break;
		}
		showInvalidInputScreen();
	}

	// Set dates
	lastAccrualDate = getToday();
	lastCompoundingDate = getToday();
	
	// Create AND check if acccount is created successfully
	bool isAccountAdded = addAccount(
		accountID,
		accountType,
		salt,
		hashedPassword,
		initialDeposit,
		interestRate,
		accruedInterest,
		lastAccrualDate,
		lastCompoundingDate);
		
	if (!isAccountAdded)
	{
		showAccountNotAddedScreen();
		return;
	}
	
	showAccountAddedScreen(accountID);
}
