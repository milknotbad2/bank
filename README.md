# s-ite001-simple-banking-system
For ITE001 course. Final project.

== FUNCTIONS ==

string getAccountDetails(string AccountID);        <-- RETURNS A STRING OF THE FORM ```<account id> \x1F <account name> \x1F <account type> \x1F <salt> \x1F <hashed password> \x1F <balance>```
bool isPasswordCorrect(string inputPassword); 
