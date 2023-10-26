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

// std::pair<std::string, std::string> pairIt(std::string key, std::string value)
// {
// 	std::pair<std::string, std::string> ret(key, value);
// 	return ret;
// }

// std::vector<std::string> clientParsing(std::string obj)
// {
// 	std::vector<std::string> tab;
// 	std::string temp;
// 	std::stringstream ss(obj);
// 	while (std::getline(ss, temp))
// 		tab.push_back(temp);
// 	std::vector<std::string>::iterator it = tab.begin();
// 	while (it != tab.end())
// 	{
// 		std::cout << *it << std::endl;
// 		it++;
// 	}
// 	if (tab.begin()->find("GET") == std::string::npos && tab.begin()->find("POST") == std::string::npos && tab.begin()->find("DELETE") == std::string::npos)
// 		throw std::exception();
// }


void	fill_basic_content(ClientRequest &obj)
{
	std::vector<std::string> temp;
	temp.push_back("webserv.com");
	obj.setPath("./demosite/index.html");
	obj.setHttpVersion("HTTP/1.1");
	obj.setMethod("GET /fr/docs/Glossary/Simple_header HTTP/1.1");
	obj.setBody("<THIS IS THE BODY>\n");
	std::pair<std::string, std::vector<std::string> > ret("Host", temp);
	obj.setHeader(ret);
}