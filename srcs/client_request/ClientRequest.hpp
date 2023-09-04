#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>

class ClientRequest 
{
	protected:
		std::string											method;
		std::string											path;
		std::string											http_version;
		std::string											body;
		std::map<std::string, std::vector<std::string> > 	header;


	public:
		ClientRequest();
		ClientRequest(const ClientRequest &copy);
		~ClientRequest();

		ClientRequest
		&operator=(const ClientRequest &copy);

		void	print();

		/*
		**	GETTER
		*/
		const std::string getPath() const;
		const std::string getMethod() const;
		const std::string getHttpVersion() const;
		const std::string getBody() const;
		const std::map<std::string, std::vector<std::string>> getHeader() const;

		//set
		void	setPath(const std::string path);
		void	setMethod(const std::string method);
		void	setHttpVersion(const std::string http_version);
		void	setBody(const std::string body);
		void	setHeader(const std::map<std::string, std::vector<std::string> > header);
};

#endif