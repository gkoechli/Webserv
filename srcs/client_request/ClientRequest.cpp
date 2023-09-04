#include "ClientRequest.hpp"

ClientRequest::ClientRequest(): method(), path(), http_version(), body(), header()
{
	
}

ClientRequest::ClientRequest(const ClientRequest &copy)
{
	if (this != &copy)
		*this = copy;
}

ClientRequest::~ClientRequest()
{

}

ClientRequest  &ClientRequest::operator=(const ClientRequest &copy)
{
	if (this != &copy)
	{
		http_version = copy.http_version;
		method = copy.method;
		path = copy.path;
		header = copy.header;
		body = copy.body;
	}
	return (*this);
}

//get

const std::string	ClientRequest::getPath() const
{ return (path); }

const std::string	ClientRequest::getMethod() const
{ return (method); }

const std::string	ClientRequest::getHttpVersion() const
{ return (http_version); }

const std::vector<char>	ClientRequest::getBody() const
{ return (body); }

const std::map<std::string, std::vector<std::string> >	ClientRequest::getHeader() const
{ return (header); }

//set

void	ClientRequest::setPath(const std::string path)
{ path = path; }

void	ClientRequest::setMethod(const std::string method)
{ method = method; }

void	ClientRequest::setHttpVersion(const std::string http_version)
{ http_version = http_version; }

void	ClientRequest::setBody(const std::vector<char> body)
{ body = body; }

void	ClientRequest::setHeader(const std::map<std::string, std::vector<std::string> > header)
{ header = header; }