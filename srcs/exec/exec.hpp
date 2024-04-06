#ifndef EXEC
# define EXEC

#include "response.hpp"
#include "HttpCodes.hpp"
#include "../Model/Model.hpp"
#include "../client_request/ClientRequest.hpp"
#include "../config_file_parsing/configParsing.hpp"
#include "../config_file_parsing/serverClass.hpp"
#include <utility>
#include <string>
#include "../tcp_in_out/utils.hpp"

class Exec {
	private:
		std::string request_as_string;
		configParsing	&config;
		int default_error_code;
		std::string default_error_path;

	public:
		Exec(std::string request_string, configParsing &config);
		~Exec();

		void	main_exec_loop();

		bool is_cgi(ClientRequest &request);
		void error_in_settings(std::string error_path);
		std::vector<char> return_final_response();
		std::vector<char> error_response_constructor(int error_code);
};

#endif