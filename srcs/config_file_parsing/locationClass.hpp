#ifndef LOCATIONCLASS_HPP
# define LOCATIONCLASS_HPP
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>

class locationClass 
{
	public:
		locationClass();
		~locationClass();
		void	insertPair(std::pair<std::string, std::string>);
		void	setName(std::string);
		std::string getName();
		std::string getKeyContent(std::string);
		void	printLocationValues();
	private:
		std::string location_name;
		std::map<std::string, std::string> data;
};
#endif