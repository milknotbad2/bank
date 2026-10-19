#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

#define FULL_MONTH 30

using namespace std::chrono;

string getToday()
{
	// Get current UTC date and time
	auto now = system_clock::now(); 

	// Convert UTC date and time to PH date and time
    auto local = current_zone()->to_local(now);  

	// Remove time components
    auto today = floor<days>(local);

	// Convert days type to year month day type
	year_month_day calendarDate{today}; 

	// Put into string stream to automatically convert to YY-MM-DD
    stringstream sstream;
    sstream << calendarDate; 

    return sstream.str(); 
}

int dateDifference(string date, string pastDate)
{
    int yearValue  = stoi(date.substr(0, 4));
    unsigned int monthValue = stoi(date.substr(5, 2));
    unsigned int dayValue   = stoi(date.substr(8, 2));

    int pastyearValue  = stoi(pastDate.substr(0, 4));
    unsigned int pastmonthValue = stoi(pastDate.substr(5, 2));
	unsigned int pastdayValue = stoi(pastDate.substr(8, 2));

	year_month_day dateValue{
		year{yearValue},
		month{(monthValue)},
		day{(dayValue)}
	};

	year_month_day pastDateValue{
		year{pastyearValue},
		month{(pastmonthValue)},
		day{(pastdayValue)}
	};

	sys_days dateDays = dateValue;
	sys_days dateDays2 = pastDateValue;

    days difference = dateDays2 - dateDays;

    return difference.count();
 }
 
 string addDays(string date, int numDays)
{
    int yearValue = stoi(date.substr(0, 4));
    unsigned int monthValue = stoi(date.substr(5, 2));
    unsigned int dayValue = stoi(date.substr(8, 2));

    year_month_day dateValue{
        year{yearValue},
        month{monthValue},
        day{dayValue}
    };

    if (!dateValue.ok()) return "Invalid date";

    sys_days result = sys_days{dateValue} + chrono::days{numDays};

    year_month_day newDate{result};

    return to_string(int(newDate.year())) + "-" +	
           (unsigned(newDate.month()) < 10 ? "0" : "") +
           to_string(unsigned(newDate.month())) + "-" +
           (unsigned(newDate.day()) < 10 ? "0" : "") +
           to_string(unsigned(newDate.day()));
}
  
void updateAccrual(unordered_map<string, string> &accountDetails, int days)
{
	// Initialize
	double accruedInterest;
	double balance;
	float rate;
    
	// Fetch necessary values
	accruedInterest = stod(accountDetails["Accrued Interest"]);
	rate = stof(accountDetails["Interest Rate"]);
	balance = stod(accountDetails["Balance"]);
	
	// Catch up accrual
	accruedInterest += balance * rate * (days/360);
	
	// Store it back
	accountDetails["Accrued Interest"] = to_string(accruedInterest);
	accountDetails["Last Accrual Date"] = addDays(accountDetails["Last Accrual Date"], days);
}

void compoundBalance(unordered_map<string, string> &accountDetails)
{
	// initialize
	double accruedInterest;
    double balance;
 
	// Fetch necessary values 
	accruedInterest = stod(accountDetails["Accrued Interest"]);
	balance = stod(accountDetails["Balance"]); 
    
	// Add the accrued interest back to the spendable balance
    accountDetails["Balance"] = to_string(balance + accruedInterest);

	// Reset Accrued Interest back to zero
	accountDetails["Accrued Interest"] = "0";
	
	// Add thirty days to the Last Compounding Date
    accountDetails["Last Compounding Date"] = addDays(accountDetails["Last Accrual Date"], FULL_MONTH);   // moves the compounding day forward by 30 
}

void catchUpBalance(unordered_map<string, string> &accountDetails)
{
	// Initialize
	string targetDate;
	int daysSinceAccrual;
    int daysSinceCompounding;
    int timesToCompound;
    int i = 0;

	// How many days have passed since accrued interest was added to balance (compounding)
	daysSinceCompounding = dateDifference(getToday(), accountDetails["Last Compounding Date"]);    

	if (daysSinceCompounding < FULL_MONTH)
	{
		// No compounding since not a month has passed
		daysSinceAccrual = dateDifference(getToday(), accountDetails["Last Accrual Date"]);
		updateAccrual(accountDetails, daysSinceAccrual);
		return;
	} 

	// Compounding is strictly sequential, the interest depends on the balance last month
	timesToCompound = daysSinceCompounding / FULL_MONTH;
	
	while (i < timesToCompound)
	{
		// One whole month as a date
		targetDate = addDays(accountDetails["Last Compounding Date"], FULL_MONTH);

		// Compute accrued interest then add to balance
		daysSinceAccrual = FULL_MONTH - dateDifference(targetDate, accountDetails["Last Accrual Date"]);
		updateAccrual(accountDetails, daysSinceAccrual);
		compoundBalance(accountDetails);
		i++;
	}

	//  Call itself to get interest for the leftover days
	catchUpBalance(accountDetails);
}