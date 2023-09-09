#ifndef EXEC
# define EXEC

#include "response.hpp"
#include "../client_request/ClientRequest.hpp"
#include <utility>
#include <string>

class Exec {
	private:
		std::string request_as_string;
		ClientRequest	request;
		Response_obj	response;
		// std::string	response_body; //not needed?
		// Method method; //Maybe not needed here, can be instanciated in exec handler?
		// CGI cgi; //Same as method

	public:
		Exec(std::string request_string/*configParsing &config*/);
		~Exec();

		// void	request_parse();
		//checking step, everything that can be checked from request obj and settings
		//exec step: Method and CGI
		void	main_exec_loop();
		// void	response_build();
		void	print_response(); //Del
		void	mockup_response_object();//intermediate system to create a "valid" response //Del
		std::vector<char> return_final_response();
		//TODO: delete after final implementation!
};

#endif