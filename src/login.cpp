#include <iostream>
#include <unordered_map>

void runLoginDisplay()
{
    // INITIALIZE
    string inputAccountID, inputPassword;
    unordered_map<string, string> accountDetails;
    
    // RETURN TO MAIN MENU IF DATABASE IS EMPTY
    if (!getAccountsCount(databasePath)) 
    {
        showDatabaseEmptyScreen();
        return;
    }
    
    while (RUNNING)
    {
        showLoginScreen();
		
		cout << "PIN >> "; getline(cin, inputAccountID);
		
		if (inputAccountID == "1")
		{
			return;
		}
        
        accountDetails = parseAccountDetails(inputAccountID);
		
        // RETURN TO LOGIN IF THE ID DOES NOT EXIST IN THE DATABASE
        if (accountDetails.empty())
        {
			showNoAccountFoundScreen();
			continue;
        }

		cout << "Password >> "; getline(cin, inputPassword);

		// Exit
		if (inputAccountID == "1")
		{
			return;
		}

        // PROCEED TO TRANSACTION IF THE PASSWORD ENTERED IS CORRECT
        if (isPasswordCorrect(inputPassword, accountDetails["Salt"], accountDetails["Hashed Password"]))
        {
            runAccountMenuDisplay(accountDetails);
            return;
        }

        // REPEAT THE LOGIN LOOP OTHERWISE
        showIncorrectPasswordScreen();
    }
}
