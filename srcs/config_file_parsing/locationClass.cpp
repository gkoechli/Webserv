#include "locationClass.hpp"

locationClass::locationClass()
{

}

locationClass::~locationClass()
{

}


std::string locationClass::getKeyContent(std::string key)
{
	return (this->data.find(key)->second);
}

std::string locationClass::getName()
{
	return (this->location_name);
}

void	locationClass::setName(std::string name)
{
	this->location_name = name;
}

void	locationClass::insertPair(std::pair<std::string, std::string> obj)
{
	if (obj.first == "location_name")
		this->location_name = obj.second;
	this->data.insert(obj);
}

void	locationClass::printLocationValues()
{
	std::map<std::string, std::string>::iterator it = this->data.begin();
	std::cout << "LOCATION : " << this->getName() << std::endl;
	while (it != this->data.end())
	{
		std::cout << it->first << " : " << it->second << std::endl;
		it++;
	}
}