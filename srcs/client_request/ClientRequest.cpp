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
	// fill_basic_content(*this);
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
		else if (temp == "\r" || temp == "")//Carriage return (CRLF) to separate header from body
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
				this->setPath(targ);
				method = 0;
			}
			first = 1;
		}
	}
	this->setPort();
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

const std::string ClientRequest::getPort() const
{
	return (port);
}


void	ClientRequest::setPath(const std::string path)
{
	int found = 0;
	std::string tmp = "./demosite";
	tmp += path;
	if (*tmp.rbegin() == '/') // if autoindex -> on rajoute l'index du server s'il existe, sinon index.html
	{
		std::map<std::string, serverClass>::iterator it = this->ptr.getBeginServerListIterator();
		std::map<std::string, serverClass>::iterator ite = this->ptr.getEndServerListIterator();
		while (it != ite)
		{
			if (it->second.getKeyContent("autoindex") != "on")
			{
				found = 1;
				it++;
			}
			else
			{
				if (path.find(it->first) != std::string::npos)
				{
					std::map<std::string, locationClass>::iterator itl = it->second.getBeginLocationListIterator();
					std::map<std::string, locationClass>::iterator itel = it->second.getEndLocationListIterator();
					while (itl != itel)
					{
						if (path.find(it->second.getLocationRef((itl->second.getName())).getName()) != std::string::npos)
						{
							tmp += itl->second.getKeyContent("index");
							found = 1;
							break;
						}
						itl++;
					}
					break;
				}	
				it++;
			}
		}
		if (found == 0)
			tmp += "index.html";
	}
	this->path = tmp;
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

void	ClientRequest::setPort()
{
	std::string tmp;
	
	if (this->header.find("Host") != this->header.end())
	{
		tmp = this->getHeaderContent("Host");
		if (tmp.find(":") != std::string::npos)
			tmp = tmp.substr(tmp.find(":") + 1, tmp.size());
	}
	this->port = tmp;
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
	std::cout << "|" << this->getBody() << "|" << std::endl;
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

void	ClientRequest::check_method()
{
	std::string  getHeaderContentRet;
	std::string allowed;
	getHeaderContentRet = this->getPort();
	allowed = ptr.getServerRef(getHeaderContentRet).getKeyContent("allow");
	// std::cout << "allowed = " << allowed << std::endl;  
	// std::cout << "getmethod = " << this->getMethod() << std::endl;
	if (allowed.find(this->getMethod()) == std::string::npos)
	{
		std::cout << "Method not allowed or non existant\n";
		throw std::exception();
	}
}

void	ClientRequest::check_body_size()
{
	std::string  getHeaderContentRet;
	std::string tmp;
	getHeaderContentRet = this->getPort();
	tmp = ptr.getServerRef(getHeaderContentRet).getKeyContent("cli_max_size");
	std::stringstream ret(tmp);
	size_t diff;
	ret >> diff;
	if (this->body.size() >= diff)
	{
		throw 413;
	}
}

void	ClientRequest::check_errors()
{
	int i;
	i = ptr.findServer(this->getPort());
	if ( i != 200)
	{
		std::cerr << "Couldn't find server, wrong port" << std::endl;
		throw std::exception();
	}
	// else
	// 	std::cout << "FOUND " << this->getHeaderContent("Host") << std::endl;
	this->check_method();
	this->check_body_size();
}

void ClientRequest::printAll() const
{
	std::cout << "Path = ";
	this->printPath();
	std::cout << "Method = ";
	this->printMethod();
	std::cout << "Target = ";
	this->printTarget();
	std::cout << "HttpVersion = ";
	this->printHttpVersion();
	std::cout << "Body = ";
	this->printBody();
}