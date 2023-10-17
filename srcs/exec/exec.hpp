#ifndef EXEC
# define EXEC

#include "response.hpp"
#include "../Model/Model.hpp"
#include "../client_request/ClientRequest.hpp"
#include <utility>
#include <string>

class Exec {
	private:
		std::string request_as_string; // del
		ClientRequest	request;

	public:
		Exec(std::string request_string/*configParsing &config*/);
		~Exec();

		void	main_exec_loop();
		// void	response_build();
		// void	print_response(); //Del
		void	mockup_response_object();//intermediate system to create a "valid" response //Del
		std::vector<char> return_final_response();
		//TODO: delete after final implementation!
};

#endif