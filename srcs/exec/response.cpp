#include "response.hpp"

Response_obj::Response_obj()
{
	http_code = 200
}
~Response_obj::Response_obj() {}

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
void	Response_obj::insertBodyPair(std::pair<std::string, std::string> headerPair)
{
	this->data.insert(headerPair);
}
// void	setRequest(Request_obj request)
// void	setSettings(Settings settings)

//getter

//TODO: response aggregator from header and body, as a string or vector<char>
// const std::vector<char>	&getResponse() const
// {
// 	return ()
// }
const int				Response_obj::&getHTTPCode() const
{
	return (http_code);
}
const std::string		Response_obj::&getPath() const
{
	return (path);
}
const std::string		Response_obj::&getLocation() const
{
	return (location);
}
bool					Response_obj::isCGI() const
{
	return (isCGI);
}
std::string 			Response_obj::getHeaderContent(std::string HeaderKey)
{
	return (this->data.find(HeaderKey)->second);
}
std::string 			Response_obj::getBody()
{
	return (body);
}
// const					&getRequest() const
// const					&getSettings() const