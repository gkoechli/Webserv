#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>

std::pair<std::string, std::vector<std::string> > pair_Token_Vector(std::string key, std::vector<std::string> value);

class ClientRequest
{
	protected:
		std::string											method;
		std::string											path;
		std::string											http_version;
		std::string											body;
		std::map<std::string, std::vector<std::string> >	 	header;


	public:
		ClientRequest(std::string);
		ClientRequest(ClientRequest &to_copy);
		~ClientRequest();

		void	print();

		/*
		**	GETTER
		*/
		const std::string getPath() const;
		const std::string getMethod() const;
		const std::string getHttpVersion() const;
		const std::string getBody() const;
		// const std::map<std::string, std::vector<std::string>> getHeader() const;

		//set
		void	setPath(const std::string path);
		void	setMethod(const std::string method);
		void	setHttpVersion(const std::string http_version);
		void	setBody(const std::string body);
		void	setHeader(std::pair<std::string, std::vector<std::string> >);

		void printPath() const;    //d
		void printMethod() const;    //d
		void printHttpVersion() const;    //d
		void printBody() const;    //d
		void printHeader();    //d
};

#endif