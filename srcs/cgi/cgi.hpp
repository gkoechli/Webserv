#ifndef CGI_CPP
# define CGI_CPP
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>
# include <unistd.h>
class cgi 
{
	public:
		cgi(std::string);
		~cgi();
		std::string	getPath();
		std::string	getFunction();
		char *getPathInChar();
		char *getFunctionInChar();
	private:
		std::string path;
		std::string fct;
};

#endif