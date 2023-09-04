#include "exec.hpp"

Exec::Exec() //will need settings and request string as argument
{

}

Exec::~Exec() {}

void Exec::print_response()
{
	std::cout << "current content of response object:" << std::endl;
	// std::string body = response.getbody();
	// std::cout << body << std::endl;
	std::cout << response.getPath() << std::endl;
	std::cout << response.getLocation() << std::endl;
	std::cout << response.getHeaderContent("Content-Type:") << std::endl;
	std::cout << response.getHeaderContent("Content-Length:") << std::endl;
	std::cout << response.getHeaderContent("Connection:") << std::endl;
	std::cout << response.getHeaderContent("Content-Language:") << std::endl;
	std::cout << response.getHeaderContent("Date:") << std::endl;
	std::cout << response.getHeaderContent("Server:") << std::endl;
	std::cout << response.getbody() << std::endl;
	std::cout << "end of response object." << std::endl;
}

void	Exec::mockup_response_object()
{
	response.setHTTPCode(404);
	response.setPath("/mnt/nfs/homes/rokerjea/webservRepo/Webserv/demosite/test.html");
	response.setLocation("Website/folder/file.extension");
	response.setCGI(false);
	response.setbody("\n"
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
	"<head>\n"
	"<meta charset=\"utf-8\">\n"
	"<title>A simple webpage</title>\n"
	"</head>\n"
	"<body>\n"
	"<h1>Simple HTML webpage</h1>\n"
	"<p>Hello, world!</p>\n"
	"</body>\n"
	"</html>\n"
	"\n"
	"\n");
	response.insertHeaderPair(std::make_pair("HTTP/1.1", "200 OK\n"));
	response.insertHeaderPair(std::make_pair("Content-Type:", "text/html; charset=utf-8\n"));
	response.insertHeaderPair(std::make_pair("Content-Length:", "55743\n"));
	response.insertHeaderPair(std::make_pair("Connection:", "keep-alive\n"));
	response.insertHeaderPair(std::make_pair("Content-Language:", "en-US\n"));
	response.insertHeaderPair(std::make_pair("Date:", "Thu, 06 Dec 2018 17:37:18 GMT\n"));
	response.insertHeaderPair(std::make_pair("Server:", "meinheld/0.6.1\n"));
	// std::string test = response.getPath();
	// test = response.getbody();
	//ERROR, if i delete last line exec fail immediatly
	//wich means a memory error usually
	//i might have made a mistake somewhere with pair or map, maybe an error of initialisation
}

std::vector<char> Exec::return_final_response()
{
	std::string full_response;
	full_response = response.getFullHeader();
	full_response += response.getbody();
    std::vector<char> res(full_response.begin(), full_response.end());
	return (res);
}