

// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void createAccount();
    int main (){
        int savings, time_depost, deposit, balance;
        char account;

        cout << "Create a new account (y/n):"; 
        cin >> account;

        if (account == 'y' || account == 'Y')
        {
            createAccount();
        }
        else
        {
            cout << "Account creation canceled.\n";
        }


    }

    void createAccount() {
    string username;
    string password;
    int account_type;
    int deposit, balance;
    cout << "Enter username:";
    cin >> username;

    cout << "Enter password:";
    cin >> password;

    cout << "Choose account type 1 for savings or 2 for time deposit:";
    cin >> account_type;

    if (account_type == 1) {
        cout << "You have chosen a savings account.\n";
    
    }
    else if (account_type == 2) {
        cout << "You have chosen a time deposit account.\n";

    }
    else {
        cout << "Invalid account type. Please choose 1 for savings or 2 for time deposit.\n";
        return;
    }

        cout << "deposit amount: ";
        cin >> deposit;

        balance = deposit;
    
        cout << "Your account balance is: " << balance << endl;


    ofstream file("accounts.txt", ios::app);

    file << username << " " << password << " " << account_type << " " << balance << endl;

    file.close();

    cout << "Account created successfully!\n";
        
    }
