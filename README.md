# s-ite001-simple-banking-system
For ITE001 course. Final project.

== DB API FUNCTIONS ==

```cpp
unordered_map<string, string> parseAccountDetails(string accountID);
int getAccountsCount();
string getAccountDetails(string AccountID); 
```

== SECURITY RELATED STUFF ==

```cpp
string createPassword(string salt, string password);
bool isPasswordCorrect(string passwordToCheck, string salt, string hashedPassword);
string generateSalt();
```

== UNFINISHED (TO-DO) ==

```cpp
void createDummyDB();
string generateID();
void createAccount();
ofstream createTempDatabase();
void runMainDisplay();
void runLoginDisplay();
```
