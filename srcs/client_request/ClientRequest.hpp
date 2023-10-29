#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include "../config_file_parsing/configParsing.hpp"

class configParsing;

std::pair<std::string, std::vector<std::string> > pair_Token_Vector(std::string key, std::vector<std::string> value);

class ClientRequest
{
	protected:
		std::string											method;
		std::string											path;
		std::string											http_version;
		std::string											body;
		std::string											target;
		std::string											port;
		std::map<std::string, std::vector<std::string> >	header;
		configParsing 										&ptr;

	public:
		ClientRequest(std::string, configParsing&);
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
		const std::string getTarget() const;
		const std::string getPort() const;
		serverClass& getConfigServerRef(std::string);
		std::string getHeaderContent(std::string);

		//set
		void	setPath(const std::string);
		void	setTarget(const std::string);
		void	setMethod(const std::string);
		void	setHttpVersion(const std::string);
		void	setBody(const std::string);
		void	setPort();
		void	setHeader(std::pair< std::string, std::vector<std::string> >);
		void	check_method();
		void	check_body_size();
		void	check_errors();

		void printAll() const; // d
		void printPath() const;    //d
		void printMethod() const;    //d
		void printTarget() const;    //d
		void printHttpVersion() const;    //d
		void printBody() const;    //d
		void printHeader();   //d
};

#endif