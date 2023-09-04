#include "ClientRequest.hpp"

std::pair<std::string, std::string> pairIt(std::string key, std::string value)
{
	std::pair<std::string, std::string> ret(key, value);
	return ret;
}

void	fill_basic_content(ClientRequest &obj)
{
	obj.setHttpVersion("HTTP/1.1");
	obj.setMethod("GET /fr/docs/Glossary/Simple_header HTTP/1.1");
	obj.header->insert(pairIt("Host", "developer.mozilla.org"));
	obj.header->insert(pairIt("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0"));
	obj.header->insert(pairIt("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"));
	obj.header->insert(pairIt("Accept-Language", "en-US,en;q=0.5"));
	obj.header->insert(pairIt("Accept-Encoding", "gzip, deflate, br"));
	obj.header->insert(pairIt("Referer", "https://developer.mozilla.org/fr/docs/Glossary/Simple_header"));
	obj.setBody("THIS IS THE BODY\n");
}