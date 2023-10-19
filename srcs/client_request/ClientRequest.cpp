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

std::pair<std::string, std::vector<std::string> > pair_Token_Vector(std::string key, std::vector<std::string> value)
{
	std::pair<std::string, std::vector<std::string> > ret(key, value);
	return ret;
}



ClientRequest::ClientRequest(std::string obj, configParsing &confptr):ptr(confptr)
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
		if (body == 1) // if last line was empty we parse the body
		{
			if (first == 2)
			{
				first = 1;
				this->body = temp;
			}
			else
			{
				this->body += "\n";
				this->body += temp;
			}
		}
		else if (temp == "")
		{
			body = 1;
			first = 2;
		}
		else
		{
			std::vector<std::string> tab;
			std::stringstream wording(temp);
			while (wording >> word)
			{
				if (first == 1) // each first element of line will be the token
				{
					token = word;
					first = 0;
				}
				else
					tab.push_back(word); // the rest is setup as std::vector<string> and added as value to the map
			}
			this->setHeader(pair_Token_Vector(token, tab));
			if (method == 1) // if its the first line we get the method and version. it is still added to the map -> change it ?
			{
				this->setMethod(token);
				this->setHttpVersion(tab.back());

				tab.pop_back();
				std::vector<std::string>::iterator it = tab.begin();
				std::string targ = "";
				int i = 1;
				while (it != tab.end())
				{
					if (i == 1)
					{
						targ = *it;
						i = 0;
					}
					else
					{
						targ += " ";
						targ += *it;
					}
					it++;
				}
				this->setTarget(targ);
				method = 0;
			}
			first = 1;
		}
	}
	// this->check_errors();
	// if (tab.begin()->find("GET") == std::string::npos && tab.begin()->find("POST") == std::string::npos && tab.begin()->find("DELETE") == std::string::npos)
	// 	throw std::exception();

	// penser a check si methode existe.
	// this->printMethod();  //d
	// this->printPath();  //d
	// this->printHttpVersion();  //d
	// this->printHeader();  //d
	// this->printBody();  //d
}


ClientRequest::ClientRequest(ClientRequest &request_to_copy):ptr(request_to_copy.ptr)
{
	this->ptr = request_to_copy.ptr;
	(void)request_to_copy;
	
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

const std::string ClientRequest::getTarget() const
{
	return (target);
}

std::string ClientRequest::getHeaderContent(std::string contentkey)
{
	std::string ret = "";
	if (this->header.find(contentkey) != this->header.end())
	{
		std::vector<std::string>::iterator it = this->header.find(contentkey)->second.begin();
		while (it != this->header.find(contentkey)->second.end())
		{
			// std::cout << *it << std::endl;
			ret += *it;
			it++;
		}
	}
	// std::cout << "ret  = "  << ret << std::endl;
	return ret;
}

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

void	ClientRequest::setTarget(const std::string targ)
{
	this->target = targ;
}

void	ClientRequest::setHeader(std::pair<std::string, std::vector<std::string> > head)
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

void ClientRequest::printTarget() const   // d
{
	std::cout << this->getTarget() << std::endl;
}

void ClientRequest::printHeader()   // d
{
	std::map<std::string,std::vector<std::string> >::iterator it = this->header.begin();
	while (it != this->header.end())
	{
		std::cout << it->first << " // ";
		for (std::vector<std::string>::iterator itx = it->second.begin(); itx != it->second.end(); itx++)
			std::cout << *itx << " ";
		std::cout << std::endl;
		it++;
	}
}

void	ClientRequest::check_errors()
{
	int i;
	i = ptr.findServer(ptr.getKeyContent(this->getHeaderContent("server_name")));
	std::cout << "i = " << i << std::endl;
	if ( i != 200)
	{
		throw std::exception();
	}
}