#include "response.hpp"

Response_obj::Response_obj()
{
	http_code = 200;
}
Response_obj::~Response_obj() {}

//setter
void	Response_obj::setHTTPCode(int code)
{
	http_code = code;
}
void	Response_obj::setPath(std::string path_to_set)
{
	path = path_to_set;
}
void	Response_obj::setLocation(std::string location_to_set)
{
	location = location_to_set;
}
void	Response_obj::setCGI(bool isCGI)
{
	this->isCGI = isCGI;
}
void	Response_obj::setbody(std::string body_to_set)
{
	body = body_to_set;
}
void	Response_obj::insertHeaderPair(std::pair<std::string, std::string> headerPair)
{
	this->header.insert(headerPair);
}

//getter

int				Response_obj::getHTTPCode() const
{
	return (http_code);
}
std::string		Response_obj::getPath() const
{
	return (path);
}
std::string		Response_obj::getLocation() const
{
	return (location);
}
bool					Response_obj::getisCGI() const
{
	return (isCGI);
}
std::string 			Response_obj::getHeaderContent(std::string HeaderKey)
{
	return (this->header.find(HeaderKey)->second);
}


std::string				Response_obj::getFullHeader()
{
	std::string full_response;
	std::map<std::string, std::string>::iterator it = header.begin();
	while (it != header.end())
	{
		full_response += it->first;
		full_response += " ";
		full_response += it->second;
		it++;
	}
	return (full_response);
}

std::string 			Response_obj::getbody()
{
	return (body);
}