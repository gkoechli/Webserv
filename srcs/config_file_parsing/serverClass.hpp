#ifndef SERVERCLASS_HPP
# define SERVERCLASS_HPP
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>
# include "locationClass.hpp"

class serverClass 
{
	public:
		serverClass();
		~serverClass();
		void	insertPair(std::pair<std::string, std::string>);
		std::string getName();
		std::string getKeyContent(std::string);
		void	insert_location(std::pair<std::string, locationClass>);
		void	printServerValues();
	private:
		std::string server_name;
		std::map<std::string, std::string> data;
		std::map<std::string, locationClass> locationList;
};
#endif