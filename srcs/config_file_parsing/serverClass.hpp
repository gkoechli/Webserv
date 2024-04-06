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
		std::map<std::string, locationClass>::iterator getBeginLocationListIterator();
		std::map<std::string, locationClass>::iterator getEndLocationListIterator();
		void	insert_location(std::pair<std::string, locationClass>);
		void	printServerValues();
		void 	printServerData();
		void 	printLocationList();
		std::map<std::string, std::string>::iterator getBeginDataIterator();
		std::map<std::string, std::string>::iterator getEndDataIterator();
		locationClass&	getLocationRef(std::string);
		
	private:
		std::string server_name;
		std::map<std::string, std::string> data;
		std::map<std::string, locationClass> locationList;
};

#endif