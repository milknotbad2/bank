#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std::chrono;

void updateAccrual(unordered_map<string, string> &accountDetails, int days)
{
	double accruedInterest;
	double balance;
	float rate;
    
	// Fetch necessary values
	accruedInterest = stod(accountDetails["Accrued Interest"]);
	rate = stof(accountDetails["Interest Rate"]);
	balance = stod(accountDetails["balance"]);
	
	// Catch up accrual
	accruedInterest += balance * rate * (days/360);
	
	// Store it back
	accountDetails["Accrued Interest"] = to_string(accruedInterest);
	accountDetails["Last Accrual Date"] = addDays(accountDetails["Last Accrual Date"]);
}

void compoundBalance(unordered_map<string, string> &accountDetails)
{
	double accruedInterest;
    double balance;
 
	// Fetch necessary values 
	accruedInterest = stod(accountDetails["Accrued Interest"]);
	balance = stod(accountDetails["Balance"]); 
    
	// Add the accrued interest back to the spendable balance
    accountDetails["Balance"] = to_string(balance + accruedInterest)

	// Reset Accrued Interest back to zero
	accountDetails["Accrued Interest"] = "0";
	
	// Add thirty days to the Last Compounding Date
    accountDetails["Last Compounding Date"] = addDays(accountDetails["Last Accrual Date"], 30);   // moves the compounding day forward by 30 
}

string dateDifference(string date, string pastDate)
{
    int yearValue  = stoi(date.substr(0, 4));
    int monthValue = stoi(date.substr(5, 2));
    int dayValue   = stoi(date.substr(8, 2));

    int pastyearValue  = stoi(pastDate.substr(0, 4));
    int pastmonthValue = stoi(pastDate.substr(5, 2));
	int pastdayValue = stoi(pastDate.substr(8, 2));

	year_month_day dateValue{
		year{yearValue},
		month{static_cast<unsigned>(monthValue)},
		day{static_cast<unsigned>(dayValue)}
	};

	year_month_day pastDateValue{
		year{pastyearValue},
		month{static_cast<unsigned>(pastmonthValue)},
		day{static_cast<unsigned>(pastdayValue)}
	};

	sys_days dateDays = dateValue;
	sys_days dateDays2 = pastDateValue;

    days Difference = dateDays2 - dateDays;

    return to_string(Difference.count());
 }
