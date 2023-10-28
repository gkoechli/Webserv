#include "serverClass.hpp"

serverClass::serverClass()
{

}

serverClass::~serverClass()
{

}

std::string serverClass::getKeyContent(std::string key)
{
	if (data.find(key) != data.end())
		return this->data.find(key)->second;
	return ("");
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
	// this->printServerData();
	// this->printLocationList();
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
		std::cout << std::endl;
		itloc++;
	}
	std::cout << " ////////////////////////////////////////////////////////\n";
}

void serverClass::insert_location(std::pair<std::string, locationClass> obj)
{
	this->locationList.insert(obj);
}

void serverClass::printServerData()
{
	std::cout << "[SERVERDATA]\n";
	std::map<std::string, std::string>::iterator it = this->data.begin();
	while (it != this->data.end())
	{
		std::cout << it->first << " " << it->second << std::endl; 
		it++;
	}
	std::cout << " ....................................................... <\n";
}

void serverClass::printLocationList()
{
	std::cout << "[LOCATIONLIST]\n";
	std::map<std::string, locationClass>::iterator it = this->locationList.begin();
	while (it != this->locationList.end())
	{
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << " ....................................................... <\n";
}

locationClass&	serverClass::getLocationRef(std::string name)
{
	if (this->locationList.find(name) != this->locationList.end())
		return this->locationList[name];
	else
		throw std::exception();
}

std::map<std::string, locationClass>::iterator serverClass::getBeginLocationListIterator()
{
	std::map<std::string, locationClass>::iterator it;

	it = this->locationList.begin();
	return it;
}

std::map<std::string, locationClass>::iterator serverClass::getEndLocationListIterator()
{
	std::map<std::string, locationClass>::iterator it;

	it = this->locationList.end();
	return it;
}