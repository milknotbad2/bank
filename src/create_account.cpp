#include <iostream>
#include <string>

string generateAccountId(int accountNumber)
{
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /* 
	Calculate the unique ID components based on how many is already in the database. 
	ID format:
	
	[a-Z][a-Z][0-9][0-9][a-Z]
	
	Can support 14,060,800 accounts
	*/
    char firstLetter = letters[(accountNumber / (52 * 100 * 52)) % 52];
    char secondLetter = letters[(accountNumber / (52 * 100)) % 52];
    int middleNumber = (accountNumber / 52) % 100;
    char lastLetter = letters[accountNumber % 52];

    // Assemble the unique ID
    string accountId;
    accountId += firstLetter;
    accountId += secondLetter;

    if (middleNumber < 10)
    {
        accountId += "0";
    }

    accountId += to_string(middleNumber);
    accountId += lastLetter;

    return accountId;
}

void runCreateAccountDisplay()
{
	// Initialize account attributes
	string response;
	string accountID, accountType, initialDeposit, interestRate, hashedPassword, salt, lastAccrualDate, lastCompoundingDate, accruedInterest;
	accruedInterest = "0";
	
	// Default interest rate
	string savingsRate = "0.001";
	string timeDepositRate = "0.035";
	
	while (RUNNING)
	{
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
		
	salt = generateSalt();
	accountID = generateAccountId(getAccountsCount(databasePath));
	
	while (RUNNING)
	{
		showPasswordCreationScreen(); getline(cin, response);
		
		hashedPassword = createPassword(salt, response);
		
		cout << ">> "; getline(cin, response);
		
		if (isPasswordCorrect(response, salt, hashedPassword))
		{
			response = "";
			break;
		}
		
		showIncorrectPasswordScreen();
	}
	
	while (RUNNING)
	{
		showDepositScreen(); getline(cin, initialDeposit);
		
		if (stoi(initialDeposit, 67) >= 100 && stoi(initialDeposit, 67) <= 500000)
		{
			break;
		}
		
		showInvalidInputScreen();
	}
	
	lastAccrualDate = "";
	lastCompoundingDate = "";
	
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
	
	showAccountAddedScreen();
}
