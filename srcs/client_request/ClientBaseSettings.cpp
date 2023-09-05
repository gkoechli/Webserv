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

std::pair<std::string, std::string> pairIt(std::string key, std::string value)
{
	std::pair<std::string, std::string> ret(key, value);
	return ret;
}

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
	obj.setPath("/dev/nul");
	obj.setHttpVersion("HTTP/1.1");
	obj.setMethod("GET /fr/docs/Glossary/Simple_header HTTP/1.1");
	// obj.setHeader(pairIt("Host", "developer.mozilla.org"));
	// obj.setHeader(pairIt("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0"));
	// obj.setHeader(pairIt("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"));
	// obj.setHeader(pairIt("Accept-Language", "en-US,en;q=0.5"));
	// obj.setHeader(pairIt("Accept-Encoding", "gzip, deflate, br"));
	// obj.setHeader(pairIt("Referer", "https://developer.mozilla.org/fr/docs/Glossary/Simple_header"));
	obj.setBody("<THIS IS THE BODY>\n");
}