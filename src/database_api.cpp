#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <unordered_map>

#define DELIMITER '\x1F'

using namespace std::filesystem;

// DATABASE PATH IS RELATIVE TO WHERE THE MAIN APPLICATION IS RUNNING FROM
const string databasePath = "database/database.txt";
const string tempPath = "database/temp.txt";

/*
This is a helper function (you do NOT need to call this),
this fetches an entire line (1 account) in the database
ONLY IF it matches the accountID.

This returns an empty string (truth value: false) if no
account was found with the accountID.
*/
string getAccountDetails(const string &accountID)
{
	ifstream database(databasePath);
	string line;
	string id;
	
	// Check if the database.txt was succesfully opened
	if (!database)
	{
		showDatabaseOpenFailedScreen();
	}
	
	while (getline(database, line))
	{
		stringstream sstream(line);
		
		if (getline(sstream, id, DELIMITER))
		{
			if (id == accountID)
			{
				database.close();
				
				return line;
			}
		}
	}
	
	database.close();
	
	return "";
}

/*
Remember how the function getAccountDetails returns an entire line?
Yeah well that entire line is not useful since accessing each detail
is cumbersome.

So this function separates the entire line into a hash map (dictionary)
of details, to use this, you should:

	auto accountDetails = parseAccountDetails(accountID);
	
Which you can now use as:

	string accountID = accountDetails["Account ID"];
	string accountName = accountDetails["Account Name"];
	string accountType = accountDetails["Account Type"];
	string salt = accountDetails["Salt"];
	string hashedPassword = accountDetails["Hashed Password"];
	string balance = accountDetails["Balance"];

NOTE: the attributes are in string type, so the balance (which should
be a double) is a string. To fix this just do:

	#include <string>
	double balance = stod(accountDetails["Balance"])
	
stod means string to double
*/
unordered_map<string, string> parseAccountDetails(const string &accountID)
{
	string accountDetails = getAccountDetails(accountID);
	unordered_map<string, string> accountDetailsDictionary;
	
	if (accountDetails.empty())
	{
		// HANDLE THIS
		return accountDetailsDictionary;
	}
	
	stringstream sstream(accountDetails);
	string detail;
	string labels[] = {
		"Account ID",
		"Account Type",
		"Salt",
		"Hashed Password",
		"Balance",
		"Interest Rate",
		"Accrued Interest",
		"Last Accrual Date",
		"Last Compounding Date"
	};
	int counter = 0;
	
	while (getline(sstream, detail, DELIMITER))
	{
		accountDetailsDictionary[labels[counter]] = detail;
		counter++;
	}
	
	return accountDetailsDictionary;
}

int getAccountsCount(const string &path)
{
	ifstream database(path);
	string account;
	int counter = 0;
	
	// Check if the database.txt was succesfully opened
	if (!database)
	{
		showDatabaseOpenFailedScreen();
	}
	
	while (getline(database, account))
	{
		counter++;
	}
	
	return counter;
}

int getAccountIDValue(string accountID)
{
	const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
	
	char symbol1 = accountID[0];
    char symbol2 = accountID[1];
    char symbol3 = accountID[2];
    char symbol4 = accountID[3];
    char symbol5 = accountID[4];

    // Find value of each symbol
    int index1 = letters.find(symbol1);
    int index2 = letters.find(symbol2);
    int index3 = digits.find(symbol3);
    int index4 = digits.find(symbol4);
    int index5 = letters.find(symbol5);

    // Multiply by place values
    int symbolValue1 = index1 * (52 * 10 * 10 * 52);
    int symbolValue2 = index2 * (52 * 10 * 10);
    int symbolValue3 = index3 * (52 * 10);
    int symbolValue4 = index4 * 52;
    int symbolValue5 = index5;

    // Add
    return symbolValue1 + symbolValue2 + symbolValue3 + symbolValue4 + symbolValue5;
}

int getLastAccountValue()
{
	ifstream database(databasePath);
	string account;
	int accountValue = 0;
	
	// Check if the database.txt was succesfully opened
	if (!database)
	{
		return -1;
	}
	
	while (getline(database, account))
	{
		if (getAccountIDValue(account) + 1> accountValue)
		{
			accountValue = 1 + getAccountIDValue(account);
		}
	}
	
	return accountValue;
}

bool addAccount(const string &accountID,
				const string &accountType,
				const string &salt,
				const string &hashedPassword,
				const string &initialDeposit,
				const string &interestRate,
				const string &accruedInterest,
				const string &lastAccrualDate,
				const string &lastCompoundingDate)
{
	try
	{
		copy_file(databasePath, tempPath, copy_options::overwrite_existing);
	}
	catch (filesystem_error &e)
	{
		cerr << e.what();
		return 0;
	}
	
	ofstream temp(tempPath, ios::app);
	
	// Check if the temp.txt was succesfully opened
	if (!temp)
	{
		return 0;
	}
	
	temp << accountID << DELIMITER 
		 << accountType << DELIMITER
		 << salt << DELIMITER
		 << hashedPassword << DELIMITER
		 << initialDeposit << DELIMITER
		 << interestRate << DELIMITER
		 << accruedInterest << DELIMITER
		 << lastAccrualDate << DELIMITER
		 << lastCompoundingDate << '\n';
		 
	temp.close();
	
	// Greater than or equal means no account was added
	if (getAccountsCount(databasePath) >= getAccountsCount(tempPath))
	{
		return 0;
	}
	
	rename(tempPath, databasePath);
	
	return 1;
}

bool copyDatabaseWithout(const string &excludedID)
{
	// Open the database to copy
	ifstream database(databasePath);
	
	// Create the database to write the copy on
	ofstream temp(tempPath);
	
	// Initialize 
	string account;
	string excludedAccount = getAccountDetails(excludedID);
	
	// Check if the database.txt and temp.txt was succesfully opened/created
	if (!database || !temp)
	{
		showDatabaseOpenFailedScreen();
		return 0;
	}
	
	// Scan the entire database
	while (getline(database, account))
	{
		if (account == excludedAccount) continue;
		temp << account << '\n';
	}
	
	// Close files
	temp.close();
	database.close();
		
	rename(tempPath, databasePath);
	
	return 1;
}

bool deleteAccount(const string &account)
{
	return copyDatabaseWithout(account);
}

bool updateAccountDetails(const unordered_map<string, string> &accountDetails)
{
	bool isCopied = copyDatabaseWithout(accountDetails.at("Account ID"));
	
	if (!isCopied) return 0;
	
	return addAccount(accountDetails.at("Account ID"),
					  accountDetails.at("Account Type"),
					  accountDetails.at("Salt"),
					  accountDetails.at("Hashed Password"),
					  accountDetails.at("Balance"),
					  accountDetails.at("Interest Rate"),
					  accountDetails.at("Accrued Interest"),
					  accountDetails.at("Last Accrual Date"),
					  accountDetails.at("Last Compounding Date"));
}