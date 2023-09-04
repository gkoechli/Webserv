#ifndef EXEC
# define EXEC

class Exec {
	private:
		std::string request_as_string;
		Request_obj	request;
		Response_obj	response;
		std::string	response_body;
		// Method method;
		// CGI cgi;

	public:
		Exec(std::string request_string/*configParsing &config*/);
		~Exec();

		void	request_parse();
		//checking step, everything that can be checked from request obj and settings
		//exec step: Method and CGI
		void	handle_exec();
		void	response_build();
		std::string get_response_as_string();//final command to get response to buffer
		void	mockup_response_object();//intermediate system to create a "valid" response
		//TODO: delete after final implementation!
}

#endif