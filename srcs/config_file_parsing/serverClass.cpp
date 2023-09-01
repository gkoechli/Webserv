#include "serverClass.hpp"

serverClass::serverClass()
{

}

serverClass::~serverClass()
{

}

std::string serverClass::getKeyContent(std::string key)
{
	return (this->data.find(key)->second);
}

std::string serverClass::getName()
{
	return (this->server_name);
}

void	serverClass::insertPair(std::pair<std::string, std::string> obj)
{
	if (obj.first == "server_name")
		this->server_name = obj.second;
	this->data.insert(obj);
}

void	serverClass::printServerValues()
{
	std::map<std::string, std::string>::iterator it = this->data.begin();
	std::cout << "SERVER : " << this->getName() << std::endl;
	while (it != this->data.end())
	{
		std::cout << it->first << " : " << it->second << std::endl;
		it++;
	}
	std::cout << "   ------------------  \n";
	std::map<std::string, locationClass>::iterator itloc = this->locationList.begin();
	while (itloc != this->locationList.end())
	{
		itloc->second.printLocationValues();
		itloc++;
	}
	std::cout << " ////////////////////////////////////////////////////////\n";
}

void serverClass::insert_location(std::pair<std::string, locationClass> obj)
{
	this->locationList.insert(obj);
}

