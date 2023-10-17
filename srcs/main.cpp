#include "config_file_parsing/configParsing.hpp"
// #include "config_file_parsing/configClass.hpp"
#include "tcp_in_out/tcp.hpp"

int main(int ac, char **av)
{
	// add signal management, sigint
	if (ac != 2)
	{
		std::cerr << "Error : Usage is " << av[0] << " <config_file>.\n";
		return (ERROR);
	}
	try
	{
		Tcp_handler server(av[1]);
		std::cout << "Press ctrl+c to exit.\n";
		server.main_tcp_loop();
	}
	catch(std::exception &e)
	{
		std::cerr << "smtg went wrong!\n";
		return (ERROR);
	}
	return (SUCCESS);
}
