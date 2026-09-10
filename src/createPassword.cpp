#include "osrandom.hpp"
#include "picosha2.h"

std::string createPassword(std::string salt, std::string password)
{
	return picosha2::hash256_hex_string(salt + password);
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