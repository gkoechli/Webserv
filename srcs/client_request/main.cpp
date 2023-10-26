#include "ClientRequest.hpp"

void	fill_basic_content(ClientRequest &obj);

int main(int argc, char **argv)
{
	try
	{
		configParsing test1(argv[1]);
		test1.printServerInfo();
		// std::cout << test1.findServer(argv[2]) << std::endl;
		std::string insert_string_here = "POST webserv.com/set_cookies/ HTTP/1.1\nHost webserv.com\nfucking hell\n\nNOWTHISISTH\nEBODDY\nITSHUGE\nITSMARV\n\nELOUS";
		ClientRequest test((insert_string_here), test1);
		test.printAll();
		// test.printHeader();
		// test1.getServerRef(argv[2]).printServerValues();
		// std::cout << test.getMethod() << std::endl;
		// std::cout << test.getHeaderContent("Host") << std::endl;
		// std::cout << test.getMethod()<< std::endl;
		// test1.printConfFile();
		// test1.printLines();
		// std::cout << test.getTarget();
		// std::cout <<  "getkeycontent(server_name) = " << test1.getKeyContent("server_name") << std::endl;
		// test1.printServerInfo();
		// test.check_errors();
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}