#include "configParsing.hpp"
#include "configClass.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong number of arguments\n";
		return (1);
	}
	try
	{
		configParsing one(av[1]);
		// one.routine();
		// one.printLines();
		configClass two;
		// two.printConfFile();
		std::pair<std::string, std::string> tmp = two.getListenPort();
		std::cout << tmp.first << " ----------> " << tmp.second << std::endl;
		std::cout << two.getKeyContent("cli_max_size") << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "smtg went wrong!\n";
		return (1);
	}
	return (0);
}