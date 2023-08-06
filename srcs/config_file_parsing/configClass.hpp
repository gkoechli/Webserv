#ifndef CONFIGCLASS_CPP
# define CONFIGCLASS_CPP
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>

class configClass 
{
	public:
		configClass();
		~configClass();
		configClass(const configClass&);
		configClass &operator=(const configClass&);
		void	printConfFile();
		std::pair<std::string, std::string> getListenPort();
		std::string getKeyContent(std::string);
	private:
		std::map<std::string, std::string> file;
	
	
};


#endif