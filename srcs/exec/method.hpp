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
		std::string response_content;
		std::string _path;
		//File_manip file;
		//Request_obj &request;//need to have all infos needed to exec
		//maybe a pointer to settings/request?
	public:
		Method(std::string path/*Request_obj &request*/);
		~Method();

		bool	is_empty();
		bool	check_error();
		// void extract_path_from_request(/*request object*/);

		void	method_get();
		// void	method_post();
		// void	method_delete();

		// std::string get_content();
		std::string get_path();
		int get_status_code();

};

#endif