#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
	private:
		ClientRequest &request;
		Response_obj response;
		//settings, maybe this should be inside request object
		File file;
		int status_code;

	public:
		Model(/*args*/);
		~Model();
		//isCGI
		//response builder()
		std::string get_full_response_str();
		//handle operation()
		void get();
		//post
		//delete
		//build error response
		// move response mockup here
		//cgi operation() //CGI obj only need to be instanciated here, not kept in private member
};

#endif