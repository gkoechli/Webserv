#ifndef METHOD
#define METHOD
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>


class Method{
	private:
		int	status_code;
		// std::string content;
		std::string _path;
		//maybe a pointer to settings/request?
	public:
		Method(std::string path/*request object*/);
		~Method();

		bool	is_empty();
		bool	check_error();
		// void extract_path_from_request(/*request object*/);

		// void	method_get();
		// void	method_post();
		// void	method_delete();

		// std::string get_content();
		std::string get_path();
		int get_status_code();

};

#endif