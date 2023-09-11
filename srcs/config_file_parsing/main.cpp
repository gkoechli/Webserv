#include "serverClass.hpp"
#include "configParsing.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong number of arguments\n";
		return (1);
	}
	try
	{
		configParsing test(av[1]);
		test.printServerInfo();
		
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}