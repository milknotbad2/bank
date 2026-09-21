#include <sstream>
#include "osrandom.hpp"
#include "picosha2.h"

// NOTE: DO NOT use using namespace std; since this conflicts with "osrandom.hpp"

/*
The password system goes like this:
	* Every account has a unique salt (added security feature)
	* The password they will input is not the password we will 
		store in the database, instead we will combine it with 
		their salt, then turn it into a unique irreversible 
		string using the function: 
		
			picosha2::hash256_hex_string(salt + password);
			
		which will return an irreversible string, which we will
		store in the database
	* Then to check if their password is correct, we do the same 
		procedure for the inputted password, then we will check if
		this is the same string stored in their account in the database
*/

std::string createPassword(std::string salt, std::string password)
{
	return picosha2::hash256_hex_string(salt + password);
}

bool isPasswordCorrect(std::string passwordToCheck, std::string salt, std::string hashedPassword)
{
	return picosha2::hash256_hex_string(salt + passwordToCheck) == hashedPassword;
}

std::string generateSalt()
{
	Chocobo1::OSRandom randomNum;
	std::string salt;
	std::stringstream stream;
	
	for (int i = 0; i < 16; i++)
	{
		stream << std::hex << randomNum();
		salt += stream.str();
		stream.str("");
	}
	
	return salt;
}