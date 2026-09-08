# s-ite001-simple-banking-system
For ITE001 course. Final project.

== FUNCTIONS ==

int getBalance();
int getAccountType();
int getAccountName();
string getAccountDetails(string AccountID);\t\t RETURNS A STRING OF THE FORM ```<account id> \x1F <account name> \x1F <account type> \x1F <salt> \x1F <hashed password> \x1F <balance>```
bool isPasswordCorrect(string inputPassword); 
