#include "ClientRequest.hpp"
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>

void	fill_basic_content(ClientRequest &obj);
std::pair<std::string, std::vector<std::string>> pair_Token_Vector(std::string key, std::vector<std::string> value)
{
	std::pair<std::string, std::vector<std::string>> ret(key, value);
	return ret;
}

ClientRequest::ClientRequest(std::string obj)
{
	fill_basic_content(*this);
	
	std::string temp;
	int first = 1;
	int body = 0;
	int method = 1;
	std::string word;
	std::string token;
	std::stringstream ss(obj);
	while (std::getline(ss, temp))
	{
		if (body == 1)
		{
			this->setBody(temp);
			break;
		}
		if (temp == "")
			body = 1;
		else
		{
			std::vector<std::string> tab;
			std::stringstream wording(temp);
			while (wording >> word)
			{
				if (first == 1)
				{
					token = word;
					first = 0;
				}
				else
					tab.push_back(word);
			}
			this->setHeader(pair_Token_Vector(token, tab));
			if (method == 1)
			{
				this->setMethod(temp);
				this->setHttpVersion(tab.back());
				method = 0;
			}
		}
		first = 1;
	}	
	// if (tab.begin()->find("GET") == std::string::npos && tab.begin()->find("POST") == std::string::npos && tab.begin()->find("DELETE") == std::string::npos)
	// 	throw std::exception();

	// penser a check si methode existe.
	this->printMethod();  //d
	this->printPath();  //d
	this->printHttpVersion();  //d
	this->printHeader();  //d
	this->printBody();  //d
}

ClientRequest::~ClientRequest()
{

}

//get

const std::string	ClientRequest::getPath() const
{
	return (path);
}

const std::string	ClientRequest::getMethod() const
{
	return (method);
}

const std::string	ClientRequest::getHttpVersion() const
{
	return (http_version);
}

const std::string ClientRequest::getBody() const
{
	return (body);
}
// const std::map<std::string, std::string>	ClientRequest::getHeader() const
// {
// 	return (header);
// }

//set

void	ClientRequest::setPath(const std::string path)
{ 
	this->path = path;
}

void	ClientRequest::setMethod(const std::string method)
{ 
	this->method = method; 
}

void	ClientRequest::setHttpVersion(const std::string http_version)
{ 
	this->http_version = http_version;
}

void	ClientRequest::setBody(const std::string body)
{
	this->body = body;
}

void	ClientRequest::setHeader(std::pair<std::string, std::vector<std::string>> head)
{
	this->header.insert(head);
}

void ClientRequest::printPath() const   // d
{
	std::cout << this->getPath() << std::endl;
}

void ClientRequest::printMethod() const   // d
{
	std::cout << this->getMethod() << std::endl;
}

void ClientRequest::printHttpVersion() const   // d
{
	std::cout << this->getHttpVersion() << std::endl;
}

void ClientRequest::printBody() const   // d
{
	std::cout << this->getBody() << std::endl;
}

void ClientRequest::printHeader()   // d
{
	std::map<std::string,std::vector<std::string>>::iterator it = this->header.begin();
	while (it != this->header.end())
	{
		std::cout << it->first << " // ";
		for (std::vector<std::string>::iterator itx = it->second.begin(); itx != it->second.end(); itx++)
			std::cout << *itx << " ";
		std::cout << std::endl;
		it++;
	}
}