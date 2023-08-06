#include "configClass.hpp"

std::pair<std::string, std::string> pairIt(std::string key, std::string value)
{
	std::pair<std::string, std::string> ret(key, value);
	return ret;
}

configClass::configClass()
{
	this->file.insert(pairIt("allow","PUT GET DELETE POST"));
	this->file.insert(pairIt("listen", "127.0.0.1:8080"));
	this->file.insert(pairIt("cli_max_size","5000000"));
	this->file.insert(pairIt("error page","404 error.html"));
	this->file.insert(pairIt("server_name", "rokekoe"));
	this->file.insert(pairIt("index","index.html"));
	this->file.insert(pairIt("cgi_pass","/usr/bin/php-cgi"));
	this->file.insert(pairIt("autoindex", "on"));
}

configClass::~configClass()
{

}

configClass::configClass(const configClass& copy)
{
	*this = copy;
}

configClass &configClass::operator=(const configClass& obj)
{
	this->file = obj.file;
	return (*this);

}

void	configClass::printConfFile()
{
	std::map<std::string, std::string>::iterator it = this->file.begin();
	while (it != this->file.end())
	{
		std::cout << it->first << "  -------------->  " << it->second << std::endl;
		it++;
	}
}

std::pair<std::string, std::string> configClass::getListenPort()
{
	std::string tmp = this->file.find("listen")->second;
	
	std::string pop1;
	std::string pop2;
	

	pop1 = tmp.substr(0, tmp.find(":"));
	
	pop2 = tmp.substr(tmp.find(":") + 1, tmp.size() - tmp.find(":"));
	std::cout << pop1 << " " << pop2 << std::endl;
	return pairIt(pop1, pop2);
}

std::string configClass::getKeyContent(std::string key)
{
	std::string ret = this->file.find(key)->second;
	return (ret);
}