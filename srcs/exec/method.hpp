#ifndef METHOD
#define METHOD
#include <iostream>


class Method{
	private:
		int	status_code;
		std::string content;
		std::string path;
		//maybe a pointer to settings/request?
	public:
		Method(std::string path/*request object*/);
		~Method();

		void extract_path_from_request(/*request object*/);

		void	method_get();
		void	method_post();
		void	method_delete();

		std::string get_content();
		int get_status_code();

};

#endif