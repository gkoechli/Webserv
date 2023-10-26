#ifndef MODEL_HPP
#define MODEL_HPP

// #include "../exec/exec.hpp"
#include "../client_request/ClientRequest.hpp"
#include "../exec/response.hpp"
#include "file_manager.hpp"
#include <sys/types.h>
# include <sys/wait.h>

#include "unistd.h"

#include <utility>
#include "../tcp_in_out/utils.hpp"
#include <string>


class Model {
	private:
		ClientRequest &request;
		Response_obj response;
		file_manager file;
		int status_code;

	public:
		Model(ClientRequest &request);
		~Model();
		//isCGI

		char** mapToEnvp(const std::map<std::string, std::string>& m);
		char**	create_envp();
		void cgi_operation();
		std::vector<char> get_full_response_str();
		void	mockup_response_object();
		void method_get();
		void method_delete();
		void method_post();
		void set_status_code(int code);

		//cgi operation() //CGI obj only need to be instanciated here, not kept in private member
};

#endif