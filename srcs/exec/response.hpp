#ifndef RESPONSE
# define RESPONSE

# include <string>
# include <iostream>
# include <iomanip>
# include <map>
# include <cstring>
# include <sstream>
# include <string>
# include <fstream>
# include <vector>

class Response_obj {
	private:
		//all variables
		int	http_code;
		std::string path;
		std::string	location;
		std::string	body;
		std::map<std::string, std::string> header;
		bool isCGI;
	public:
		Response_obj();
		~Response_obj();

		//setter
		void	setHTTPCode(int code);
		void	setPath(std::string path);
		void	setLocation(std::string location);
		void	setCGI(bool isCGI);
		void	setbody(std::string body);
		void	insertHeaderPair(std::pair<std::string, std::string>);

		//getter

		// const std::vector<char>	&getResponse() const;
		int				getHTTPCode() const;
		std::string		getPath() const;
		std::string		getLocation() const;
		bool					getisCGI() const;
		std::string 			getHeaderContent(std::string HeaderKey);
		std::string				getFullHeader();
		std::string				getbody();
};

#endif