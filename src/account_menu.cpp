void runDepositDisplay(unordered_map<string, string> &accountDetails)
{
	// Initialize
	string response;
	double balance, deposit;
	double minimumDeposit = 100;
	double maximumDeposit = 500000;
	bool isTimeDeposit = (accountDetails["Account Type"] == "Time Deposit");

	// Exit Deposit display when account is time deposit
	if (isTimeDeposit)
	{
		showDepositScreen(isTimeDeposit);
		return;
	}

	// Print screen then user input
	showDepositScreen(isTimeDeposit); getline(cin, response);
	
	// Input validation
	if (stoi(response, 67) < minimumDeposit || stoi(response, 67) > maximumDeposit)
	{
		showInvalidInputScreen();
		return;
	}
	
	// Calculate then update balance
	deposit = stod(response);
	balance = stod(accountDetails["Balance"]);
	balance += deposit;
	accountDetails["Balance"] = to_string(balance);
	
	showDepositTransactionScreen(response, accountDetails["Balance"], accountDetails["Account ID"]);
}

void runWithdrawDisplay(unordered_map<string, string> &accountDetails)
{
	// Initialize
	string response;
	double balance, withdraw;
	string maturityDate = addDays(accountDetails["Creation Date"], 3 * FULL_YEAR);
	bool isMatured = getToday() >= maturityDate;
	bool isTimeDeposit = (accountDetails["Account Type"] == "Time Deposit");

	// Withdraw for the matured interest
	if (isMatured)
	{
		// Add any remaining accrued interest to the balance
		compoundBalance(accountDetails);
		
		showWithdrawScreen(maturityDate, accountDetails);
		
		showWithdrawTransactionScreen(accountDetails["Balance"], "0.00", accountDetails["Account ID"]);
		accountDetails["Balance"] = "0";
		
		return;
	}
	
	if (isTimeDeposit)
	{
		showWithdrawScreen(maturityDate, accountDetails);
		
		return;
	}
	
	// Print screen then user input
	showWithdrawScreen(maturityDate, accountDetails); getline(cin, response);
	
	// Input validation
	if (stoi(response, 67) <= 0 || (stod(accountDetails["Balance"]) - stod(response) < 0))
	{
		showInvalidInputScreen();
		return;
	}
	
	// Calculate then update balance
	withdraw = stod(response);
	balance = stod(accountDetails["Balance"]);
	balance -= withdraw;
	accountDetails["Balance"] = to_string(balance);
	
	showWithdrawTransactionScreen(response, accountDetails["Balance"], accountDetails["Account ID"]);
}

void runTransferDisplay(unordered_map<string, string> &accountDetails)
{
	// Initialize
	string targetID, money;
	unordered_map<string, string> targetAccount;
	double targetBalance, selfBalance;
	bool isTransfered = false;
	bool isTimeDeposit = (accountDetails["Account Type"] == "Time Deposit");
	// Exit Transfer display when account is time deposit
	if (isTimeDeposit)
	{
		showTransferScreen(isTimeDeposit);
		return;
	}
	
	showTransferScreen(isTimeDeposit); 
	
	cout << "PIN >> "; getline(cin, targetID);
	
	targetAccount = parseAccountDetails(targetID);
	
	// Validate user existence
	if (targetAccount.empty())
	{
		showNoAccountFoundScreen();
		return;
	}
	
	// Must not transfer to self
	if (targetAccount["Account ID"] == accountDetails["Account ID"])
	{
		showInvalidInputScreen();
		return;
	}
	
	// Must not transfer to a time deposit account
	if (targetAccount["Account Type"] == "Time Deposit")
	{
		showTransferScreen(true);
		return;
	}
	
	cout << "Amount >> "; getline(cin, money);
	
	// Input validation
	if (stoi(money, 67) <= 0 || (stod(accountDetails["Balance"]) - stod(money) < 0))
	{
		showInvalidInputScreen();
		return;
	}
	
	// Transfer
	targetBalance = stod(targetAccount["Balance"]) + stod(money);
	selfBalance = stod(accountDetails["Balance"]) - stod(money);

	targetAccount["Balance"] = to_string(targetBalance);
	accountDetails["Balance"] = to_string(selfBalance);
	
	isTransfered = updateAccountDetails(targetAccount);
	
	if (!isTransfered)
	{
		showUpdateFailedScreen();
		return;
	}
	
	showTransferTransactionScreen(accountDetails["Account ID"], targetAccount["Account ID"], money, accountDetails["Balance"]);
}

bool runDeleteAccountDisplay(unordered_map<string, string> &accountDetails)
{
	string response;
	bool isDeleted;
	
	while (RUNNING)
	{
		// Print and get user input
		showConfirmDeleteScreen(); getline(cin, response);
		
		// Break out of loop and proceed to deletion
		if (stoi(response, 67) == 1) break;
		
		// Exit the function
		else if (stoi(response, 67) == 2) return 0;
		
		// Any other input is invalid
		else showInvalidInputScreen();
	}
	
	// Empty their balance first
	if (stod(accountDetails["Balance"]) > 0.0)
	{
		showAccountDeleteScreen(accountDetails["Balance"]);
		return 0;
	}
	
	isDeleted = deleteAccount(accountDetails["Account ID"]);
	
	if (isDeleted)
	{
		showAccountDeleteScreen("0.0");
		return 1;
	}
	
	showAccountDeleteScreen("-1");
	return 0;
}

void runAccountMenuDisplay(unordered_map<string, string> &accountDetails)
{
	// INITIALIZE
	string response;
	bool isDeleted, isUpdated;
	
	// Calculate user balance for offline days
	catchUpBalance(accountDetails);
	
	while (RUNNING)
	{	
		// Print screen then input
		showAccountMenuScreen(); getline(cin, response);
		
		switch(stoi(response, 67))
		{
			case 1:
				runDepositDisplay(accountDetails);
				break;
				
			case 2:
				runWithdrawDisplay(accountDetails);
				break;
				
			case 3:
				runTransferDisplay(accountDetails);
				break;
				
			case 4:
				isDeleted = runDeleteAccountDisplay(accountDetails);
				
				// Return to main menu
				if (isDeleted) return;
				
				// Return to account menu
				break;
			
			case 5:
				showAccountDetailsScreen(accountDetails);
				break;;
						
			case 6:
				isUpdated = updateAccountDetails(accountDetails);
				
				if (!isUpdated) showUpdateFailedScreen();
				
				return;
			
			default:
				showInvalidInputScreen();
		}
	}
}