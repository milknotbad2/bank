#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define DELIMITER '\x1F'

string getAccountDetails(string accountID);
// other getter/setter

string getAccountDetails(string accountID)
{
	fstream database("database.txt", ios::in);
	string line;
	string id;
	
	while (getline(database, line))
	{
		stringstream sstream(line);
		
		if (getline(sstream, id, '\x1F'))
		{
			if (id == accountID)
			{
				return line;
			}
		}
	}
	
	database.close();
	
	return "";
}