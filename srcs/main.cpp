#include "config_file_parsing/configParsing.hpp"
#include "config_file_parsing/configClass.hpp"
#include "tcp_in_out/tcp.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong number of arguments\n";
		return (1);
	}
	try
	{
		Tcp_handler server(av[1]);
		// two.printConfFile();
		// std::pair<std::string, std::string> tmp = two.getListenPort();
		// std::cout << tmp.first << " ----------> " << tmp.second << std::endl;
		// std::cout << two.getKeyContent("cli_max_size") << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}