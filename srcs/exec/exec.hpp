#ifndef EXEC
# define EXEC

#include "response.hpp"
#include "../Model/Model.hpp"
#include "../client_request/ClientRequest.hpp"
#include "../config_file_parsing/configParsing.hpp"
#include <utility>
#include <string>
#include "../tcp_in_out/utils.hpp"

class Exec {
	private:
		std::string request_as_string;
		configParsing	&config;

	public:
		Exec(std::string request_string, configParsing &config);
		~Exec();

		void	main_exec_loop();
		// void	response_build();
		// void	print_response(); //Del
		void	mockup_response_object();//intermediate system to create a "valid" response //Del
		std::vector<char> return_final_response();
		std::vector<char> error_response_constructor(int error_code);
		//TODO: delete after final implementation!
};

#endif