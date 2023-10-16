#include "config_file_parsing/configParsing.hpp"
// #include "config_file_parsing/configClass.hpp"
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
		server.main_tcp_loop();
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}
