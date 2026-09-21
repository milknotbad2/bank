#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define DELIMITER '\x1F'

void createDummyDB()
{
	ofstream database("database.txt");
	
	string databaseMatrix[6][6] = {
		// {"a7293", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		// {"b6429", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		// {"c6212", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		// {"d7473", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		// {"e2341", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		// {"f5322", "Cornelius", "Time Deposit", "3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56", string(""), "350"},
		
		{"a7293", "b6429", "c6212", "d7473", "e2341", "f5322"},
		{"Cornelius", "Maximillius", "Retinious", "Jaki", "Nilius", "Habanero Shaitsuke"},
		{"Time Deposit", "Savings", "Savings", "Time Deposit", "Savings", "Savings"},
		{
			"3127b16071221b4d6c6b7d08f649b635c6871a90ad1393b6f383d9b2159236fa9d09db9a4681dba5a61da506193108397e7febc8b57c7fc263f1fc3a36467a56",
			"2bbe3aa3a4574023c76e657a6fd78d4ee56bc19d723fed8b892a58886a5060bd74fdfba3f82d50d2c9699bf02ae12c549d41c81d5fda3ee66ab8bafc6111c736",
			"a67d4cc440e4f5fa8c947cc0637eec9f24de982cb696a804c99f731f3a6cea6f216229ba908c6ab7e5dbe09f4df2efaaa73ff5f345e89198b4ece3f8d8a0e",
			"ac8f876e3d46a3498dac7629a0a5f74af8ffe9d2e63ede4918073056ba1900de5c1ad365aafe24fb26060ee1506b7ba168f9388be23d45866619cddb6630c2bb",
			"fd9e0ecc256c9651984bfa5a19763408825278387105aeaf6d59c1c654ea6723aeb1437fe1040b1255d3ce11a3a3939dfa8ca581a5ec87dc20832b181e61c16",
			"c5a1a69388410c37eec86468d21e7442ba8638caa5cbc25df049eda63c2bc96d4e2101a115c2d2dc3fb7b7bae51546ae34eac2aae23f5bd53c12aab147d10a"
		},
		{
			"",
			"",
			"",
			"",
			picosha2::hash256_hex_string(string("fd9e0ecc256c9651984bfa5a19763408825278387105aeaf6d59c1c654ea6723aeb1437fe1040b1255d3ce11a3a3939dfa8ca581a5ec87dc20832b181e61c16") + string("pass123")),
			""
		},
		{"350", "1000", "250", "3000", "1500", "200"}
	};

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			database << databaseMatrix[j][i] << DELIMITER;
		}		
		database << '\n';
	}
}

/*
This is a helper function (you do NOT need to call this),
this fetches an entire line (1 account) in the database
ONLY IF it matches the accountID.

This returns an empty string (truth value: false) if no
account was found with the accountID.
*/
string getAccountDetails(string accountID)
{
	ifstream database("database.txt");
	string line;
	string id;
	
	if (!database.is_open())
	{
		// HANDLE THIS
	}
	
	while (getline(database, line))
	{
		stringstream sstream(line);
		
		if (getline(sstream, id, '\x1F'))
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
		"Account Name",
		"Account Type",
		"Salt",
		"Hashed Password",
		"Balance"
	};
	int counter = 0;
	
	while (getline(sstream, detail, DELIMITER))
	{
		accountDetailsDictionary[labels[counter]] = detail;
		counter++;
	}
	
	return accountDetailsDictionary;
}

int getAccountsCount()
{
	ifstream database("database.txt");
	string account;
	int counter = 0;
	
	while (getline(database, account))
	{
		counter++;
	}
	
	return counter;
}