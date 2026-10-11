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
string getAccountDetails(string accountID)
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
unordered_map<string, string> parseAccountDetails(string accountID)
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


int getAccountsCount(string path)
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

bool addAccount(string accountID,
				string accountType,
				string salt,
				string hashedPassword,
				string initialDeposit,
				string interestRate,
				string accruedInterest,
				string lastAccrualDate,
				string lastCompoundingDate)
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
