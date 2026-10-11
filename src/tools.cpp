// ADD BEHAVIOUR SO THAT USER INPUT WORKS FLAWLESSLY
int stoi(string str, int flag=67)
{
	try
	{
		return std::stoi(str);
	}
	catch (std::exception &e)
	{
		return -1;
	}
}