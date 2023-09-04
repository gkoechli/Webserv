#ifndef RESPONSE
# define RESPONSE

# include <string>

class Response_obj {
	private:
		//all variables
		int	http_code;
		std::string path;
		std::string	location;
		std::string	body;
		std::map<std::string, std::string> header;
		bool isCGI;
		//Request client_request;
		//Settings	settings;
	public:
		Response_obj();
		~Response_obj();

		//setter
		void	setHTTPCode(int code);
		void	setPath(std::string path);
		void	setLocation(std::string location);
		void	setCGI(bool isCGI);
		void	setbody(std string body);
		void	insertBodyPair(std::pair<std::string, std::string>);
		// void	setRequest(Request_obj request);
		// void	setSettings(Settings settings);

		//getter

		const std::vector<char>	&getResponse() const;
		const int				&getHTTPCode() const;
		const std::string		&getPath() const;
		const std::string		&getLocation() const;
		bool					isCGI() const;
		std::string 			getHeaderContent(std::string HeaderKey);
		// const					&getRequest() const;
		// const					&getSettings() const;
		std::stri
};

#endif