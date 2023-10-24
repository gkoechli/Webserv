#ifndef MODEL_HPP
#define MODEL_HPP

// #include "../exec/exec.hpp"
#include "../client_request/ClientRequest.hpp"
#include "../exec/response.hpp"
#include "file_manager.hpp"

#include <utility>
#include "../tcp_in_out/utils.hpp"
#include <string>


class Model {
	private:
		ClientRequest &request;
		Response_obj response;
		//settings, maybe this should be inside request object
		file_manager file;
		int status_code;

	public:
		Model(ClientRequest &request);
		~Model();
		//isCGI
		//response builder()
		std::vector<char> get_full_response_str();
		void	mockup_response_object();
		//handle operation()
		void method_get();
		void method_delete();
		void method_post();
		void set_status_code(int code);
		
		//build error response
		// move response mockup here
		//cgi operation() //CGI obj only need to be instanciated here, not kept in private member
		// void cgi_operation();
		
};

#endif